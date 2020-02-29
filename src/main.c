/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alzaynou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 23:48:41 by alzaynou          #+#    #+#             */
/*   Updated: 2020/02/13 23:10:11 by akhossan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lemin.h"

static void	print_usage(void)
{
	ft_printf("Usage: \n");
	ft_printf("./lem-in [-A ANTS_NUMBER] [-p]\n");
	ft_printf("ANTS_NUMBER should be strictly greater than 0.\n");
	exit(1);
}

static void	parse_args(t_graph *g, int ac, char **av, int *print_flg)
{
	int		i;
	int		ants;

	*print_flg = 0;
	i = 1;
	while (i < ac)
	{
		if (ft_strcmp(av[i], "-A") == 0)
		{
			if (i == ac - 1 || (ants = ft_atoi_all(av[i + 1])) <= 0)
				print_usage();
			g->ants = ants;
			i++;
		}
		else if (ft_strcmp(av[i], "-p") == 0)
			*print_flg = 1;
		else
			print_usage();
		i++;
	}
}

int			main(int ac, char **av)
{
	t_data		data;
	t_graph		graph;
	t_paths		*paths;
	int			print_flg;

	paths = NULL;
	ft_bzero(&data, sizeof(t_data));
	ft_bzero(&graph, sizeof(t_graph));
	ft_bzero(&data.s_end, sizeof(t_start));
	data.fd = open(".tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	graph.ants = get_nb_ants(&data);
	parse_args(&graph, ac, av, &print_flg);
	get_rooms(&data, &graph);
	paths = edmond_karp_max_flow(&graph, &data);
	if (!paths)
		error_path(&graph, &data);
	sum_and_remove(graph.ants, paths);
	printf_file(&data);
	move_ants(&graph, paths);
	print_flg ? print_paths(&graph, paths) : 0;
	free_vertex(graph.vertex, graph.size);
	free_paths(paths);
	close(data.fd);
}
