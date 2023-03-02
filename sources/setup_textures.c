/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcandeia < dcandeia@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 12:25:05 by dcandeia          #+#    #+#             */
/*   Updated: 2023/03/01 14:19:28 by dcandeia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void	init_doors_tex(t_tex *tex, void *mlx);
static void	init_doors_sprites_1(t_img *doors, void *mlx);
static void	init_doors_sprites_2(t_img *doors, void *mlx);

void	setup_textures(char **tex_files, int *rgb, t_tex *texture, void *mlx)
{
	texture->no.mlx_img = mlx_xpm_file_to_image(mlx, tex_files[TEX_NO], \
		&(texture->no.width), &(texture->no.height));
	texture->no.addr = mlx_get_data_addr(texture->no.mlx_img, \
		&(texture->no.bpp), &(texture->no.line_len), &(texture->no.endian));
	texture->so.mlx_img = mlx_xpm_file_to_image(mlx, tex_files[TEX_SO], \
		&(texture->so.width), &(texture->so.height));
	texture->so.addr = mlx_get_data_addr(texture->so.mlx_img, \
		&(texture->so.bpp), &(texture->so.line_len), &(texture->so.endian));
	texture->ea.mlx_img = mlx_xpm_file_to_image(mlx, tex_files[TEX_EA], \
		&(texture->ea.width), &(texture->ea.height));
	texture->ea.addr = mlx_get_data_addr(texture->ea.mlx_img, \
		&(texture->ea.bpp), &(texture->ea.line_len), &(texture->ea.endian));
	texture->we.mlx_img = mlx_xpm_file_to_image(mlx, tex_files[TEX_WE], \
		&(texture->we.width), &(texture->we.height));
	texture->we.addr = mlx_get_data_addr(texture->we.mlx_img, \
		&(texture->we.bpp), &(texture->we.line_len), &(texture->we.endian));
	init_doors_tex(texture, mlx);
	texture->ceil_rgb = rgb[RGB_C];
	texture->floor_rgb = rgb[RGB_F];
}

static void	init_doors_tex(t_tex *tex, void *mlx)
{
	tex->door_side.mlx_img = mlx_xpm_file_to_image(mlx, SIDE_DOOR_TEX, \
		&(tex->door_side.width), &(tex->door_side.height));
	tex->door_side.addr = mlx_get_data_addr(tex->door_side.mlx_img, \
		&(tex->door_side.bpp), &(tex->door_side.line_len), \
		&(tex->door_side.endian));
	init_doors_sprites_1(tex->doors, mlx);
	init_doors_sprites_2(tex->doors, mlx);
}

static void	init_doors_sprites_1(t_img *doors, void *mlx)
{
	doors[DOOR_CLOSE].mlx_img = mlx_xpm_file_to_image(mlx, D_TEX_CLOSE, \
		&(doors[DOOR_CLOSE].width), &(doors[DOOR_CLOSE].height));
	doors[DOOR_CLOSE].addr = mlx_get_data_addr(doors[DOOR_CLOSE].mlx_img, \
		&(doors[DOOR_CLOSE].bpp), &(doors[DOOR_CLOSE].line_len), \
		&(doors[DOOR_CLOSE].endian));
	doors[DOOR_OPEN_1].mlx_img = mlx_xpm_file_to_image(mlx, D_TEX_OPEN_1, \
		&(doors[DOOR_OPEN_1].width), &(doors[DOOR_OPEN_1].height));
	doors[DOOR_OPEN_1].addr = mlx_get_data_addr(doors[DOOR_OPEN_1].mlx_img, \
		&(doors[DOOR_OPEN_1].bpp), &(doors[DOOR_OPEN_1].line_len), \
		&(doors[DOOR_OPEN_1].endian));
	doors[DOOR_OPEN_2].mlx_img = mlx_xpm_file_to_image(mlx, D_TEX_OPEN_2, \
		&(doors[DOOR_OPEN_2].width), &(doors[DOOR_OPEN_2].height));
	doors[DOOR_OPEN_2].addr = mlx_get_data_addr(doors[DOOR_OPEN_2].mlx_img, \
		&(doors[DOOR_OPEN_2].bpp), &(doors[DOOR_OPEN_2].line_len), \
		&(doors[DOOR_OPEN_2].endian));
	doors[DOOR_OPEN_3].mlx_img = mlx_xpm_file_to_image(mlx, D_TEX_OPEN_3, \
		&(doors[DOOR_OPEN_3].width), &(doors[DOOR_OPEN_3].height));
	doors[DOOR_OPEN_3].addr = mlx_get_data_addr(doors[DOOR_OPEN_3].mlx_img, \
		&(doors[DOOR_OPEN_3].bpp), &(doors[DOOR_OPEN_3].line_len), \
		&(doors[DOOR_OPEN_3].endian));
}

static void	init_doors_sprites_2(t_img *doors, void *mlx)
{
	doors[DOOR_OPEN_4].mlx_img = mlx_xpm_file_to_image(mlx, D_TEX_OPEN_4, \
		&(doors[DOOR_OPEN_4].width), &(doors[DOOR_OPEN_4].height));
	doors[DOOR_OPEN_4].addr = mlx_get_data_addr(doors[DOOR_OPEN_4].mlx_img, \
		&(doors[DOOR_OPEN_4].bpp), &(doors[DOOR_OPEN_4].line_len), \
		&(doors[DOOR_OPEN_4].endian));
	doors[DOOR_OPEN_5].mlx_img = mlx_xpm_file_to_image(mlx, D_TEX_OPEN_5, \
		&(doors[DOOR_OPEN_5].width), &(doors[DOOR_OPEN_5].height));
	doors[DOOR_OPEN_5].addr = mlx_get_data_addr(doors[DOOR_OPEN_5].mlx_img, \
		&(doors[DOOR_OPEN_5].bpp), &(doors[DOOR_OPEN_5].line_len), \
		&(doors[DOOR_OPEN_5].endian));
	doors[DOOR_OPEN_6].mlx_img = mlx_xpm_file_to_image(mlx, D_TEX_OPEN_6, \
		&(doors[DOOR_OPEN_6].width), &(doors[DOOR_OPEN_6].height));
	doors[DOOR_OPEN_6].addr = mlx_get_data_addr(doors[DOOR_OPEN_6].mlx_img, \
		&(doors[DOOR_OPEN_6].bpp), &(doors[DOOR_OPEN_6].line_len), \
		&(doors[DOOR_OPEN_6].endian));
	doors[DOOR_OPEN_7].mlx_img = mlx_xpm_file_to_image(mlx, D_TEX_OPEN_7, \
		&(doors[DOOR_OPEN_7].width), &(doors[DOOR_OPEN_7].height));
	doors[DOOR_OPEN_7].addr = mlx_get_data_addr(doors[DOOR_OPEN_7].mlx_img, \
		&(doors[DOOR_OPEN_7].bpp), &(doors[DOOR_OPEN_7].line_len), \
		&(doors[DOOR_OPEN_7].endian));
	doors[DOOR_OPEN].mlx_img = mlx_xpm_file_to_image(mlx, D_TEX_OPEN, \
		&(doors[DOOR_OPEN].width), &(doors[DOOR_OPEN].height));
	doors[DOOR_OPEN].addr = mlx_get_data_addr(doors[DOOR_OPEN].mlx_img, \
		&(doors[DOOR_OPEN].bpp), &(doors[DOOR_OPEN].line_len), \
		&(doors[DOOR_OPEN].endian));
}
