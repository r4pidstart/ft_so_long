/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjo <tjo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 22:05:21 by tjo               #+#    #+#             */
/*   Updated: 2022/08/29 22:47:31 by tjo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"ft_header.h"

int	main(void)
{
	void	*mlx;
	void	*mlx_win;

	printf("test");
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "TEST");
	mlx_loop(mlx);

	(void)mlx_win;
}