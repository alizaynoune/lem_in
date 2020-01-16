/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alzaynou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/05 17:52:45 by alzaynou          #+#    #+#             */
/*   Updated: 2020/01/09 22:00:41 by alzaynou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"

t_vist		*free_other_roms(t_vist *nvist, t_lst *new)
{
	t_lst	*tmp0;
	t_lst	*tmp1;

	tmp0 = nvist->lst;
	while (tmp0)
	{
		tmp1 = tmp0;
		tmp0 = tmp0->next;
		free(tmp1);
	}
	nvist->lst = new;
	nvist->bck = new;
	return (nvist);
}

t_stack		*free_stack(t_stack *stack)
{
	t_stack *tmp;

	tmp = stack;
	stack = stack->prev;
	free(tmp);
	return (stack);
}

t_vist		*free_vist(t_vist *vist)
{
	t_vist	*tmp;
	t_vist	*ret;
	t_lst	*lst;
	t_lst   *tlst;

	if (vist)
		ret = vist->prev;
	if (ret)
		ret->next = NULL;
	while (vist)
	{
		lst = vist->bck;
		while (lst)
		{
			tlst = lst;
			lst = lst->next;
			free(tlst);
		}
		tmp = vist;
		vist = vist->next;;
		free(tmp);
	}
	return (ret);
}

void		free_paths(t_paths *path)
{
	t_stack	*lst;
	t_paths	*tmp;
	t_stack	*tlst;

	while (path)
	{
		tmp = path;
		lst = path->path;
		while (lst)
		{
			tlst = lst;
			lst = lst->next;
			free(tlst);
		}
		path = path->next;
		free(tmp);
	}
}

void		free_p_roms(t_roms *roms, int len)
{
	t_roms	*tmp;
	t_roms	*tmp1;
	int		cnt;

	cnt = 0;
	while (cnt < len)
	{
		tmp = roms[cnt].childe;
		tmp1 = roms[cnt].childe;
		free(roms[cnt].name);
		while (tmp)
		{
			if (tmp1)
				tmp1 = tmp1->childe;
			free(tmp->name);
			free(tmp);
			tmp = tmp1;
		}
		cnt++;
	}
	free(roms);
}

void		free_lines(t_lines *lines)
{
	t_lines *tmp;

	while (lines)
	{
		tmp = lines;
		lines = lines->next;
		free(tmp->line);
		free(tmp);
	}
}

void		free_tab(char **tab, int start)
{
	while (tab && tab[start])
		free(tab[start++]);
	free(tab);
}

void		free_roms(t_roms *roms)
{
	t_roms *tmp;

	tmp = roms;
	while (tmp)
	{
		if (roms)
			roms = roms->childe;
		free(tmp);
		tmp = roms;
	}
}

void        free_roms_error(t_roms *roms)
{
	t_roms *tmp;

	tmp = roms;
	while (tmp)
	{
		if (roms)
			roms = roms->childe;
		free(tmp->name);
		free(tmp);
		tmp = roms;
	}

}
