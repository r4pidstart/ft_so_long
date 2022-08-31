/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjo <tjo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 03:29:47 by tjo               #+#    #+#             */
/*   Updated: 2022/09/01 04:05:14 by tjo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"ft_header.h"

static t_assets	get_assets(t_vars *v)
{
	t_assets	r;
	int			t;

	r.chest = mlx_xpm_file_to_image(v->mlx, "./assets/chest.xpm", &t, &t);
	r.door = mlx_xpm_file_to_image(v->mlx, "./assets/door.xpm", &t, &t);
	r.ground = mlx_xpm_file_to_image(v->mlx, "./assets/ground.xpm", &t, &t);
	r.player[0] = mlx_xpm_file_to_image(v->mlx, "./assets/player1.xpm", &t, &t);
	r.player[1] = mlx_xpm_file_to_image(v->mlx, "./assets/player2.xpm", &t, &t);
	r.slime = mlx_xpm_file_to_image(v->mlx, "./assets/slime.xpm", &t, &t);
	r.wall = mlx_xpm_file_to_image(v->mlx, "./assets/wall.xpm", &t, &t);
	r.sharp = mlx_xpm_file_to_image(v->mlx, "./assets/num/#.xpm", &t, &t);
	r.num[0] = mlx_xpm_file_to_image(v->mlx, "./assets/num/0.xpm", &t, &t);
	r.num[1] = mlx_xpm_file_to_image(v->mlx, "./assets/num/1.xpm", &t, &t);
	r.num[2] = mlx_xpm_file_to_image(v->mlx, "./assets/num/2.xpm", &t, &t);
	r.num[3] = mlx_xpm_file_to_image(v->mlx, "./assets/num/3.xpm", &t, &t);
	r.num[4] = mlx_xpm_file_to_image(v->mlx, "./assets/num/4.xpm", &t, &t);
	r.num[5] = mlx_xpm_file_to_image(v->mlx, "./assets/num/5.xpm", &t, &t);
	r.num[6] = mlx_xpm_file_to_image(v->mlx, "./assets/num/6.xpm", &t, &t);
	r.num[7] = mlx_xpm_file_to_image(v->mlx, "./assets/num/7.xpm", &t, &t);
	r.num[8] = mlx_xpm_file_to_image(v->mlx, "./assets/num/8.xpm", &t, &t);
	r.num[9] = mlx_xpm_file_to_image(v->mlx, "./assets/num/9.xpm", &t, &t);
	return (r);
}

void	draw_image(t_vars *v)
{
	t_assets	a;
	int			x;
	int			y;

	a = get_assets(v);
	x = v->map.row;
	while (x--)
	{
		y = v->map.col;
		while (y--)
		{
			mlx_put_image_to_window(v->mlx, v->win, a.ground, y * 64, x * 64);
			if (v->table[x][y] == 'C')
				mlx_put_image_to_window(v->mlx, v->win, a.chest, y * 64, x * 64);
			else if (v->table[x][y] == 'W')
				mlx_put_image_to_window(v->mlx, v->win, a.wall, y * 64, x * 64);
			else if (v->table[x][y] == 'Q')
				mlx_put_image_to_window(v->mlx, v->win, a.door, y * 64, x * 64);
			else if (v->table[x][y] == 'P')
				mlx_put_image_to_window(v->mlx, v->win, a.player[0], y * 64, x * 64);
		}
	}
}