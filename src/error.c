/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alzaynou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 15:10:21 by alzaynou          #+#    #+#             */
/*   Updated: 2020/02/12 08:17:18 by alzaynou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	message_error(char *str)
{
	ft_printf("%sERROR: [%s%s%s]%s\n", RED, YELLOW, str, RED, DEFAULT);
}

void	error_file(t_data *data)
{
	message_error(strerror(data->err));
	close(data->fd);
	exit(1);
}

void	error_empty_line(t_data *data, t_graph *graph)
{
	message_error("Empty line");
	ft_strdel(&data->line);
	if (data->rooms)
		free_rooms(data->rooms);
	if (graph && graph->vertex)
		free_vertex(graph->vertex, graph->size);
	free_start_end(&data->s_end);
	close(data->fd);
	exit(1);
}

void	error_ants(t_data *data)
{
	ft_strdel(&data->line);
	message_error("Number of ants <= 0 or not found");
	close(data->fd);
	exit(1);
}

void	error_name_room(t_data *data)
{
	message_error("Name of room");
	ft_strdel(&data->line);
	free_start_end(&data->s_end);
	if (data->rooms)
		free_rooms(data->rooms);
	close(data->fd);
	exit(1);
}
