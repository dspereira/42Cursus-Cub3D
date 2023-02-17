/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:44:56 by dcandeia          #+#    #+#             */
/*   Updated: 2023/02/17 21:49:17 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	minimap_draw_map(t_img img, char **map, t_pos p_pos, t_mini_map minimap);
t_pos	minimap_get_map_pos(t_pos pos);
unsigned int minimap_get_pixel_color(int x, int y, char **map);
unsigned int minimap_draw_pixel(t_img img, t_pos pos, int color);
t_pos minimap_get_init_pos(t_pos p_pos, t_mini_map minimap);
t_pos minimap_get_drawing_pos(t_pos pos, t_pos offset_correct, t_mini_map minimap);
t_pos minimap_get_player_pos(t_pos pos, t_mini_map minimap);
void minimap_draw_player(t_img img, t_pos p_pos, float dir, t_mini_map minimap);

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
	minimap_draw_player(img, player.pos, player.dir, minimap);
}

void minimap_draw_map(t_img img, char **map, t_pos p_pos, t_mini_map minimap)
{
	t_pos	init_pos;
	t_pos	draw_pos;
	t_pos	pos;
	int		color;

	p_pos = minimap_get_player_pos(p_pos, minimap);
	init_pos = minimap_get_init_pos(p_pos, minimap);
	pos.y = init_pos.y;
	while (pos.y < init_pos.y + minimap.size.y)
	{
		pos.x = init_pos.x;
		while (pos.x < init_pos.x + minimap.size.x)
		{
			color = minimap_get_pixel_color(pos.x, pos.y, map);
			draw_pos = minimap_get_drawing_pos(pos, init_pos, minimap);
			minimap_draw_pixel(img, draw_pos, color);
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

t_pos minimap_get_drawing_pos(t_pos pos, t_pos offset_correct, t_mini_map minimap)
{
	pos.x += minimap.win_pos.x - offset_correct.x;
	pos.y += minimap.win_pos.y - offset_correct.y;
	return (pos);
}

t_pos minimap_get_player_pos(t_pos pos, t_mini_map minimap)
{
	pos.x = pos.x / minimap.map_scale;
	pos.y = pos.y / minimap.map_scale;
	return (pos);
}

void minimap_draw_player(t_img img, t_pos p_pos, float dir, t_mini_map minimap)
{
	t_pos	point;
	t_pos	init_pos;
	t_pos	draw_pos;
	int		i;

	p_pos = minimap_get_player_pos(p_pos, minimap);
	init_pos = minimap_get_init_pos(p_pos, minimap);
	i = 0;
	while (i <= 360)
	{
		point = get_new_dist_pos(p_pos, i, PLAYER_RADIUS);
		draw_pos = minimap_get_drawing_pos(point, init_pos, minimap);
		minimap_draw_pixel(img, draw_pos, PLAYER_COLOR);
		i += 1;
	}
}
