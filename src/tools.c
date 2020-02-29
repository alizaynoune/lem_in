/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alzaynou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 15:03:30 by alzaynou          #+#    #+#             */
/*   Updated: 2020/02/13 23:36:20 by akhossan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lemin.h"

int		is_comment(char *s)
{
	if (*s == '#')
	{
		if (*(s + 1) != '#')
			return (1);
		else if (!ft_strcmp(s, START) || !ft_strcmp(s, END))
			return (0);
		return (1);
	}
	return (0);
}

int		get_nb_ants(t_data *data)
{
	int		ants;

	while ((data->ret = get_next_line(STDIN, &data->line)) > 0)
	{
		ft_putendl_fd(data->line, data->fd);
		if (!data->line[0])
			error_empty_line(data, NULL);
		if (!is_comment(data->line))
			break ;
		ft_strdel(&data->line);
	}
	if (data->ret == 0)
	{
		message_error("Empty file");
		exit(1);
	}
	if (data->ret == -1 && (data->err = errno))
		error_file(data);
	ants = ft_atoi_all(data->line);
	ants <= 0 ? error_ants(data) : 0;
	ft_strdel(&data->line);
	return (ants);
}

void	get_start_end(t_data *data)
{
	int	start;
	int	end;

	remove_last_sapce(data->line);
	start = ft_strcmp(data->line, START);
	end = ft_strcmp(data->line, END);
	if (start && end)
		return ;
	ft_strdel(&data->line);
	while (get_next_line(STDIN, &data->line) > 0)
	{
		ft_putendl_fd(data->line, data->fd);
		if (!data->line[0])
			error_empty_line(data, NULL);
		if (data->line[0] == 'L')
			error_name_room(data);
		if (data->line[0] != '#')
			break ;
		ft_strdel(&data->line);
	}
	if (count_words(data->line, ' ') == 3)
		get_start_end2(data, start, end);
	else
		error_name_room(data);
}

void	get_start_end2(t_data *data, int start, int end)
{
	char	**tab;

	if (!start && data->s_end.start)
		error_start_end(data, NULL, 1);
	if (!end && data->s_end.end)
		error_start_end(data, NULL, 1);
	if (!(tab = ft_strsplit(data->line, ' ')))
		error_malloc(data, NULL);
	if (!start)
		data->s_end.start = tab[0];
	if (!end)
		data->s_end.end = tab[0];
	free_tab(tab, 1);
}

int		binary_search(t_vertex *vertex, char *str, uint16_t size)
{
	uint16_t	min;
	uint16_t	mid;
	int			cmp;

	min = 0;
	size--;
	while (min <= size)
	{
		mid = (min + size) / 2;
		if (!(cmp = ft_strcmp(vertex[mid].name, str)))
			return (mid);
		if (cmp > 0 && mid)
			size = mid - 1;
		else
			min = mid + 1;
	}
	return (-1);
}
