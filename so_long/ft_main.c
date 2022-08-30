/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjo <tjo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 22:05:21 by tjo               #+#    #+#             */
/*   Updated: 2022/08/31 05:08:03 by tjo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"ft_header.h"

int	main(int argc, char **argv)
{
	t_map	map;
	char	**table;

	if (argc != 2)
		return (!printf("Wrong argument\n"));
	else if (verify_map(argv[1], &map))
		return (1);
	table = make_table(map);
	if (!table)
		return (2);

	// free_table(table, map.row);
}