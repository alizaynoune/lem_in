/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alzaynou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 18:42:06 by alzaynou          #+#    #+#             */
/*   Updated: 2019/12/26 19:20:23 by alzaynou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	size_t cnt;

	cnt = 0;
	while (cnt < len && ((char *)src)[cnt] != '\0')
	{
		dst[cnt] = ((char *)src)[cnt];
		cnt++;
	}
	while (cnt < len)
		dst[cnt++] = '\0';
	return (dst);
}
