/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcandeia <dcandeia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 12:00:26 by dcandeia          #+#    #+#             */
/*   Updated: 2023/01/23 09:44:44 by dcandeia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int	main(int ac, char **av)
{
	t_map	*map;

	if (ac == 2)
	{
		if (check_file(av[1]))
		{
			map = init_map_struct();
			if (!get_all_map_info(&map, av[1]))
				printf("Map KO\n");
			else
				printf("Map OK\n");
		}
		else
			printf("Map KO\n");
		free_memory(map);
		return (0);
	}
	printf("Error: Invalid number of Arguments\n");
	return (-1);
}
