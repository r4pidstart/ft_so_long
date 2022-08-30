/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_header.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjo <tjo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 22:05:23 by tjo               #+#    #+#             */
/*   Updated: 2022/08/31 05:04:40 by tjo              ###   ########.fr       */
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
# include"mlx/mlx.h"
# include"mylibft/libft.h"

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
	t_point	player;
	t_point	enemy;
	t_list	*exit;
	t_list	*collectible;
	t_list	*wall;
}t_map;

/* ft_verify_map.c */
int	verify_map(char *path, t_map *map);

/* ft_header.c */
char	**make_table(t_map map);

/* ft_utils.c */
size_t	__rand(void);


#endif