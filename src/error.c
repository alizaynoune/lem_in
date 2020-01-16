/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alzaynou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/05 01:38:43 by alzaynou          #+#    #+#             */
/*   Updated: 2020/01/08 01:46:13 by alzaynou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"

void	error_message(char *msg, int n_line)
{
	ft_printf(RED);
	ft_printf("ERROR: [");
	ft_printf(YELLOW);
	if (n_line >= 0)
		ft_printf("line \033[32;1m%d ", n_line);
	ft_printf(YELLOW);
	ft_printf("%s", msg);
	ft_printf(RED);
	ft_printf("]\n");
	ft_printf(DEFAULT);
}

void	error_num_ants(t_lines *lines)
{
	error_message("number of ants <= 0 or not fond it", -1);
	free_lines(lines);
	exit (0);
}

void	error_start_end(t_all data)
{
	free_roms_error(data.roms);
	free_lines(data.lines);
	if (!data.s_end[0] && data.s_end[1])
	{
		error_message("start not fond", -1);
		free_tab(data.s_end, 1);
	}
	else if (!data.s_end[1] && data.s_end[0])
	{
		error_message("end not fond", -1);
		free(data.s_end[0]);
		free(data.s_end);
	}
	else
	{
		error_message("start and end not fond", -1);
		free_tab(data.s_end, 0);
	}
	exit(0);
}

void		error_empty_line(t_all data, int n_line)
{
	free_lines(data.lines);
	free(data.s_end);
	error_message("is empty", n_line);
	exit (0);
}

void		error_many_s_end(t_all data)
{
	free_lines(data.lines);
	free(data.s_end);
	error_message("many start or/and end", -1);
	exit (0);
}

void	error_fille(int error)
{
	error_message(strerror(error), -1);
	exit (0);
}
