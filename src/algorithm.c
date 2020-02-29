/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alzaynou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 23:20:23 by alzaynou          #+#    #+#             */
/*   Updated: 2020/02/12 10:31:30 by alzaynou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_paths	*edmond_karp_max_flow(t_graph *g, t_data *d)
{
	t_queue		*q;
	uint16_t	curr;
	uint16_t	lq;
	t_paths		*p;
	uint16_t	step;

	p = NULL;
	step = 0;
	if (!(q = (t_queue *)ft_memalloc(sizeof(t_queue) * (g->size))))
		error_malloc2(NULL, g, NULL, d);
	while (bfs_short_path(g, q, &curr, &lq))
	{
		update_flow(g->vertex, q, curr);
		reset_visited(g->vertex, q, lq);
		get_prefect_paths(&p, g, d, &step);
		g->up_flow++;
		if (p->lp == 2)
			break ;
	}
	free(q);
	return (p);
}

void	reset_paths_used(t_graph *g)
{
	uint16_t	cnt;

	cnt = 0;
	while (cnt < g->size)
		g->vertex[cnt++].used2 = 0;
}

void	get_prefect_paths(t_paths **p, t_graph *g, t_data *d, uint16_t *stp)
{
	t_paths		*p2;
	uint16_t	stp2;

	p2 = NULL;
	reset_paths_used(g);
	get_paths(g, d, &p2);
	stp2 = sum_step(g->ants, p2);
	if (!*p)
	{
		*p = p2;
		*stp = stp2;
	}
	else if (stp2 < *stp)
	{
		free_paths(*p);
		*p = p2;
		*stp = stp2;
	}
	if (stp2 >= *stp && p2 != *p)
		free_paths(p2);
}

int		bfs_short_path(t_graph *g, t_queue *q, uint16_t *curr, uint16_t *lq)
{
	uint16_t	cnt;
	uint16_t	last;

	cnt = 0;
	last = 1;
	q[0].index = g->start;
	q[0].from = -1;
	g->vertex[g->start].visited = 1;
	g->vertex[g->start].used = 1;
	while (cnt < last)
	{
		if (q[cnt].index == g->end)
		{
			*lq = last;
			*curr = cnt;
			return (1);
		}
		push_to_queue(q, g->vertex, cnt, &last);
		cnt++;
	}
	return (0);
}

void	push_to_queue(t_queue *q, t_vertex *v, uint16_t from, uint16_t *last)
{
	t_adj	*tmp;
	int		cnt;

	tmp = v[q[from].index].adj;
	cnt = 0;
	while (tmp)
	{
		if (!v[tmp->index].visited && tmp->flow && (!v[tmp->index].used ||
					force_redirect(v, q[from].index, tmp->index)))
		{
			q[*last].index = tmp->index;
			q[*last].from = from;
			v[tmp->index].visited = 1;
			*last += 1;
			cnt++;
		}
		tmp = tmp->next;
	}
}
