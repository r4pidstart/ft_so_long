/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_header.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjo <tjo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 22:05:23 by tjo               #+#    #+#             */
/*   Updated: 2022/09/01 23:49:27 by tjo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_HEADER_H
# define FT_HEADER_H

# include<stdlib.h>
# include<unistd.h>
# include<fcntl.h>
# include<stdio.h>
# include<errno.h>
# include<string.h> 
# include"../mlx/mlx.h"
# include"../mylibft/libft.h"

typedef struct s_point
{
	int	x;
	int	y;
}t_point;

typedef struct s_map
{
	int		row;
	int		col;
	int		empty_cnt;
	int		collectible_cnt;
	int		move_cnt;
	t_point	player;
	t_point	enemy;
	t_list	*exit;
	t_list	*collectible;
	t_list	*wall;
}t_map;

typedef struct s_assets
{
	void	*chest;
	void	*door;
	void	*ground;
	void	*player[2];
	void	*slime;
	void	*wall;
	void	*num[10];
	void	*sharp;
}t_assets;

typedef struct s_vars
{
	void		*m;
	void		*w;
	char		**table;
	t_map		map;
	t_assets	assets;
}t_vars;


enum	e_keycode
{
	KEY_W = 13,
	KEY_A = 0,
	KEY_S = 1,
	KEY_D = 2,
	KEY_ESC = 53
};

/* ft_main.c */
int			close_game(t_vars *vars);
/* ft_verify_map.c */
int			verify_map(char *path, t_map *map);

/* ft_header.c */
char		**make_table(t_map *map);

/* ft_utils.c */
size_t		__rand(void);

/* ft_draw.c */
t_assets	get_assets(t_vars *v);
void		draw_image(t_vars *vars, int moved);

/* ft_move.c */
void		move_player(int keycode, t_vars *vars);
void		move_enemy(t_vars *v);




#endif