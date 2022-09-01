/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjo <tjo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 22:05:21 by tjo               #+#    #+#             */
/*   Updated: 2022/09/01 19:39:19 by tjo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"ft_header.h"

int	close_game(t_vars *vars)
{
	mlx_destroy_window(vars->mlx, vars->win);
	// free all map, ptr
	exit(0);
}

int	key_hook(int keycode, t_vars *vars)
{
	if (keycode == KEY_W || keycode == KEY_A \
		|| keycode == KEY_S || keycode == KEY_D)
		move_player(keycode, vars);
	else if (keycode == KEY_ESC)
		close_game(vars);
	return (0);
}

static int	loooooop(t_vars *vars)
{
	draw_image(vars, get_assets(vars), 0);
	return (0);
}

int	main(int argc, char **argv)
{
	t_vars	vars;

	if (argc != 2)
		return (!printf("Wrong argument\n"));
	else if (verify_map(argv[1], &vars.map))
		return (1);
	vars.table = make_table(vars.map);
	if (!vars.table)
		return (2);
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, vars.map.col * 64, vars.map.row * 64, \
		"so_long");
	draw_image(&vars, get_assets(&vars), 0);
	mlx_hook(vars.win, 2, 0, key_hook, &vars);
	mlx_hook(vars.win, 17, 0, close_game, &vars);
	mlx_loop_hook(vars.mlx, loooooop, &vars);
	mlx_loop(vars.mlx);
}