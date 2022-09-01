/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_move.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjo <tjo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 19:06:23 by tjo               #+#    #+#             */
/*   Updated: 2022/09/01 20:06:32 by tjo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"ft_header.h"

void	move_player(int c, t_vars *v)
{
	static int	way[14][2] = {[KEY_W] = {-1, 0}, \
		[KEY_A] = {0, -1}, [KEY_S] = {1, 0}, [KEY_D] = {0, 1}};
	t_point		next;

	next = (t_point){v->map.player.x + way[c][0], v->map.player.y + way[c][1]};
	if (v->table[next.x][next.y] == 'W')
		return ;
	else if (v->table[next.x][next.y] == 'Q' && v->map.collectible_cnt)
		return ;
	else if (v->table[next.x][next.y] == 'C')
		v->map.collectible_cnt--;
	else if (v->table[next.x][next.y] == 'E')
	{
		v->table[v->map.player.x][v->map.player.y] = '\0';
		v->map.player.x = -1;
		draw_image(v, get_assets(v), 0);
		return ;
	}
	else if (v->table[next.x][next.y] == 'Q')
		exit(0);
	v->table[v->map.player.x][v->map.player.y] = 0;
	v->map.player = next;
	v->table[v->map.player.x][v->map.player.y] = 'P';
	v->map.move_cnt++;
	draw_image(v, get_assets(v), 1);
}

// void	move_enemy()
// {
	
// }