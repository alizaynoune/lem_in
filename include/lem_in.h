/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alzaynou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/05 00:20:20 by alzaynou          #+#    #+#             */
/*   Updated: 2020/01/10 19:19:34 by alzaynou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H
# include "../libprintf/includes/ft_printf.h"
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>
/*
 * **Macros
 */
# define DEFAULT "\033[0m"
# define RED "\033[31;1m"
# define GREEN "\033[32;1m"
# define YELLOW "\033[33;1m"
/*
 ** Data stuct
 */

typedef struct		s_lines
{
	char			*line;
	struct s_lines	*next;
}					t_lines;

typedef struct		s_roms
{
	char			*name;
	int				index;
	struct s_roms	*childe;
}					t_roms;

typedef struct		s_stack
{
	int				index;
	struct s_stack	*next;
	struct s_stack	*prev;
}					t_stack;

typedef struct		s_lst
{
	int				index;
	struct s_lst	*next;
	struct s_lst	*prev;
}					t_lst;

typedef struct		s_vist
{
	t_lst			*lst;
	t_lst			*bck;
	struct s_vist	*next;
	struct s_vist	*prev;
}					t_vist;

typedef struct		s_paths
{
	t_stack			*path;
	int				n_roms;
	struct s_paths	*next;
}					t_paths;

typedef struct      s_all
{
	t_lines         *lines;
	t_roms          *roms;
	t_paths			*paths;
	char            **s_end;
	int             n_ants;
	int             n_roms;
}                   t_all;


t_all     read_fill(t_all data, t_lines *new, t_lines *tmp, char *line);
void    print_lines(t_lines *lines);//
void    error_message(char *msg, int n_line);
t_all      get_roms(t_all data, t_lines *tmp);
t_roms      *push_roms(t_roms *roms, char *line, int *nbr);
void    print_roms(t_roms *roms, int n);//
int     cnt_char(char *str, char c);
t_roms      *stock_roms(t_roms *roms, int n_roms, t_roms *tmp);
void        free_tab(char **tab, int start);
void        free_roms(t_roms *roms);
void        free_p_roms(t_roms *roms, int len);
void        free_lines(t_lines *lines);
t_roms      *sort_roms(t_roms *roms, int len);
int     binary_search(t_roms *roms, char *str,  int len);
t_roms      *find_links(t_roms *roms, t_lines *lines, int n_roms);
t_roms      *push_links(t_roms *roms, char **tab, int tmp0, int tmp1);
void    error_num_ants(t_lines *lines);
char    **get_start_end(char *line, char **s_end, char *cmd);
void    error_start_end(t_all data);
void        free_roms_error(t_roms *roms);
void        error_empty_line(t_all data, int n_line);
t_paths     *find_paths(t_roms *roms, t_paths *head, int start, int end);//
t_vist      *rom_not_vist(t_vist *vist, t_roms *roms, t_stack *stack, int end);
t_lst       *push_to_lst(t_lst *head, t_lst *new);
int         check_is_vist(int index, t_stack *stack);
t_stack     *push_to_stack(int index, t_stack *stack);
t_stack     *stack_to_path(t_stack *stack, int   *nbr);
t_paths     *get_paths(t_stack *stack, t_paths *head);
void    print_not_vist(t_paths *lst, t_roms *roms);//
void        free_paths(t_paths *path);
t_vist        *free_vist(t_vist *vist);
void    error_fille(int error);
void        error_many_s_end(t_all data);
t_stack     *free_stack(t_stack *stack);
int     check_is_pushed(t_roms *roms, int tmp0, int tmp1);
int         check_is_vist2(int index, t_vist *vist);
t_vist      *free_other_roms(t_vist *nvist, t_lst *new);

#endif
