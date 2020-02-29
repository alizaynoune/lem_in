/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alzaynou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 15:20:33 by alzaynou          #+#    #+#             */
/*   Updated: 2020/02/11 23:34:33 by akhossan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	free_rooms(t_room *rooms)
{
	t_room		*ptr;
	t_room		*tmp;

	tmp = rooms;
	while (tmp)
	{
		ptr = tmp;
		tmp = tmp->next;
		ft_strdel(&ptr->name);
		free(ptr);
	}
}

void	free_vertex(t_vertex *vertex, uint16_t size)
{
	uint16_t	cnt;
	t_adj		*ptr;
	t_adj		*tmp;

	cnt = 0;
	while (cnt < size)
	{
		tmp = vertex[cnt].adj;
		while (tmp)
		{
			ptr = tmp;
			tmp = tmp->next;
			free(ptr);
		}
		ft_strdel(&vertex[cnt].name);
		cnt++;
	}
	free(vertex);
	vertex = NULL;
}

void	free_tab(char **tab, int8_t start)
{
	int8_t	cnt;

	cnt = start;
	while (tab[cnt])
		ft_strdel(&tab[cnt++]);
	free(tab);
}
