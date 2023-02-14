/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcandeia < dcandeia@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:44:56 by dcandeia          #+#    #+#             */
/*   Updated: 2023/02/14 17:37:53 by dcandeia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static void render_map(t_img img, char **map);
static void render_background(t_img img);
static void render_player(t_img img, t_player player, char **map);
static void render_player_circle(t_img img, t_player player, char **map);

void minimap_render(t_img img, t_player player, char **map)
{
	render_background(img);
	render_map(img, map);
    
	render_player_circle(img, player, map);
	//render_player_circle(img, player, map);
}

static void render_map(t_img img, char **map)
{
	t_pos	map_pos;
	t_pos	win_pos;

	map_pos.y = 0;
	while (map_pos.y < MAP_HEIGHT)
	{
		map_pos.x = 0;
		while (map_pos.x < MAP_WIDTH)
		{
			//win_pos.x = (map_pos.x * MINIMAP_SQUARE_SIZE) + (WIN_WIDTH / 2) - (MINIMAP_SQUARE_SIZE * MAP_WIDTH/2);
			//win_pos.y = (map_pos.y * MINIMAP_SQUARE_SIZE) + (WIN_HEIGHT / 2) - (MINIMAP_SQUARE_SIZE * MAP_HEIGHT/2);
			win_pos.x = (map_pos.x * MINIMAP_SQUARE_SIZE);
			win_pos.y = (map_pos.y * MINIMAP_SQUARE_SIZE);
            if (map[map_pos.y][map_pos.x] != '0')
				draw_fill_square(img, win_pos, MINIMAP_SQUARE_SIZE, WALL_COLOR);
			map_pos.x++;
		}
		map_pos.y++;
	}
}

static void render_background(t_img img)
{
	int	i;
	int	j;

	//i = (WIN_WIDTH / 2) - (MINIMAP_SQUARE_SIZE * MAP_WIDTH/2);
    i = 0;
	while (i < MINIMAP_SQUARE_SIZE * MAP_HEIGHT)
	{
		//j = (WIN_HEIGHT / 2) - (MINIMAP_SQUARE_SIZE * MAP_HEIGHT/2);
        j = 0;
		while (j < MINIMAP_SQUARE_SIZE * MAP_WIDTH)
		{
			draw_pixel(img, j, i, BGD_MINIMAP_COLOR);
			j++;
		}
		i++;
	}
}

static void render_player(t_img img, t_player player, char **map)
{
	int		i;
	t_pos	p_pos;
	t_pos	ray_end_pos;
    float   resize_scale;

    // square size (WIN_WIDTH / MAP_WIDT) tem de ser alterado para um valor constante
    resize_scale = 2.66;//WIN_WIDTH / MAP_WIDTH / MINIMAP_SQUARE_SIZE;

	p_pos.x = player.pos.x - PLAYER_MINIMAP_SIZE / 2;
	p_pos.y = player.pos.y - PLAYER_MINIMAP_SIZE / 2;

    p_pos.x /= resize_scale;
    p_pos.y /= resize_scale;
    
	draw_fill_square(img, p_pos, PLAYER_MINIMAP_SIZE, PLAYER_COLOR);
	i = 0;
	//while (i < NUMBER_RAYS)
	//{
	//	ray_end_pos = get_new_pos(player.pos, player.rays[i].cos, player.rays[i].sin,  player.rays[i].length_win);
	//	draw_line(img, player.pos, ray_end_pos, 0x00FF0000);
	//	i++;
	//}
}

static void render_player_circle(t_img img, t_player player, char **map)
{
	t_pos	p_pos;
	t_pos	point_pos;
	float 	i;

    float   resize_scale;

    // square size (WIN_WIDTH / MAP_WIDT) tem de ser alterado para um valor constante
    resize_scale = (float) WIN_WIDTH / MAP_WIDTH / MINIMAP_SQUARE_SIZE;

    //printf("valor: %0.5f\n", resize_scale);
	p_pos = player.pos;

    //p_pos.x = player.pos.x - PLAYER_RADIUS / 2;
	//p_pos.y = player.pos.y - PLAYER_RADIUS / 2;

    p_pos.x = p_pos.x / resize_scale;
    p_pos.y = p_pos.y / resize_scale;

	i = 0;
	while (i <= 360)
	{
		point_pos = get_new_dist_pos(p_pos, i, PLAYER_MINIMAP_SIZE);
		//draw_pixel(img, point_pos.x, point_pos.y, PLAYER_COLOR);
        draw_line(img, p_pos, point_pos, PLAYER_COLOR);
        
		i += 0.1;
	}
	draw_line(img, p_pos, get_new_dist_pos(p_pos, player.dir, 15), PLAYER_COLOR);
}
