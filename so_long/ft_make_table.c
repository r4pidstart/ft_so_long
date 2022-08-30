/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_make_table.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjo <tjo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 04:40:57 by tjo               #+#    #+#             */
/*   Updated: 2022/08/31 05:03:16 by tjo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"ft_header.h"

static void	fill_table(char **table, t_map map)
{
	t_list	*tmp;

	tmp = map.collectible;
	while (tmp)
	{
		table[((t_point *)tmp->content)->x][((t_point *)tmp->content)->y] = 'C';
		tmp = tmp->next;
	}
	tmp = map.wall;
	while (tmp)
	{
		table[((t_point *)tmp->content)->x][((t_point *)tmp->content)->y] = 'W';
		tmp = tmp->next;
	}
	tmp = map.exit;
	while (tmp)
	{
		table[((t_point *)tmp->content)->x][((t_point *)tmp->content)->y] = 'Q';
		tmp = tmp->next;
	}
	table[map.player.x][map.player.y] = 'P';
}

static void	make_enemy(char **table, t_map map)
{
	t_point	tmp;

	if (map.empty_cnt < 10)
		return ;
	while (1)
	{
		tmp = (t_point){.x = __rand() % map.row, .y = __rand() % map.col};
		if (!table[tmp.x][tmp.y])
		{
			map.enemy = tmp;
			table[tmp.x][tmp.y] = 'E';
			return ;
		}
	}
}

char	**make_table(t_map map)
{
	char	**table;
	int		i;

	table = (char **)malloc(sizeof(char **) * map.row);
	if (!table)
		return (0);
	i = map.row;
	while (i--)
	{
		table[i] = (char *)malloc(sizeof(char *) * map.col);
		if (!table[i])
			return (0);
		ft_memset(table[i], 0, map.col);
	}
	fill_table(table, map);
	make_enemy(table, map);
	return (table);
}