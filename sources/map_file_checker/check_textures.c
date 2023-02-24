/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcandeia < dcandeia@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 11:35:50 by dcandeia          #+#    #+#             */
/*   Updated: 2023/02/24 15:11:18 by dcandeia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

#define MAX_NBR_RGB 16777216
#define MIN_NBR_RGB 0

static int	check_tex_files(char *filename);
static int	check_rgb_colour(int colour);

int	check_textures(char **textures, int *rgb_colors)
{
	if (!check_rgb_colour(rgb_colors[RGB_C])
		|| !check_rgb_colour(rgb_colors[RGB_F])
		|| !check_tex_files(textures[TEX_NO])
		|| !check_tex_files(textures[TEX_SO])
		|| !check_tex_files(textures[TEX_WE])
		|| !check_tex_files(textures[TEX_EA]))
		return (FALSE);
	return (TRUE);
}

static int	check_tex_files(char *filename)
{
	int	fd;

	if (!filename)
	{
		print_error_msg("Missing texture File");
		return (FALSE);
	}
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		print_error_msg("Impossible to read from Texture file");
		putstr_error("File: ");
		putstr_error(filename);
		putstr_error("\n");
		return (FALSE);
	}
	close(fd);
	return (TRUE);
}

static int	check_rgb_colour(int colour)
{
	if (colour < MIN_NBR_RGB || colour > MAX_NBR_RGB)
	{
		print_error_msg("Incorrect RGB colour");
		return (FALSE);
	}
	return (TRUE);
}
