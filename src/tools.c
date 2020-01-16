/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alzaynou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/05 21:06:05 by alzaynou          #+#    #+#             */
/*   Updated: 2020/01/10 19:19:07 by alzaynou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"

int		binary_search(t_roms *roms, char *str,  int len)
{
	int start;
	int mid;

	start = 0;
	len--;
	while (start <= len)
	{
		mid = (start + len) / 2;
		if (!ft_strcmp(roms[mid].name, str))
			return (mid);
		if (ft_strcmp(roms[mid].name, str) > 0)
			len = mid - 1;
		else
			start = mid + 1;
	}
	return (-1);
}

int     cnt_char(char *str, char c)
{
	int cnt;
	int c_ch;

	cnt = 0;
	c_ch = 0;
	while (str[cnt])
	{
		if (str[cnt] == c)
			c_ch++;
		cnt++;
	}
	return (c_ch);
}

char	**get_start_end(char *line, char **s_end, char *cmd)
{
	char	**tab;
	int		chk0;
	int		chk1;

	chk0 = ft_strcmp(cmd, "##start");
	chk1 = ft_strcmp(cmd, "##end");
	if (chk0 && chk1)
		return (s_end);
	if (line[0] == 'L' || line[0] == '#' || cnt_char(line, ' ') != 2)
		return (s_end);
	tab = ft_strsplit(line, ' ');
	if (!chk0 && !s_end[0])
		s_end[0] = tab[0];
	if (!chk1 && !s_end[1])
		s_end[1] = tab[0];
	free_tab(tab, 1);
	return (s_end);
}
