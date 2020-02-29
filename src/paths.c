/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alzaynou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 06:14:09 by alzaynou          #+#    #+#             */
/*   Updated: 2020/02/11 23:37:22 by akhossan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lemin.h"

void		get_paths(t_graph *g, t_data *d, t_paths **p)
{
	t_queue		*q;

	if (!(q = (t_queue *)ft_memalloc(sizeof(t_queue) * g->size)))
		error_malloc2(*p, g, NULL, d);
	while (1)
	{
		ft_bzero(q, sizeof(t_queue));
		q[0].index = g->start;
		q[0].from = -1;
		g->vertex[g->start].used2 = 1;
		if (!bfs_get_path(g, &*p, q, d))
			break ;
	}
	free(q);
}

int			bfs_get_path(t_graph *g, t_paths **p, t_queue *q, t_data *d)
{
	t_adjp		*newp;
	uint16_t	curr;
	uint16_t	lq;
	uint16_t	lp;

	curr = 0;
	lq = 1;
	lp = 0;
	while (curr < lq)
	{
		if (q[curr].index == g->end)
		{
			reset_used(g->vertex, q, lq);
			if (!(newp = get_path(q, g, curr, &lp)))
				error_malloc2(*p, g, q, d);
			if (!(push_path(newp, p, lp)))
				error_malloc2(*p, g, q, d);
			return (1);
		}
		push_to_q(q, g, curr++, &lq);
	}
	reset_used(g->vertex, q, lq);
	return (0);
}

static void	update_flow3(t_adj *adj, uint16_t index, int plus)
{
	while (adj)
	{
		if (adj->index == index)
		{
			adj->flow2 += plus;
			break ;
		}
		adj = adj->next;
	}
}

t_adjp		*get_path(t_queue *q, t_graph *g, uint16_t curr, uint16_t *lp)
{
	t_adjp		*new;
	t_adjp		*head;

	head = NULL;
	while (curr >= 0)
	{
		if (!(new = (t_adjp *)ft_memalloc(sizeof(t_adjp))))
			return (NULL);
		new->index = q[curr].index;
		if (q[curr].index != g->end)
			g->vertex[q[curr].index].used2 = 1;
		new->next = head;
		if (head)
			head->prev = new;
		head = new;
		*lp += 1;
		if (q[curr].from == -1)
		{
			update_flow3(g->vertex[q[0].index].adj, q[curr].index, 1);
			break ;
		}
		update_flow3(g->vertex[q[q[curr].from].index].adj, q[curr].index, 1);
		curr = q[curr].from;
	}
	return (head);
}

int			push_path(t_adjp *new, t_paths **p, uint16_t lp)
{
	t_paths		*newp;
	t_paths		*tmp;

	tmp = *p;
	if (!(newp = (t_paths *)ft_memalloc(sizeof(t_paths))))
	{
		free_one_path(new);
		return (0);
	}
	newp->lp = lp;
	newp->p = new;
	while (tmp && tmp->next)
		tmp = tmp->next;
	if (tmp)
		tmp->next = newp;
	else if (!*p)
		*p = newp;
	return (1);
}
