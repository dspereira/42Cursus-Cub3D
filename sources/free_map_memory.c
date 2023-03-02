/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_map_memory.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcandeia < dcandeia@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 11:19:08 by dcandeia          #+#    #+#             */
/*   Updated: 2023/03/01 16:30:48 by dcandeia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void	free_textures(char **textures, int *rgb_colors);
static void	free_content(char **content);

void	free_map_memory(t_map map)
{
	free_textures(map.wall_textures, map.rgb_colors);
	free_content(map.content);
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

static void	free_content(char **content)
{
	int	i;

	i = 0;
	if (content)
	{
		while (content[i])
		{
			free (content[i]);
			i++;
		}
		free (content);
	}
}
