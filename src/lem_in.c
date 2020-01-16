/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alzaynou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/05 00:22:14 by alzaynou          #+#    #+#             */
/*   Updated: 2020/01/12 18:17:47 by alzaynou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"

int		main()
{
	t_all data;
	int		start;
	int		end;
	data.s_end = (char **)malloc(sizeof(char *) * 3);
	data.s_end[0] = NULL;
	data.s_end[1] = NULL;
	data.s_end[2] = NULL;
	data.lines = NULL;
	data = read_fill(data, NULL, NULL, NULL);
//	print_lines(data.lines);
	if ((data.n_ants = atoi(data.lines->line)) <= 0)
		error_num_ants(data.lines);
	data = get_roms(data, data.lines);
	start = binary_search(data.roms, data.s_end[0], data.n_roms);//
	end = binary_search(data.roms, data.s_end[1], data.n_roms);//
	if (!(data.paths = find_paths(data.roms, NULL, start, end)))//
		error_message("not fond paths from start to end", -1);
//	print_not_vist(data.paths, data.roms);
	print_roms(data.roms, data.n_roms);//
	ft_printf("start=> [%s] end=> [%s]\n", data.s_end[0], data.s_end[1]);
	ft_printf("######n_ants %d n_roms %d ########\n", data.n_ants, data.n_roms);
	free_lines(data.lines);
	free_tab(data.s_end, 0);
	free_p_roms(data.roms, data.n_roms);
	free_paths(data.paths);
}

t_all		read_fill(t_all data, t_lines *new, t_lines *tmp, char *line)
{
	int cnt;
	int ret;
	int	err;

	cnt = 0;
	err = 0;
	while ((ret = get_next_line(0, &line)) > 0)
	{
		if (line[0] != '#' || (line[0] == '#' && (!ft_strcmp(line, "##start") || !ft_strcmp(line, "##end"))))
		{
		new = (t_lines *)malloc(sizeof(t_lines));
		new->line = line;
		new->next = NULL;
		cnt++;
		if (!data.lines)
		{
			data.lines = new;
			tmp = new;
		}
		else
		{
			tmp->next = new;
			tmp = tmp->next;
		}
		if (!line[0])
			error_empty_line(data, cnt);
		if (line[1] == '#' && (!ft_strcmp(line, "##start") || !ft_strcmp(line, "##end")))
			err++;
		if (err > 2)
			error_many_s_end(data);
		}
		else
			free(line);
	}
	if (ret == -1)
		error_fille(errno);
	return (data);
}

t_all		get_roms(t_all data, t_lines *tmp)
{
	data.n_roms = 0;
	while (tmp)
	{
		if (tmp->line[0] != '#' && tmp->line[0] != 'L' && cnt_char(tmp->line, ' ') == 2)
			data.roms = push_roms(data.roms, tmp->line, &data.n_roms);
		else if (tmp->line[0] != '#' && ft_strchr(tmp->line, '-'))
			break ;
		if (tmp->line[0] == '#' && tmp->line[1] == '#' && tmp->next)
			data.s_end = get_start_end(&*tmp->next->line, data.s_end, &*tmp->line);
		tmp = tmp->next;
	}
	if (!data.s_end[0] || !data.s_end[1])
		error_start_end(data);
	data.roms = stock_roms(data.roms, data.n_roms, data.roms);
	data.roms = sort_roms(data.roms, data.n_roms);
	data.roms = find_links(data.roms, tmp, data.n_roms);//
	return (data);
}

t_roms		*push_roms(t_roms *roms, char *line, int *nbr)
{
	t_roms	*new;
	char	**tab;

	tab = ft_strsplit(line, ' ');
	new = (t_roms *)malloc(sizeof(t_roms));
	new->name = tab[0];
	new->childe = roms;
	*nbr += 1;
	free_tab(tab, 1);
	return (new);
}

t_roms		*stock_roms(t_roms *roms, int n_roms, t_roms *tmp)
{
	t_roms	*p_roms;
	int		cnt;

	cnt = 0;
	p_roms = (t_roms *)malloc(sizeof(t_roms) * n_roms);
	while (tmp)
	{
		p_roms[cnt].name = tmp->name;
		p_roms[cnt++].childe = NULL;
		tmp = tmp->childe;
	}
	free_roms(roms);
	return (p_roms);
}

t_roms		*sort_roms(t_roms *roms, int len)
{
	int		cnt1;
	int		cnt2;
	char	*bck;

	cnt1 = 0;
	while (cnt1 < len)
	{
		cnt2 = cnt1 + 1;
		while (cnt2 < len)
		{
			if (ft_strcmp(roms[cnt1].name, roms[cnt2].name) > 0)
			{
				bck = roms[cnt1].name;
				roms[cnt1].name = roms[cnt2].name;
				roms[cnt2].name = bck;
			}
			cnt2++;
		}
		cnt1++;
	}
	return (roms);
}

t_roms		*find_links(t_roms *roms, t_lines *lines, int n_roms)
{
	char	**tab;
	int		tmp0 = 0;
	int		tmp1 = 0;

	while (lines)
	{
		if (lines->line[0] != '#' && cnt_char(lines->line, '-') == 1)
		{
			tab = ft_strsplit(lines->line, '-');
			tmp0 = binary_search(roms, tab[0], n_roms);
			tmp1 = binary_search(roms, tab[1], n_roms);
			//if (!(check_is_pushed(roms, tmp0, tmp1))
			if (tmp0 != tmp1 && tmp0 >= 0 && tmp1 >= 0 && check_is_pushed(roms, tmp0, tmp1))
				roms = push_links(roms, tab, tmp0, tmp1);
			else
				free_tab(tab, 0);
		}
		lines = lines->next;
	}
	return (roms);
}

int		check_is_pushed(t_roms *roms, int tmp0, int tmp1)
{
	t_roms	*tmp;

	tmp = roms[tmp0].childe;
	//ft_printf("==[%s]==[%s]\n", roms[tmp0].name, roms[tmp1].name);
	while (tmp)
	{
		if (tmp->index == tmp1)
		{
	//		ft_printf("==[%s]==[%s]==[%s]\n", roms[tmp->index].name, roms[tmp1].name, roms[tmp0].name);
			return (0);
		}
		tmp = tmp->childe;
	}
	return (1);
}

t_roms		*push_links(t_roms *roms, char **tab, int tmp0, int tmp1)
{
	t_roms	*tmp;
	t_roms	*new;

	tmp = &roms[tmp0];
	while (tmp->childe)
		tmp = tmp->childe;
	new = (t_roms *)malloc(sizeof(t_roms));
	new->name = tab[1];
	new->index = tmp1;
	new->childe = NULL;
	tmp->childe = new;
	tmp = &roms[tmp1];
	while (tmp->childe)
		tmp = tmp->childe;
	new = (t_roms *)malloc(sizeof(t_roms));
	new->name = tab[0];
	new->index = tmp0;
	new->childe = NULL;
	tmp->childe = new;
	free(tab);
	return (roms);
}
