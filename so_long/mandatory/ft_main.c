/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjo <tjo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 22:05:21 by tjo               #+#    #+#             */
/*   Updated: 2022/09/02 00:03:32 by tjo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"ft_header.h"

static void	free_elements(t_vars *vars)
{
	int	n;

	ft_lstclear(&vars->map.collectible, free);
	ft_lstclear(&vars->map.exit, free);
	free(vars->assets.chest);
	free(vars->assets.door);
	free(vars->assets.ground);
	free(vars->assets.player[0]);
	free(vars->assets.player[1]);
	free(vars->assets.slime);
	free(vars->assets.wall);
	n = 10;
	while (n--)
		free(vars->assets.num[n]);
	free(vars->assets.sharp);
}

int	close_game(t_vars *vars)
{
	mlx_destroy_window(vars->m, vars->w);
	free_elements(vars);
	exit(0);
}

static int	key_hook(int keycode, t_vars *vars)
{
	if (vars->map.player.x == -1)
		return (0);
	if (keycode == KEY_W || keycode == KEY_A \
		|| keycode == KEY_S || keycode == KEY_D)
		move_player(keycode, vars);
	else if (keycode == KEY_ESC)
		close_game(vars);
	return (0);
}

static int	loooooop(t_vars *vars)
{
	draw_image(vars, 0);
	return (0);
}

int	main(int argc, char **argv)
{
	t_vars	vars;

	if (argc != 2)
		return (!printf("Wrong argument\n"));
	else if (verify_map(argv[1], &vars.map))
		return (1);
	vars.table = make_table(&vars.map);
	if (!vars.table)
	{
		free_elements(&vars);
		return (2);
	}
	vars.m = mlx_init();
	vars.w = mlx_new_window(vars.m, vars.map.col * 64, vars.map.row * 64, \
		"so_long");
	vars.assets = get_assets(&vars);
	draw_image(&vars, 0);
	mlx_hook(vars.w, 2, 0, key_hook, &vars);
	mlx_hook(vars.w, 17, 0, close_game, &vars);
	mlx_loop_hook(vars.m, loooooop, &vars);
	mlx_loop(vars.m);
}
