/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 09:18:16 by dcandeia          #+#    #+#             */
/*   Updated: 2023/03/09 12:39:37 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	init_map_struct(t_map *init)
{
	init->wall_textures = ft_calloc(4, sizeof(char *));
	init->rgb_colors = ft_calloc(2, sizeof(int));
	if (!init->wall_textures || !init->rgb_colors)
	{
		if (init->wall_textures)
			free(init->wall_textures);
		if (init->rgb_colors)
			free(init->rgb_colors);
		return (FALSE);
	}
	init->rgb_colors[RGB_C] = RGB_NO_COLOR;
	init->rgb_colors[RGB_F] = RGB_NO_COLOR;
	init->content = NULL;
	return (TRUE);
}

int	get_all_map_info(t_map **map, char *filename)
{
	int		fd;

	fd = open(filename, O_RDONLY);
	if (!fd)
		return (0);
	if (!get_map_textures(map, fd) || !get_map_content(&(*map)->content, fd)
		|| !get_player_info((*map)->content, &(*map)->orientation, \
		&(*map)->pos) || !get_map_dimensions(map))
		return (FALSE);
	if (get_doors_info((*map)->content, &(*map)->doors) == -1)
		return (FALSE);
	return (TRUE);
}

int	get_game_configs(int ac, char **av, t_map *map)
{
	if (ac == 2)
	{
		if (check_file(av[1]))
		{
			if (!init_map_struct(map))
				return (0);
			if (!get_all_map_info(&map, av[1]))
			{
				free_map_memory(*map);
				return (0);
			}
		}
		else
			return (0);
		return (1);
	}
	print_error_msg("Invalid number of Arguments");
	return (0);
}
