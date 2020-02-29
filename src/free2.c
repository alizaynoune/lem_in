/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhossan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 23:33:32 by akhossan          #+#    #+#             */
/*   Updated: 2020/02/12 13:45:35 by alzaynou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	free_start_end(t_start *s_end)
{
	if (s_end->start)
		free(s_end->start);
	if (s_end->end)
		free(s_end->end);
	ft_bzero(s_end, sizeof(t_start));
}

void	free_paths(t_paths *p)
{
	t_paths		*ptr;

	ptr = p;
	while (ptr)
	{
		p = ptr;
		ptr = ptr->next;
		free_one_path(p->p);
		p->p = NULL;
		free(p);
	}
}

void	free_one_path(t_adjp *p)
{
	t_adjp	*ptr;

	ptr = p;
	while (ptr)
	{
		p = ptr;
		ptr = ptr->next;
		free(p);
	}
}

void	error_link(t_data *data, t_graph *g)
{
	free_vertex(g->vertex, g->size);
	ft_strdel(&data->line);
	close(data->fd);
	message_error("Link format");
	exit(1);
}
