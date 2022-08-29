/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_verify_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjo <tjo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 03:15:23 by tjo               #+#    #+#             */
/*   Updated: 2022/08/30 04:54:54 by tjo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"ft_header.h"

static void	lst_point_append(int x, int y, t_list **lst)
{
	t_point	*new;

	new = (t_point *)malloc(sizeof(t_point));
	new->x = x;
	new->y = y;
	ft_lstadd_front(lst, new);
}

static int	read_map(int fd, t_map *map)
{
	char	*tmp;
	int		tmp_len;
	int		map_len;

	map->collectible = (t_list *)0;
	map->exit = (t_list *)0;
	ft_memset(&(map->player), -1, sizeof(map->player));
	tmp = get_next_line(fd);
	map_len = ft_strlen(tmp);
	while (tmp)
	{
		tmp_len = ft_strlen(tmp);
		if (tmp_len != map_len)
			return (1);
		tmp = get_next_line(fd);
	}
	return (0);
}

// if error, free all the list
int	verify_map(char *path, t_map *map)
{
	int		fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		perror("Error\n");
		perror(strerror(errno));
		return (1);
	}
	else if (read_map(fd, map))
	{
		perror("Error\nInvalid map file\n");
		return (1);
	}
	close(fd);
	return (0);
}