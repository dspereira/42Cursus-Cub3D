/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:44:56 by dcandeia          #+#    #+#             */
/*   Updated: 2023/02/20 12:21:26 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static void	draw_minimap(t_img img, char **map, t_pos p_pos, t_minimap minimap);

t_minimap	minimap_init(void)
{
	t_minimap	minimap;
	int			offset_corner;

	offset_corner = 20;
	minimap.size.x = WIN_WIDTH * 0.2;
	minimap.size.y = WIN_HEIGHT * 0.2;
	minimap.half_size.x = minimap.size.x / 2;
	minimap.half_size.y = minimap.size.y / 2;
	minimap.scaled_map_size.x = MINIMAP_SQUARE_SIZE * MAP_WIDTH;
	minimap.scaled_map_size.y = MINIMAP_SQUARE_SIZE * MAP_HEIGHT;
	minimap.win_pos.x = WIN_WIDTH - minimap.size.x - offset_corner;
	minimap.win_pos.y = WIN_HEIGHT - minimap.size.y - offset_corner;
	minimap.map_scale = (float) WIN_WIDTH / MAP_WIDTH / MINIMAP_SQUARE_SIZE;
	return (minimap);
}

void	minimap_render(t_img img, char **map, t_player pl, t_minimap minimap)
{
	draw_minimap(img, map, pl.pos, minimap);
	minimap_draw_player(img, pl, minimap);
}

static void	draw_minimap(t_img img, char **map, t_pos p_pos, t_minimap minimap)
{
	t_pos	init_pos;
	t_pos	draw_pos;
	t_pos	pos;
	int		color;

	p_pos = get_player_pos_map_scaled(p_pos, minimap);
	init_pos = get_minimap_init_pos(p_pos, minimap);
	pos.y = init_pos.y;
	while (pos.y < init_pos.y + minimap.size.y)
	{
		pos.x = init_pos.x;
		while (pos.x < init_pos.x + minimap.size.x)
		{
			color = get_pixel_color(pos, map);
			draw_pos = get_minimap_pos(pos, p_pos, minimap);
			if (color != MINIMAP_COLOR_NONE)
				draw_pixel(img, draw_pos.x, draw_pos.y, color);
			pos.x++;
		}
		pos.y++;
	}
}
