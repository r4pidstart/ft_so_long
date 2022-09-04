/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjo <tjo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 03:29:47 by tjo               #+#    #+#             */
/*   Updated: 2022/09/04 20:03:26 by tjo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"ft_header_bonus.h"

t_assets	get_assets(t_vars *v)
{
	t_assets	r;
	int			t;

	r.chest = mlx_xpm_file_to_image(v->m, "./assets/chest.xpm", &t, &t);
	r.door = mlx_xpm_file_to_image(v->m, "./assets/door.xpm", &t, &t);
	r.ground = mlx_xpm_file_to_image(v->m, "./assets/ground.xpm", &t, &t);
	r.player[0] = mlx_xpm_file_to_image(v->m, "./assets/player1.xpm", &t, &t);
	r.player[1] = mlx_xpm_file_to_image(v->m, "./assets/player2.xpm", &t, &t);
	r.slime = mlx_xpm_file_to_image(v->m, "./assets/slime.xpm", &t, &t);
	r.wall = mlx_xpm_file_to_image(v->m, "./assets/wall.xpm", &t, &t);
	r.sharp = mlx_xpm_file_to_image(v->m, "./assets/num/#.xpm", &t, &t);
	r.num[0] = mlx_xpm_file_to_image(v->m, "./assets/num/0.xpm", &t, &t);
	r.num[1] = mlx_xpm_file_to_image(v->m, "./assets/num/1.xpm", &t, &t);
	r.num[2] = mlx_xpm_file_to_image(v->m, "./assets/num/2.xpm", &t, &t);
	r.num[3] = mlx_xpm_file_to_image(v->m, "./assets/num/3.xpm", &t, &t);
	r.num[4] = mlx_xpm_file_to_image(v->m, "./assets/num/4.xpm", &t, &t);
	r.num[5] = mlx_xpm_file_to_image(v->m, "./assets/num/5.xpm", &t, &t);
	r.num[6] = mlx_xpm_file_to_image(v->m, "./assets/num/6.xpm", &t, &t);
	r.num[7] = mlx_xpm_file_to_image(v->m, "./assets/num/7.xpm", &t, &t);
	r.num[8] = mlx_xpm_file_to_image(v->m, "./assets/num/8.xpm", &t, &t);
	r.num[9] = mlx_xpm_file_to_image(v->m, "./assets/num/9.xpm", &t, &t);
	return (r);
}

static void	draw_count(t_vars *v, t_assets *a, int moved)
{
	int	cnt;
	int	digits;
	int	offset;

	if (moved == 1)
		printf("move count: #%d\n", v->map.move_cnt);
	cnt = v->map.move_cnt;
	digits = 0;
	offset = v->map.col * 64 - 64;
	while (cnt)
	{
		mlx_put_image_to_window(v->m, v->w, \
			a->num[cnt % 10], offset - digits * 18, 16);
		digits++;
		cnt /= 10;
	}
	if (digits)
		mlx_put_image_to_window(v->m, v->w, \
			a->sharp, offset - digits * 18 - 16, 16);
}

static void	draw_area(t_point p, t_vars *v, t_assets *a, int p_state)
{
	if (v->table[p.x][p.y] == 'W')
		mlx_put_image_to_window(v->m, v->w, a->wall, p.y * 64, p.x * 64);
	else if (v->table[p.x][p.y] != 'W')
	{
		mlx_put_image_to_window(v->m, v->w, a->ground, p.y * 64, p.x * 64);
		if (v->table[p.x][p.y] == 'C')
			mlx_put_image_to_window(v->m, v->w, a->chest, p.y * 64, p.x * 64);
		else if (v->table[p.x][p.y] == 'P')
			mlx_put_image_to_window(v->m, v->w, \
				a->player[p_state / 50 & 1], p.y * 64, p.x * 64);
		else if (v->table[p.x][p.y] == 'Q')
			mlx_put_image_to_window(v->m, v->w, a->door, p.y * 64, p.x * 64);
		else if (v->table[p.x][p.y] == 'E')
			mlx_put_image_to_window(v->m, v->w, a->slime, p.y * 64, p.x * 64);
	}
}

void	draw_image(t_vars *v, int moved)
{
	static int	p_state = 0;
	int			x;
	int			y;

	p_state++;
	if (p_state % 33 == 0)
	{
		move_enemy(v);
		moved = 2;
	}
	if (p_state % 50 == 0 && !moved)
		return ;
	x = v->map.row;
	while (x--)
	{
		y = v->map.col;
		while (y--)
			draw_area((t_point){x, y}, v, &v->assets, p_state);
	}
	if (p_state >= 100)
		p_state = 0;
	draw_count(v, &v->assets, moved);
}
