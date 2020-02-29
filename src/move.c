/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alzaynou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 21:21:31 by alzaynou          #+#    #+#             */
/*   Updated: 2020/02/12 15:46:44 by alzaynou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lemin.h"

static void	move_helper(t_graph *g, t_adjp *tmp, int *done)
{
	if (tmp->index == g->end && tmp->prev->ant_index)
	{
		*done += 1;
		tmp->ant_index = tmp->prev->ant_index;
		g->middle ? ft_printf(" ") : 0;
		ft_printf("L%d-%s", tmp->ant_index, g->vertex[tmp->index].name);
		!g->middle ? g->middle = 1 : 0;
	}
	else
	{
		tmp->ant_index = tmp->prev->ant_index;
		if (tmp->ant_index)
		{
			g->middle ? ft_printf(" ") : 0;
			ft_printf("L%d-%s", tmp->ant_index, g->vertex[tmp->index].name);
			!g->middle ? g->middle = 1 : 0;
		}
	}
}

static void	move_in_paths(t_graph *g, t_paths *p, int *ant, int *done)
{
	t_adjp		*tmp;

	tmp = p->last;
	p->last = p->last->next ? p->last->next : p->last;
	while (tmp)
	{
		if (tmp->index == g->start)
		{
			if (p->ants)
			{
				p->ants--;
				tmp->next->ant_index = *ant;
				g->middle ? ft_printf(" ") : 0;
				ft_printf("L%d-%s", *ant, g->vertex[tmp->next->index].name);
				!g->middle ? g->middle = 1 : 0;
				*ant += 1;
			}
			break ;
		}
		else
			move_helper(g, tmp, done);
		tmp = tmp->prev;
	}
}

static void	first_move(t_graph *g, t_paths *p, int *ant, int *done)
{
	if (p->ants)
	{
		p->ants--;
		p->last->ant_index = *ant;
		g->middle ? ft_printf(" ") : 0;
		ft_printf("L%d-%s", *ant, g->vertex[p->last->index].name);
		!g->middle ? g->middle = 1 : 0;
		*ant += 1;
		p->last->index == g->end ? *done += 1 : 0;
		while (p->last->index == g->end && *done < g->ants)
		{
			ft_printf(" L%d-%s", *ant, g->vertex[p->last->index].name);
			*ant += 1;
			*done += 1;
		}
		p->last = p->last->next ? p->last->next : p->last;
	}
}

void		move_ants(t_graph *g, t_paths *p)
{
	t_paths		*tmp;
	int			ant;
	int			done;

	ant = 1;
	done = 0;
	while (done < g->ants)
	{
		g->middle = 0;
		tmp = p;
		while (tmp)
		{
			if (tmp->last->prev->index == g->start)
				first_move(g, tmp, &ant, &done);
			else
				move_in_paths(g, tmp, &ant, &done);
			tmp = tmp->next;
		}
		ft_printf("\n");
	}
}
