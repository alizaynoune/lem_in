/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alzaynou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 11:29:04 by alzaynou          #+#    #+#             */
/*   Updated: 2019/12/26 19:18:46 by alzaynou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	U_INT cnt;

	cnt = 0;
	if (s && f)
	{
		while (s[cnt] != '\0')
		{
			(*f)(cnt, &s[cnt]);
			cnt++;
		}
	}
}
