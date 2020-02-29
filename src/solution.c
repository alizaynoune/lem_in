/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solution.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alzaynou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 21:39:20 by alzaynou          #+#    #+#             */
/*   Updated: 2020/02/12 14:41:58 by alzaynou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lemin.h"

int				cnt_ants(t_paths *p, int ant, int n_p, uint16_t lp)
{
	t_paths		*tmp;
	int			cnt;

	tmp = p;
	cnt = 0;
	while (cnt < n_p)
	{
		ant = ant - (lp - (tmp->lp - 2));
		tmp->ants = lp - (tmp->lp - 2);
		tmp = tmp->next;
		cnt++;
	}
	return (ant);
}

uint16_t		sum_step(int ants, t_paths *p)
{
	int		sum;
	int		n_p;
	t_paths	*tmp;
	int		ant;

	tmp = p;
	n_p = 1;
	while (tmp)
	{
		ant = cnt_ants(p, ants, n_p, tmp->lp - 2);
		sum = (ant / n_p) + tmp->lp - 2;
		tmp = tmp->next;
		if (!tmp || (tmp && sum < (tmp->lp - 2)))
			break ;
		n_p++;
	}
	return (sum);
}

void			sum_and_remove(int ants, t_paths *p)
{
	int			sum;
	int			n_p;
	int			ant;
	t_paths		*tmp;

	tmp = p;
	n_p = 0;
	while (tmp)
	{
		n_p++;
		tmp->last = tmp->p->next;
		ant = cnt_ants(p, ants, n_p, tmp->lp - 2);
		sum = (ant / n_p) + tmp->lp - 2;
		if (tmp->next && sum < (tmp->next->lp - 2))
		{
			free_paths(tmp->next);
			tmp->next = NULL;
			break ;
		}
		tmp = tmp->next;
	}
	add_ants_in_paths(p, ant / n_p, 1);
	add_ants_in_paths(p, ant % n_p, 0);
}

void			add_ants_in_paths(t_paths *p, int ants, int job)
{
	t_paths		*tmp;

	tmp = p;
	while (tmp && ants)
	{
		if (job == 1)
			tmp->ants += ants;
		else if (!job)
		{
			tmp->ants += 1;
			ants--;
		}
		tmp->ants_cpy = tmp->ants;
		tmp = tmp->next;
	}
}
