/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:44:56 by dcandeia          #+#    #+#             */
/*   Updated: 2023/02/17 15:11:37 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"


void	minimap_draw_map(t_img img, char **map, t_pos p_pos);
void	minimap_set_frame_pos(t_pos p_pos, t_pos *init_pos, t_pos *end_pos);
t_pos	minimap_get_map_pos(t_pos pos);
unsigned int minimap_get_pixel_color(int x, int y, char **map);
void minimap_draw_line(t_img img, t_pos init_pos, int height);
unsigned int minimap_draw_pixel(t_img img, t_pos pos, int color);
t_pos minimap_get_init_pos(t_pos p_pos);
t_pos minimap_get_shifted_pos(t_pos pos, t_pos init_pos);

t_pos minimap_get_scaled_pos(t_pos pos);

void minimap_render(t_img img, char **map, t_player player)
{
	minimap_draw_map(img, map, player.pos);
}

void minimap_draw_map(t_img img, char **map, t_pos p_pos)
{
	t_pos	init_pos;
	t_pos	pos;
	int		color;

	p_pos = minimap_get_scaled_pos(p_pos);
	init_pos = minimap_get_init_pos(p_pos);
	pos.y = init_pos.y;
	while (pos.y < init_pos.y + MINIMAP_HEIGHT)
	{
		pos.x = init_pos.x;
		while (pos.x < init_pos.x + MINIMAP_WIDTH)
		{
			color = minimap_get_pixel_color(pos.x, pos.y, map);
			minimap_draw_pixel(img, minimap_get_shifted_pos(pos, init_pos), color);
			pos.x++;
		}
		pos.y++;
	}
}

void minimap_set_frame_pos(t_pos p_pos, t_pos *init_pos, t_pos *end_pos)
{
	static int	half_h = MINIMAP_HEIGHT / 2;
	static int	half_w = MINIMAP_WIDTH / 2;

	init_pos->x = p_pos.x - half_w;
	init_pos->y = p_pos.y - half_w;
	end_pos->x = p_pos.x + half_w;
	end_pos->y = p_pos.y + half_w;
}

t_pos minimap_get_init_pos(t_pos p_pos)
{
	static int	half_h = MINIMAP_HEIGHT / 2;
	static int	half_w = MINIMAP_WIDTH / 2;
	t_pos 		pos;

	pos.x = p_pos.x - half_w;
	pos.y = p_pos.y - half_h;
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

t_pos minimap_get_shifted_pos(t_pos pos, t_pos init_pos)
{
	static int offset_x = WIN_WIDTH - MINIMAP_WIDTH - 20;
	static int offset_y = WIN_HEIGHT - MINIMAP_HEIGHT - 20;

	pos.x += offset_x - init_pos.x;
	pos.y += offset_y - init_pos.y;
	return (pos);
}

t_pos minimap_get_scaled_pos(t_pos pos)
{
	static double resize_scale = (float) WIN_WIDTH / MAP_WIDTH / MINIMAP_SQUARE_SIZE;
	
	pos.x = pos.x / resize_scale;
	pos.y = pos.y / resize_scale;
	return (pos);
}
