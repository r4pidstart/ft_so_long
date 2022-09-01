/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_verify_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjo <tjo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 03:15:23 by tjo               #+#    #+#             */
/*   Updated: 2022/09/01 20:10:32 by tjo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"ft_header.h"

static int	lst_point_append(int x, int y, t_list **lst)
{
	t_point	*new_point;
	t_list	*new;

	new = (t_list *)malloc(sizeof(t_list));
	if (!new)
		return (1);
	new->next = 0;
	new_point = (t_point *)malloc(sizeof(t_point));
	if (!new_point)
	{
		free(new);
		return (1);
	}
	new_point->x = x;
	new_point->y = y;
	new->content = new_point;
	ft_lstadd_front(lst, new);
	return (0);
}

static int	line_check(char *line, int len, int *wall_cnt, t_map *map)
{
	if (line[0] != '1' || line[len - 1] != '1')
		return (1);
	while (len--)
	{
		*wall_cnt += (line[len] == '1');
		if (line[len] == 'C')
		{
			lst_point_append(map->row, len, &map->collectible);
			map->collectible_cnt++;
		}
		else if (line[len] == 'E')
			lst_point_append(map->row, len, &map->exit);
		else if (line[len] == 'P' && map->player.x == -1)
			map->player = (t_point){.x = map->row, .y = len};
		else if (line[len] == '1')
			lst_point_append(map->row, len, &map->wall);
		else if (line[len] == '0')
			map->empty_cnt++;
		else
			return (1);
	}
	return (0);
}

static int	read_map(int fd, t_map *map)
{
	char	*tmp;
	int		tmp_len;
	int		wall_cnt;

	tmp = get_next_line(fd);
	if (tmp == 0)
		return (1);
	map->col = ft_strlen(tmp);
	map->col -= (tmp[map->col - 1] == '\n');
	while (tmp)
	{
		wall_cnt = 0;
		tmp_len = ft_strlen(tmp);
		tmp_len -= (tmp[tmp_len - 1] == '\n');
		if (tmp_len != map->col || line_check(tmp, tmp_len, &wall_cnt, map))
			return (1);
		else if (!map->row && wall_cnt != map->col)
			return (1);
		map->row++;
		tmp = get_next_line(fd);
	}
	return (wall_cnt != map->col || map->player.x == -1 \
	|| !map->collectible || !map->exit);
}

// if error, free all the list
int	verify_map(char *path, t_map *map)
{
	int		fd;

	*map = (t_map){.collectible = 0, .exit = 0, .wall = 0};
	*map = (t_map){.move_cnt = 0, .collectible_cnt = 0};
	map->player = (t_point){.x = -1, .y = -1};
	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		perror("Error\nCannot open the file");
		return (1);
	}
	else if (read_map(fd, map))
	{
		printf("Error\nInvalid map file\n");
		ft_lstclear(&map->collectible, free);
		ft_lstclear(&map->exit, free);
		return (1);
	}
	close(fd);
	return (0);
}