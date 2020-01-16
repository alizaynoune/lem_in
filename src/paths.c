/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alzaynou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 10:27:58 by alzaynou          #+#    #+#             */
/*   Updated: 2020/01/12 22:09:16 by alzaynou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"

t_paths		*find_paths(t_roms *roms, t_paths *head, int start, int end)
{
	t_vist	*vist;
	t_stack	*stack;
	t_stack	*tstk;

	vist = rom_not_vist(NULL, roms[start].childe , NULL, end);
	stack = push_to_stack(start, NULL);
	while (vist)
	{
		if (vist->lst)
		{
			start = vist->lst->index;
			stack = push_to_stack(start, stack);
			vist->lst = vist->lst->next;
			if (stack && stack->index == end)
				head = get_paths(stack, head);
			if ((stack->index != end) || (vist && !vist->lst))
				vist = rom_not_vist(vist, roms[stack->index].childe, stack, end);
			else
				stack = free_stack(stack);
		}
		if ((vist && !vist->lst) || (stack && stack->index == end))
		{
			stack = free_stack(stack);
			vist = free_vist(vist);
		}
	}
	return (head);
}

t_paths		*get_paths(t_stack *stack, t_paths *head)
{
	t_paths		*new;
	t_paths		*tmp;

	tmp = head;
	new = (t_paths *)malloc(sizeof(t_paths));
	new->next = NULL;
	new->n_roms = 0;
	new->path = stack_to_path(stack, &new->n_roms);
	if (!head)
		return (new);
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (head);
}

t_stack		*stack_to_path(t_stack *stack, int	*nbr)
{
	t_stack	*new;
	t_stack	*tmp0;
	t_stack	*tmp1;

	tmp0 = stack;
	tmp1 = NULL;
	while (tmp0)
	{
		new = (t_stack *)malloc(sizeof(t_stack));
		new->next = NULL;
		new->prev = NULL;
		new->index = tmp0->index;
		if (tmp1)
		{
			tmp1->prev = new;
			new->next = tmp1;
		}

		tmp1 = new;
		*nbr += 1;
		tmp0 = tmp0->prev;
	}
	return (tmp1);
}

t_stack		*push_to_stack(int index, t_stack *stack)
{
	t_stack *new;

	new = (t_stack *)malloc(sizeof(t_stack));
	new->index = index;
	new->next = NULL;
	new->prev = stack;
	if (stack)
		stack->next = new;
	return (new);
}

t_vist		*rom_not_vist(t_vist *vist, t_roms *roms, t_stack *stack, int end)
{
	t_lst	*new;
	t_vist	*nvist;

	nvist = (t_vist *)malloc(sizeof(t_vist));
	nvist->next = NULL;
	nvist->prev = vist;
	if (vist)
	vist->next = nvist;
	nvist->lst = NULL;
	nvist->bck = NULL;
	while (roms)
	{
		if (check_is_vist(roms->index, stack) && check_is_vist2(roms->index, vist))
		{
			new = (t_lst *)malloc(sizeof(t_lst));
			new->index = roms->index;
			new->next = NULL;
			new->prev = NULL;
			if (roms->index == end)
			{
				nvist = free_other_roms(nvist, new);
				break ;
			}
			nvist->lst = push_to_lst(nvist->lst, new);
			nvist->bck = nvist->lst;
		}
		roms = roms->childe;
	}
	if (!nvist->lst)
	{
		free(nvist);
		return (vist);
	}
	return (nvist);
}

t_lst		*push_to_lst(t_lst *head, t_lst *new)
{
	t_lst	*tmp;

	tmp = head;
	if (!head)
		return (new);
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp;
	return (head);
}

int			check_is_vist2(int index, t_vist *vist)
{
	t_vist *tmp;

	tmp = vist;
	while (tmp)
	{
		while (tmp->bck)
		{
			if (tmp->bck->index == index)
				return (0);
			tmp->bck = tmp->bck->next;
		}
		tmp = tmp->prev;
	}
	return (1);
}

int			check_is_vist(int index, t_stack *stack)
{
	t_stack	*tmp;

	tmp = stack;
	if (stack)
	while (tmp)
	{
		if (tmp->index == index)
			return (0);
		tmp = tmp->prev;
	}
	return (1);
}
