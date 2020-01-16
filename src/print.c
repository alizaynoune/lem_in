/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alzaynou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/05 00:41:13 by alzaynou          #+#    #+#             */
/*   Updated: 2020/01/09 00:46:08 by alzaynou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"

void	print_lines(t_lines *lines)
{
	t_lines *tmp;
	tmp = lines;
	while (tmp)
	{
		ft_printf("%s\n", tmp->line);
		tmp = tmp->next;
	}
}

void	print_roms(t_roms *roms, int n)
{
	int cnt = 0;
	t_roms *tmp;
	while (cnt < n)
	{
		tmp = roms[cnt].childe;
		if (!roms[cnt].childe)
			ft_printf("NULL");
		ft_printf("[%s]", roms[cnt].name);
		while(tmp)
		{
			ft_printf(" => [%s]", tmp->name);
			tmp = tmp->childe;
		}
		cnt++;
		ft_printf("\n");
	}
}

void    print_not_vist(t_paths *lst, t_roms *roms)
{
	t_stack *tmp;
	t_paths *tmp1;
	tmp1 = lst;
	while (tmp1)
	{
		tmp = tmp1->path;
		while (tmp)
		{
			ft_printf("[%s]=>", roms[tmp->index].name);
			tmp = tmp->next;
		}
		ft_printf(" %d \n", tmp1->n_roms);
		tmp1 = tmp1->next;
	}
}

