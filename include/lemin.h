/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alzaynou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/19 23:58:56 by alzaynou          #+#    #+#             */
/*   Updated: 2020/02/13 23:10:56 by akhossan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H
# include <fcntl.h>
# include <errno.h>
# include "../libprintf/includes/ft_printf.h"

/*
** Macros
*/
# define STDIN		(0)
# define START		("##start")
# define END		("##end")
# define DEFAULT	("\e[0m")
# define RED		("\e[31;1m")
# define GREEN		("\e[32;1m")
# define YELLOW		("\e[33;1m")

/*
** Structs
*/

typedef struct		s_start
{
	char			*start;
	char			*end;
}					t_start;

typedef struct		s_adj
{
	uint16_t		index;
	struct s_adj	*next;
	int8_t			flow;
	uint32_t		flow2;
}					t_adj;

typedef struct		s_vertex
{
	char			*name;
	uint16_t		index;
	int16_t			x;
	int16_t			y;
	int8_t			visited;
	int8_t			used;
	int8_t			used2;
	t_adj			*adj;
}					t_vertex;

typedef struct		s_graph
{
	t_vertex		*vertex;
	int				ants;
	uint16_t		size;
	uint16_t		start;
	uint16_t		end;
	uint32_t		up_flow;
	int				middle;
}					t_graph;

typedef struct		s_room
{
	char			*name;
	int				x;
	int				y;
	struct s_room	*next;
}					t_room;

typedef struct		s_data
{
	int				fd;
	char			*line;
	int8_t			ret;
	int				err;
	t_start			s_end;
	int				nb_rooms;
	t_room			*rooms;
}					t_data;

typedef struct		s_adjp
{
	uint16_t		index;
	int				ant_index;
	struct s_adjp	*next;
	struct s_adjp	*prev;
}					t_adjp;

typedef struct		s_paths
{
	uint16_t		lp;
	int				ants;
	int				ants_cpy;
	t_adjp			*p;
	t_adjp			*last;
	struct s_paths	*next;
}					t_paths;

typedef struct		s_queue
{
	uint16_t		index;
	int				from;
}					t_queue;

/*
** Functions prototypes
*/

int					get_nb_ants(t_data *data);
void				free_rooms(t_room *rooms);
void				free_vertex(t_vertex *vertexi, uint16_t size);
void				message_error(char *str);
void				error_empty_line(t_data *data, t_graph *graph);
void				error_ants(t_data *data);
void				error_file(t_data *data);
void				error_malloc(t_data *data, t_graph *graph);
void				get_rooms(t_data *data, t_graph *graph);
t_room				*push_room(t_data *data, char **tab, t_room *new,
					t_room *tmp);
t_room				*get_place_room(t_room *rooms, char *name);
t_room				*make_new_room(t_data *data, char **tab);
void				free_tab(char **tab, int8_t start);
void				error_name_room(t_data *data);
void				error_not_rooms_links(t_data *data, int8_t err);
void				room_to_tab(t_data *data, t_graph *graph);
void				get_start_end(t_data *data);
void				get_start_end2(t_data *data, int start, int end);
void				error_start_end(t_data *data, t_graph *grapg, int err);
void				free_start_end(t_start *s_end);
void				get_start_end2(t_data *data, int start, int end);
int					binary_search(t_vertex *vertex, char *str, uint16_t size);
void				get_links(t_data *data, t_graph *graph);
void				search_link(t_data *data, t_graph *graph);
void				push_link(t_data *data, t_graph *graph, int index1,
					int index2);
void				push_link2(t_vertex *vertex, t_adj *tmp, t_adj *new);
t_adj				*get_place_link(t_adj *adj, int index);
t_adj				*make_new_link(int index, t_data *data, t_graph *graph);
void				push_to_queue(t_queue *q, t_vertex *v, uint16_t from,
					uint16_t *last);
void				update_flow(t_vertex *v, t_queue *q, uint16_t curr);
void				reset_visited(t_vertex *v, t_queue *q, uint16_t len);
void				update_flow2(t_adj *adj, uint16_t index, int plus);
t_paths				*edmond_karp_max_flow(t_graph *g, t_data *d);
int					bfs_short_path(t_graph *g, t_queue *q, uint16_t *curr,
					uint16_t *lq);
int					bfs_get_path(t_graph *g, t_paths **p, t_queue *q,
					t_data *d);
void				push_to_q(t_queue *q, t_graph *g, uint16_t curr,
					uint16_t *lq);
t_adjp				*get_path(t_queue *q, t_graph *g, uint16_t curr,
					uint16_t *lp);
int					push_path(t_adjp *new, t_paths **p, uint16_t lp);
void				free_paths(t_paths *p);
void				get_paths(t_graph *g, t_data *d, t_paths **p);
void				error_path(t_graph *graph, t_data *data);
void				error_malloc2(t_paths *p, t_graph *g, t_queue *q,
					t_data *d);
void				free_one_path(t_adjp *p);
void				printf_file(t_data *d);
int					force_redirect(t_vertex *v, uint16_t from, uint16_t index);
int					cnt_ants(t_paths *p, int ant, int n_p, uint16_t lp);
uint16_t			sum_step(int ants, t_paths *p);
void				get_prefect_paths(t_paths **p, t_graph *g, t_data *d,
					uint16_t *stp);
void				reset_used(t_vertex *v, t_queue *q, uint16_t len);
void				sum_and_remove(int ants, t_paths *p);
void				add_ants_in_paths(t_paths *p, int ants, int job);
void				print_paths(t_graph *g, t_paths *p);
void				move_ants(t_graph *g, t_paths *p);
void				error_coord(t_data *data, char **tab);
void				error_link(t_data *d, t_graph *g);

#endif
