/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhossan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 23:33:07 by akhossan          #+#    #+#             */
/*   Updated: 2020/02/11 23:33:13 by akhossan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int		force_redirect(t_vertex *v, uint16_t from, uint16_t index)
{
	t_adj	*tmp;

	tmp = v[from].adj;
	while (tmp)
	{
		if (tmp->index == index)
		{
			if (tmp->flow == 2)
				return (1);
			break ;
		}
		tmp = tmp->next;
	}
	tmp = v[index].adj;
	while (tmp)
	{
		if (tmp->flow == 2 && !v[tmp->index].visited)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void	update_flow(t_vertex *v, t_queue *q, uint16_t curr)
{
	int		from;
	t_adj	*tmp;

	from = q[curr].from;
	while (from >= 0)
	{
		v[q[from].index].used = 1;
		tmp = v[q[from].index].adj;
		update_flow2(tmp, q[curr].index, -1);
		tmp = v[q[curr].index].adj;
		update_flow2(tmp, q[from].index, 1);
		curr = from;
		from = q[curr].from;
	}
}

void	update_flow2(t_adj *adj, uint16_t index, int plus)
{
	while (adj)
	{
		if (adj->index == index)
		{
			adj->flow += plus;
			break ;
		}
		adj = adj->next;
	}
}

void	reset_visited(t_vertex *v, t_queue *q, uint16_t len)
{
	uint16_t	cnt;

	cnt = 0;
	while (cnt < len)
		v[q[cnt++].index].visited = 0;
}
