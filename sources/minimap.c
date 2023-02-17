/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:44:56 by dcandeia          #+#    #+#             */
/*   Updated: 2023/02/17 16:38:53 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	minimap_draw_map(t_img img, char **map, t_pos p_pos, t_mini_map minimap);
t_pos	minimap_get_map_pos(t_pos pos);
unsigned int minimap_get_pixel_color(int x, int y, char **map);
void minimap_draw_line(t_img img, t_pos init_pos, int height);
unsigned int minimap_draw_pixel(t_img img, t_pos pos, int color);
t_pos minimap_get_init_pos(t_pos p_pos, t_mini_map minimap);
t_pos minimap_get_shifted_pos(t_pos pos, t_pos init_pos, t_mini_map minimap);
t_pos minimap_get_scaled_pos(t_pos pos, t_mini_map minimap);

t_mini_map minimap_init(void)
{
	t_mini_map	minimap;
	int			offset_corner;

	offset_corner = 20;
	minimap.size.x = WIN_WIDTH * 0.2;
	minimap.size.y = WIN_HEIGHT * 0.2;
	minimap.half_size.x = minimap.size.x / 2;
	minimap.half_size.y = minimap.size.y / 2;
	minimap.win_pos.x = WIN_WIDTH - minimap.size.x - offset_corner;
	minimap.win_pos.y = WIN_HEIGHT - minimap.size.y - offset_corner;
	
	minimap.map_scale = (float) WIN_WIDTH / MAP_WIDTH / MINIMAP_SQUARE_SIZE;
	return (minimap);
}

void minimap_render(t_img img, char **map, t_player player, t_mini_map minimap)
{
	minimap_draw_map(img, map, player.pos, minimap);
}

void minimap_draw_map(t_img img, char **map, t_pos p_pos, t_mini_map minimap)
{
	t_pos	init_pos;
	t_pos	pos;
	int		color;

	p_pos = minimap_get_scaled_pos(p_pos, minimap);
	init_pos = minimap_get_init_pos(p_pos, minimap);
	pos.y = init_pos.y;
	while (pos.y < init_pos.y + minimap.size.y)
	{
		pos.x = init_pos.x;
		while (pos.x < init_pos.x + minimap.size.x)
		{
			color = minimap_get_pixel_color(pos.x, pos.y, map);
			minimap_draw_pixel(img, minimap_get_shifted_pos(pos, init_pos, minimap), color);
			pos.x++;
		}
		pos.y++;
	}
}

t_pos minimap_get_init_pos(t_pos p_pos, t_mini_map minimap)
{
	t_pos 		pos;

	pos.x = p_pos.x - minimap.half_size.x;
	pos.y = p_pos.y - minimap.half_size.y;
	return (pos);
}

unsigned int minimap_get_pixel_color(int x, int y, char **map)
{
	t_pos pos;

	pos.x = x;
	pos.y = y;
	pos = minimap_get_map_pos(pos);
	if (pos.x < 0 || pos.y < 0 || pos.x >= MAP_WIDTH || pos.y >= MAP_HEIGHT)
		return (BGD_MINIMAP_COLOR);
	if (map[pos.y][pos.x] == '1')
		return (WALL_COLOR);
	else
		return (BGD_MINIMAP_COLOR);
}

unsigned int minimap_draw_pixel(t_img img, t_pos pos, int color)
{
	if ((pos.x >= 0 && pos.x < WIN_WIDTH) && (pos.y >= 0 && pos.y < WIN_HEIGHT))
		draw_pixel(img, pos.x, pos.y, color);
}

t_pos minimap_get_map_pos(t_pos pos)
{
	if (pos.x > 0)
    	pos.x = pos.x / MINIMAP_SQUARE_SIZE;
	if (pos.y > 0)
		pos.y = pos.y / MINIMAP_SQUARE_SIZE;
	return(pos);
}

t_pos minimap_get_shifted_pos(t_pos pos, t_pos init_pos, t_mini_map minimap)
{
	//static int offset_x = WIN_WIDTH - MINIMAP_WIDTH - 20;
	//static int offset_y = WIN_HEIGHT - MINIMAP_HEIGHT - 20;

	//pos.x += offset_x - init_pos.x;
	//pos.y += offset_y - init_pos.y;

	pos.x += minimap.win_pos.x - init_pos.x;
	pos.y += minimap.win_pos.y - init_pos.y;
	return (pos);
}

t_pos minimap_get_scaled_pos(t_pos pos, t_mini_map minimap)
{
	//static double resize_scale = (float) WIN_WIDTH / MAP_WIDTH / MINIMAP_SQUARE_SIZE;
	
	//pos.x = pos.x / resize_scale;
	//pos.y = pos.y / resize_scale;

	pos.x = pos.x / minimap.map_scale;
	pos.y = pos.y / minimap.map_scale;
	return (pos);
}
