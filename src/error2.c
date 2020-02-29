/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhossan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 23:30:38 by akhossan          #+#    #+#             */
/*   Updated: 2020/02/12 13:35:35 by alzaynou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	error_malloc(t_data *data, t_graph *graph)
{
	message_error("Malloc can't allocate (-_-)");
	ft_strdel(&data->line);
	if (data->rooms)
		free_rooms(data->rooms);
	if (graph && graph->vertex)
		free_vertex(graph->vertex, graph->size);
	free_start_end(&data->s_end);
	close(data->fd);
	exit(1);
}

void	error_not_rooms_links(t_data *data, int8_t err)
{
	ft_strdel(&data->line);
	if (!err)
		message_error("No Rooms");
	else if (err == 1)
	{
		message_error("No links");
		free_rooms(data->rooms);
		free_start_end(&data->s_end);
	}
	close(data->fd);
	exit(1);
}

void	error_malloc2(t_paths *p, t_graph *g, t_queue *q, t_data *d)
{
	message_error("Malloc can't allocate (-_-)");
	free_vertex(g->vertex, g->size);
	if (p)
		free_paths(p);
	if (q)
		free(q);
	close(d->fd);
	exit(1);
}

void	error_start_end(t_data *data, t_graph *graph, int err)
{
	if (err == 1)
	{
		ft_strdel(&data->line);
		message_error("Two start/end's rooms");
	}
	else if (err == 0)
		message_error("start and/or end not found");
	else if (err == 2)
	{
		free_vertex(graph->vertex, graph->size);
		message_error("Start collides with End");
	}
	if (data->rooms)
		free_rooms(data->rooms);
	free_start_end(&data->s_end);
	close(data->fd);
	exit(1);
}

void	error_path(t_graph *graph, t_data *data)
{
	free_vertex(graph->vertex, graph->size);
	close(data->fd);
	message_error("No path from start to end");
	exit(1);
}
