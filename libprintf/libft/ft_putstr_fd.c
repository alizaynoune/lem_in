/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alzaynou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 22:33:40 by alzaynou          #+#    #+#             */
/*   Updated: 2019/12/26 19:13:33 by alzaynou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_putstr_fd(char const *s, int fd)
{
	size_t cnt;

	if (s)
	{
		cnt = ft_strlen(s);
		write(fd, (const void *)s, cnt);
	}
}
