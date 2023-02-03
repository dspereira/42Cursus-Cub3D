/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene_2d.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 16:07:04 by dsilveri          #+#    #+#             */
/*   Updated: 2023/01/31 12:34:37 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static void render_map(t_img img, char **map);
static void render_player(t_img img, t_player player, char **map);
static void render_background(t_img img, int color);

void render_scene_2d(t_img img, t_player player, char **map)
{
	render_background(img, 0x0021130d);
	render_map(img, map);
	render_player(img, player, map);
}

static void render_map(t_img img, char **map)
{
	t_pos	map_pos;
	t_pos	win_pos;
	int		square_size;

	square_size = WIN_HEIGHT / MAP_HEIGHT;
	map_pos.y = 0;
	while (map_pos.y < MAP_HEIGHT) 
	{
		map_pos.x = 0;
		while (map_pos.x < MAP_WIDTH)
		{
			win_pos.x = map_pos.x * square_size;
			win_pos.y = map_pos.y * square_size;
			if (map[map_pos.y][map_pos.x])
				draw_fill_square(img, win_pos, square_size, WALL_COLOR);
			else
				draw_stroke_square(img, win_pos, square_size, WALL_COLOR);
			map_pos.x++;
		}
		map_pos.y++;
	}
}

static void render_player(t_img img, t_player player, char **map)
{
	int		i;
	//int		n_rays;
	t_pos	p_pos;
	t_pos	ray_end_pos;

	//n_rays = CAMERA_ANGLE / DIST_BTW_ANGLE;
	p_pos.x = player.pos.x - PLAYER_SIZE / 2;
	p_pos.y = player.pos.y - PLAYER_SIZE / 2;
	draw_fill_square(img, p_pos, PLAYER_SIZE, PLAYER_COLOR);
	i = 0;
	while (i < NUMBER_RAYS)
	{
		ray_end_pos = get_new_pos(player.pos, player.rays[i].cos, player.rays[i].sin,  player.rays[i].length_win);
		draw_line(img, player.pos, ray_end_pos, 0x00FF0000);
		i++;
	}
}

static void render_background(t_img img, int color)
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
