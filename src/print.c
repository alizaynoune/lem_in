/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alzaynou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 18:49:40 by alzaynou          #+#    #+#             */
/*   Updated: 2020/02/13 23:36:14 by akhossan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void		printf_file(t_data *d)
{
	close(d->fd);
	d->fd = open(".tmp", O_RDONLY);
	while (get_next_line(d->fd, &d->line) > 0)
	{
		ft_printf("%s\n", d->line);
		ft_strdel(&d->line);
		ft_strdel(&d->line);
	}
	ft_printf("\n");
	close(d->fd);
}

void		print_paths(t_graph *g, t_paths *p)
{
	t_adjp	*path;

	ft_printf("\n");
	while (p)
	{
		path = p->p;
		if (p->ants_cpy)
		{
			ft_printf("%s[%d]: ", GREEN, p->ants_cpy);
			while (path)
			{
				ft_printf("(%s)", g->vertex[path->index].name);
				if (path->next)
					ft_printf("==>");
				path = path->next;
			}
			ft_printf("\n");
		}
		p = p->next;
	}
	ft_printf("%s", DEFAULT);
}

void		reset_used(t_vertex *v, t_queue *q, uint16_t len)
{
	uint16_t	cnt;

	cnt = 0;
	while (cnt < len)
		v[q[cnt++].index].used2 = 0;
}
