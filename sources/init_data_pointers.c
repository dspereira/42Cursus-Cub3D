/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data_pointers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcandeia < dcandeia@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 12:58:45 by dcandeia          #+#    #+#             */
/*   Updated: 2023/03/01 15:25:38 by dcandeia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static void	init_imgs_pointers(t_tex *tex);

void	init_data_pointers(t_data *data)
{
	data->map.content = NULL;
	data->map.wall_textures = NULL;
	data->map.doors = NULL;
	data->map.rgb_colors = NULL;
	data->win = NULL;
	data->player = NULL;
	init_imgs_pointers(&(data->tex));
}

static void	init_imgs_pointers(t_tex *tex)
{
	int	i;

	i = 0;
	tex->ea.mlx_img = NULL;
	tex->ea.addr = NULL;
	tex->no.mlx_img = NULL;
	tex->no.addr = NULL;
	tex->we.mlx_img = NULL;
	tex->we.addr = NULL;
	tex->so.mlx_img = NULL;
	tex->so.addr = NULL;
	tex->door_side.mlx_img = NULL;
	tex->door_side.addr = NULL;
	while (i < 9)
	{
		tex->doors[i].mlx_img = NULL;
		tex->doors[i].addr = NULL;
		i++;
	}
}
