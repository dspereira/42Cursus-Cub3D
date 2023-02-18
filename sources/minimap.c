/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:44:56 by dcandeia          #+#    #+#             */
/*   Updated: 2023/02/18 15:48:31 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	minimap_draw_map(t_img img, char **map, t_pos p_pos, t_mini_map minimap);
t_pos	minimap_get_map_pos(t_pos pos);
unsigned int minimap_get_pixel_color(int x, int y, char **map);
t_pos minimap_get_init_pos(t_pos p_pos, t_mini_map minimap);
t_pos minimap_get_drawing_pos(t_pos pos, t_pos offset_correct, t_mini_map minimap);
t_pos minimap_get_player_pos(t_pos pos, t_mini_map minimap);
void minimap_draw_player_circle(t_img img, t_pos p_pos, float dir);
void minimap_draw_player_arrow(t_img img, t_pos p_pos, float dir);
void minimap_draw_player(t_img img, float dir, t_mini_map minimap);

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
	minimap.player_pos.x = minimap.win_pos.x + minimap.half_size.x;
	minimap.player_pos.y = minimap.win_pos.x + minimap.half_size.x;
	minimap.map_scale = (float) WIN_WIDTH / MAP_WIDTH / MINIMAP_SQUARE_SIZE;
	return (minimap);
}

void minimap_render(t_img img, char **map, t_player player, t_mini_map minimap)
{
	minimap_draw_map(img, map, player.pos, minimap);
	minimap_draw_player(img, player.dir, minimap);
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
			if (color != MINIMAP_COLOR_NONE)
				draw_pixel(img, draw_pos.x, draw_pos.y, color);
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
		return (MINIMAP_COLOR_NONE);
	else if (map[pos.y][pos.x] == ' ')
		return (MINIMAP_COLOR_NONE);
	else if (map[pos.y][pos.x] == '1')
		return (MINIMAP_COLOR_WALL);
	else
		return (MINIMAP_COLOR_GROUND);
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

void minimap_draw_player(t_img img, float dir, t_mini_map minimap)
{
	minimap_draw_player_circle(img, minimap.player_pos, dir);
	minimap_draw_player_arrow(img, minimap.player_pos, dir);
}

void minimap_draw_player_circle(t_img img, t_pos p_pos, float dir)
{
	t_pos point;
	int	i;

	i = -1;
	while (++i < 360)
	{
		point = get_new_dist_pos(p_pos, i, PLAYER_RADIUS);
		draw_line(img, p_pos, point, MINIMAP_PLAYER_COLOR);
		point = get_new_dist_pos(p_pos, i, PLAYER_RADIUS + 1);
		draw_pixel(img, point.x, point.y, MINIMAP_ARROW_COLOR);
		point = get_new_dist_pos(p_pos, i, PLAYER_RADIUS + 2);
		draw_pixel(img, point.x, point.y, MINIMAP_ARROW_COLOR);
	}
}

void minimap_draw_player_arrow(t_img img, t_pos p_pos, float dir)
{
	t_pos	new_pos;
	t_pos	point;
	float	new_dir;
	float 	i;

	new_pos = get_new_dist_pos(p_pos, dir, PLAYER_RADIUS + MINIMAP_ARROW_SIZE);
	new_dir = normalizeAngles(dir + 180);
	i = new_dir;
	while (i <= new_dir + 28)
	{
		point = get_new_dist_pos(new_pos, i, MINIMAP_ARROW_SIZE - 1);
		draw_line(img, new_pos, point, MINIMAP_ARROW_COLOR);
		i ++;
	}
	i = new_dir;
	while (i >= new_dir - 28)
	{
		point = get_new_dist_pos(new_pos, i, MINIMAP_ARROW_SIZE - 1);
		draw_line(img, new_pos, point, MINIMAP_ARROW_COLOR);
		i--;
	}
}
