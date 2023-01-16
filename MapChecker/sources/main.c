/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcandeia <dcandeia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 12:00:26 by dcandeia          #+#    #+#             */
/*   Updated: 2023/01/16 09:34:47 by dcandeia         ###   ########.fr       */
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
			if (!get_all_map_info(map, av[1]))
			{
				//free_memory(map);
				return (-1);
			}
			map = get_file_textures(myfile->content, &myfile->end_tex_line);
			myfile->map = get_map(myfile->content, myfile->end_tex_line);
			check_textures(myfile->tex);
			is_valid_map(myfile->map);
			printf("Map OK");
		}
		else
		{
			printf("Map KO");
			return (-1);
		}
		//free_memory(myfile);
		return (0);
	}
	printf("Error: Invalid number of Arguments\n");
	return (-1);
}
