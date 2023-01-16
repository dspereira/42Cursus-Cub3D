/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcandeia <dcandeia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 09:18:16 by dcandeia          #+#    #+#             */
/*   Updated: 2023/01/16 09:59:27 by dcandeia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

t_map	*init_map_struct(void)
{
	t_map	*init;

	init = ft_calloc(1, sizeof(t_map));
	if (!init)
		return (NULL);
	init.wall_textures = ft_calloc(4, sizeof(char *));
	init.rgb_colours = ft_calloc(2, sizeof(int));
	if (!init.wall_textures || !init.rgb_colours)
	{
		if (init.wall_textures)
			free(init.wall_textures);
		if (init.rgb_colours)
			free(init.rgb_colours);
		free(init);
		return (NULL);
	}
	map.rgb_colours[0] = -1;
	map.rgb_colours[1] = -1;
	return (init);
}

int	get_all_map_info(t_map *map, filename)
{
	int		fd;
	char	*line;

	fd = open(filename, O_READ);
	if (!fd)
		return (0);
	get_map_textures(map, fd);
	
}
