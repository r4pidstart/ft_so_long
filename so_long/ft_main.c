/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjo <tjo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 22:05:21 by tjo               #+#    #+#             */
/*   Updated: 2022/08/30 23:15:18 by tjo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"ft_header.h"

int	main(int argc, char **argv)
{
	t_map	map;

	if (argc != 2)
		return (!printf("Wrong argument"));
	else if (verify_map(argv[1], &map))
		return (2);
}