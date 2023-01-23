/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcandeia <dcandeia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 11:19:08 by dcandeia          #+#    #+#             */
/*   Updated: 2023/01/23 10:25:19 by dcandeia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

static void	free_textures(char **textures, int *rgb_colors);
static void	free_content(char **contente);

void	free_memory(t_map *map)
{
	if (map)
	{
		free_textures(map->wall_textures, map->rgb_colors);
		free_content(map->content);
		free (map);
	}
}

static void	free_textures(char **textures, int *rgb_colors)
{
	int	i;

	if (textures)
	{
		i = 0;
		while (i < 4)
		{
			if (textures[i])
				free (textures[i]);
			i++;
		}
		free (textures);
	}
	if (rgb_colors)
		free (rgb_colors);
}

static void	free_content(char **contente)
{
	int	i;

	i = 0;
	if (contente)
	{
		while (contente[i])
		{
			if (contente[i])
				free (contente[i]);
			i++;
		}
		free (contente);
	}
}
