/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhossan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 23:36:06 by akhossan          #+#    #+#             */
/*   Updated: 2020/02/12 13:53:24 by alzaynou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	push_to_q(t_queue *q, t_graph *g, uint16_t curr, uint16_t *lq)
{
	t_adj	*tmp;

	tmp = g->vertex[q[curr].index].adj;
	while (tmp)
	{
		if (!tmp->flow && !g->vertex[tmp->index].used2 &&\
			tmp->flow2 <= g->up_flow)
		{
			q[*lq].index = tmp->index;
			q[*lq].from = curr;
			g->vertex[tmp->index].used2 = 1;
			*lq += 1;
		}
		tmp = tmp->next;
	}
}

void	search_link(t_data *data, t_graph *graph)
{
	int		index1;
	int		index2;
	char	**tab;

	if (!(tab = ft_strsplit(data->line, '-')))
		error_malloc(data, graph);
	index1 = binary_search(graph->vertex, tab[0], graph->size);
	index2 = binary_search(graph->vertex, tab[1], graph->size);
	free_tab(tab, 0);
	if (index1 == index2 || index1 == -1 || index2 == -1)
		return ;
	push_link(data, graph, index1, index2);
}

void	error_coord(t_data *data, char **tab)
{
	message_error("Wrong coordinates");
	close(data->fd);
	free_tab(tab, 0);
	free_rooms(data->rooms);
	free_start_end(&data->s_end);
	exit(1);
}
