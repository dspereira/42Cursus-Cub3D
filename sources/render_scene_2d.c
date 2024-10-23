/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene_2d.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcandeia <dcandeia@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 16:07:04 by dsilveri          #+#    #+#             */
/*   Updated: 2023/03/08 14:58:58 by dcandeia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include <math.h>

static double	render_map(t_img img, char **map);
static void	render_player(t_img img, t_player player, float scale);
static void	render_player_circle(t_img img, t_player player);
static void	render_background(t_img img, int color);
static int get_map_width(char **map);
static int get_map_height(char **map);
static int get_square_size(int map_height, int map_width);
static float get_correction_scale_position(int square_size);

void	render_scene_2d(t_img img, t_player player, char **map)
{
	float scale;

	render_background(img, 0x0021130d);
	scale = render_map(img, map);
	//render_player_circle(img, player);
	render_player(img, player, scale);
}

// to calculate the square with a size of 40
static double	render_map(t_img img, char **map)
{
	t_pos	map_pos;
	t_pos	win_pos;
	int		square_size;
	int		map_width; 
	int		map_height;

	map_height = get_map_height(map);
	map_width = get_map_width(map);

	square_size = get_square_size(map_height, map_width);
	//square_size = 40;

	map_pos.y = 0;
	while (map_pos.y < map_height)
	{
		map_pos.x = 0;
		while (map_pos.x < map_width)
		{
			win_pos.x = map_pos.x * square_size;
			win_pos.y = map_pos.y * square_size;
			if (map[map_pos.y][map_pos.x] != '0')
				draw_fill_square(img, win_pos, square_size, WALL_COLOR);
			map_pos.x++;
		}
		map_pos.y++;
	}
	return get_correction_scale_position(square_size);
}

static void	render_player(t_img img, t_player player, float scale)
{
	int		i;
	t_pos	p_pos;
	t_pos	ray_end_pos;
	t_pos	ray_start;

	float	halfPlayerSize = (float)PLAYER_SIZE / 2;

	ray_start.x = round(player.pos.x * scale);
	ray_start.y = round(player.pos.y * scale);
	p_pos.x = round(ray_start.x - halfPlayerSize);
	p_pos.y = round(ray_start.y - halfPlayerSize);


	draw_fill_square(img, p_pos, PLAYER_SIZE, PLAYER_COLOR);
	i = 0;
	while (i < NUMBER_RAYS)
	{
		ray_end_pos = get_new_pos((t_pos){player.pos.x, player.pos.y}, \
			player.rays[i].cos, player.rays[i].sin, player.rays[i].length_win);
		ray_end_pos.x = round(ray_end_pos.x * scale);
		ray_end_pos.y = round(ray_end_pos.y * scale);
		draw_line(img, ray_start, ray_end_pos, 0x00FF0000);
		i++;
	}
}

static void	render_player_circle(t_img img, t_player player)
{
	t_pos	p_pos;
	t_pos	point_pos;
	float	i;

	p_pos = (t_pos){player.pos.x, player.pos.y};
	i = 0;
	while (i <= 360)
	{
		point_pos = get_new_dist_pos(p_pos, i, PLAYER_RADIUS);
		draw_pixel(img, point_pos.x, point_pos.y, PLAYER_COLOR);
		i += 0.1;
	}
	draw_line(img, p_pos, \
		get_new_dist_pos(p_pos, player.dir, 15), PLAYER_COLOR);
}

static void	render_background(t_img img, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < WIN_HEIGHT)
	{
		j = 0;
		while (j < WIN_WIDTH)
		{
			draw_pixel(img, j, i, color);
			j++;
		}
		i++;
	}	
}

static int get_map_width(char **map)
{
	int i = 0;
	while (map[0][i] != NULL) {
		i++;
	}
	return --i;
}

static int get_map_height(char **map) 
{
	int i = 0;
	while (map[i] != NULL) {
		i++;
	}
	return --i;
}

static int get_square_size(int map_height, int map_width) 
{
	if (map_height < map_width)
		return WIN_HEIGHT / map_height;
	return WIN_WIDTH / map_width;
}

static float get_correction_scale_position(int square_size) 
{
	int normal_size = 40;

	return (float)square_size / normal_size;
}