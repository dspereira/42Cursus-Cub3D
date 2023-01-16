/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcandeia <dcandeia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 11:35:50 by dcandeia          #+#    #+#             */
/*   Updated: 2023/01/16 11:01:32 by dcandeia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

#define MAX_NBR_RGB 16777216
#define MIN_NBR_RGB 0

static int	check_tex_files(char *filename);
static void	print_textures(t_textures *tex);
static int	check_rgb_colour(int colour);

int	check_textures(t_textures *tex)
{
	print_textures(tex);
	if (!check_rgb_colour(tex[TEX_C].colour)
		|| !check_rgb_colour(tex[TEX_F].colour)
		|| !check_tex_files(tex[TEX_NO].path)
		|| !check_tex_files(tex[TEX_SO].path)
		|| !check_tex_files(tex[TEX_WE].path)
		|| !check_tex_files(tex[TEX_EA].path))
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

static void	print_textures(t_textures *tex)
{
	printf("================================================\n");
	printf("TEX_NO = %s\n", tex[TEX_NO].path);
	printf("TEX_SO = %s\n", tex[TEX_SO].path);
	printf("TEX_WE = %s\n", tex[TEX_WE].path);
	printf("TEX_EA = %s\n", tex[TEX_EA].path);
	printf("TEX_F  = %d\n", tex[TEX_F].colour);
	printf("TEX_C  = %d\n", tex[TEX_C].colour);
	printf("================================================\n");
}
