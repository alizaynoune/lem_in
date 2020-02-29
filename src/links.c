/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   links.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alzaynou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 20:25:40 by alzaynou          #+#    #+#             */
/*   Updated: 2020/02/12 13:51:07 by alzaynou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	get_links(t_data *data, t_graph *graph)
{
	graph->start = binary_search(graph->vertex, data->s_end.start, graph->size);
	graph->end = binary_search(graph->vertex, data->s_end.end, graph->size);
	if (graph->start == graph->end)
		error_start_end(data, graph, 2);
	free_start_end(&data->s_end);
	if (count_words(data->line, '-') == 2)
		ft_count_char(data->line, '-') > 1 ? error_link(data, graph)\
			: search_link(data, graph);
	ft_strdel(&data->line);
	while (get_next_line(STDIN, &data->line) > 0)
	{
		if (!data->line[0])
			error_empty_line(data, graph);
		if (data->line[0] != '#' && count_words(data->line, '-') == 2)
			ft_count_char(data->line, '-') > 1 ? error_link(data, graph)\
				: search_link(data, graph);
		else if (data->line[0] != '#' && !ft_strchr(data->line, '-'))
		{
			ft_strdel(&data->line);
			break ;
		}
		ft_putendl_fd(data->line, data->fd);
		ft_strdel(&data->line);
	}
}

void	push_link(t_data *data, t_graph *graph, int index1, int index2)
{
	t_adj	*tmp;
	t_adj	*new;

	if ((!graph->vertex[index1].adj) || (graph->vertex[index1].adj &&
				(tmp = get_place_link(graph->vertex[index1].adj, index2))))
		new = make_new_link(index2, data, graph);
	else if (graph->vertex[index1].adj && !tmp)
		return ;
	if (!graph->vertex[index1].adj && new)
		graph->vertex[index1].adj = new;
	else
		push_link2(&graph->vertex[index1], tmp, new);
	if ((!graph->vertex[index2].adj) || (graph->vertex[index2].adj &&
				(tmp = get_place_link(graph->vertex[index2].adj, index1))))
		new = make_new_link(index1, data, graph);
	else if (graph->vertex[index2].adj && !tmp)
		return ;
	if (!graph->vertex[index2].adj)
		graph->vertex[index2].adj = new;
	else
		push_link2(&graph->vertex[index2], tmp, new);
}

void	push_link2(t_vertex *vertex, t_adj *tmp, t_adj *new)
{
	if (tmp == vertex->adj && vertex->adj->index > new->index)
	{
		new->next = vertex->adj;
		vertex->adj = new;
	}
	else
	{
		new->next = tmp->next;
		tmp->next = new;
	}
}

t_adj	*get_place_link(t_adj *adj, int index)
{
	t_adj	*tmp;

	tmp = adj;
	if (tmp->index == index)
		return (NULL);
	while (tmp)
	{
		if (tmp->next && tmp->next->index == index)
			return (NULL);
		if (tmp->next && tmp->next->index > index)
			return (tmp);
		if (!tmp->next)
			break ;
		tmp = tmp->next;
	}
	return (tmp);
}

t_adj	*make_new_link(int index, t_data *data, t_graph *graph)
{
	t_adj	*new;

	if (!(new = (t_adj *)ft_memalloc(sizeof(t_adj))))
		error_malloc(data, graph);
	new->flow = 1;
	new->index = index;
	return (new);
}
