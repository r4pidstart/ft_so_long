/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_move.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjo <tjo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 19:06:23 by tjo               #+#    #+#             */
/*   Updated: 2022/09/01 19:36:37 by tjo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"ft_header.h"

void	move_player(int keycode, t_vars *vars)
{
	(void)keycode;
	vars->map.move_cnt++;
	draw_image(vars, get_assets(vars), 1);
}