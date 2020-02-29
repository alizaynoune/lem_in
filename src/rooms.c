/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rooms.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alzaynou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 16:07:49 by alzaynou          #+#    #+#             */
/*   Updated: 2020/02/13 16:52:12 by akhossan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lemin.h"

void		get_rooms(t_data *data, t_graph *graph)
{
	while ((data->ret = get_next_line(STDIN, &data->line)) > 0)
	{
		ft_putendl_fd(data->line, data->fd);
		if (!data->line[0])
			error_empty_line(data, NULL);
		if (data->line[0] == 'L')
			error_name_room(data);
		if (data->line[0] == '#' && data->line[1] == '#')
			get_start_end(data);
		if (data->line[0] != '#' && count_words(data->line, ' ') == 3)
			data->rooms = push_room(data, NULL, NULL, NULL);
		else if (ft_strchr(data->line, '-'))
			break ;
		else if (data->line[0] != '#')
			error_name_room(data);
		ft_strdel(&data->line);
	}
	if (!data->rooms)
		error_not_rooms_links(data, 0);
	else if (!data->ret)
		error_not_rooms_links(data, 1);
	if (!data->s_end.start || !data->s_end.end)
		error_start_end(data, NULL, 0);
	room_to_tab(data, graph);
	get_links(data, graph);
}

void		room_to_tab(t_data *data, t_graph *graph)
{
	int		cnt;
	t_room	*tmp;
	t_room	*ptr;

	cnt = 0;
	tmp = data->rooms;
	if (!(graph->vertex = (t_vertex *)ft_memalloc(sizeof(t_vertex)\
		* data->nb_rooms)))
		error_malloc(data, graph);
	while (cnt < data->nb_rooms)
	{
		ptr = tmp;
		graph->vertex[cnt].name = tmp->name;
		graph->vertex[cnt].x = tmp->x;
		graph->vertex[cnt].y = tmp->y;
		graph->vertex[cnt].index = cnt;
		cnt++;
		tmp = tmp->next;
		free(ptr);
	}
	data->rooms = NULL;
	graph->size = data->nb_rooms;
}

t_room		*push_room(t_data *data, char **tab, t_room *new, t_room *tmp)
{
	if (ft_strchr(data->line, '-'))
		return (data->rooms);
	if (!(tab = ft_strsplit(data->line, ' ')))
		error_malloc(data, NULL);
	if (!ft_all_digit(tab[1]) || !ft_all_digit(tab[2]))
		error_coord(data, tab);
	if (data->rooms && !(tmp = get_place_room(data->rooms, tab[0])))
	{
		free_tab(tab, 0);
		return (data->rooms);
	}
	new = make_new_room(data, tab);
	if (!data->rooms)
		return (new);
	if (tmp == data->rooms && ft_strcmp(data->rooms->name, new->name) > 0)
	{
		new->next = data->rooms;
		data->rooms = new;
	}
	else
	{
		new->next = tmp->next;
		tmp->next = new;
	}
	return (data->rooms);
}

t_room		*get_place_room(t_room *rooms, char *name)
{
	t_room	*tmp;

	tmp = rooms;
	if (!ft_strcmp(tmp->name, name))
		return (NULL);
	if (ft_strcmp(tmp->name, name) > 0)
		return (tmp);
	while (tmp)
	{
		if (tmp->next && !ft_strcmp(tmp->next->name, name))
			return (NULL);
		if (tmp->next && ft_strcmp(tmp->next->name, name) > 0)
			return (tmp);
		if (!tmp->next)
			break ;
		tmp = tmp->next;
	}
	return (tmp);
}

t_room		*make_new_room(t_data *data, char **tab)
{
	t_room		*new;

	if (!(new = (t_room *)ft_memalloc(sizeof(t_room))))
	{
		free_tab(tab, 0);
		error_malloc(data, NULL);
	}
	new->name = tab[0];
	new->x = ft_atoi(tab[1]);
	new->y = ft_atoi(tab[2]);
	data->nb_rooms++;
	free_tab(tab, 1);
	if (data->nb_rooms > UINT16_MAX)
	{
		free_rooms(new);
		free_rooms(data->rooms);
		free_start_end(&data->s_end);
		message_error("Too many rooms");
		exit(1);
	}
	return (new);
}
