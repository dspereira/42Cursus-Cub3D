/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:44:56 by dcandeia          #+#    #+#             */
/*   Updated: 2023/02/19 18:40:35 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static void		minimap_draw_map(t_img img, char **map, t_pos p_pos, t_mini_map minimap);
static t_pos	minimap_get_map_pos(t_pos pos);
static int		minimap_get_pixel_color(t_pos pos, char **map);
static t_pos 	minimap_get_init_pos(t_pos p_pos, t_mini_map minimap);
static t_pos 	minimap_get_drawing_pos(t_pos pos, t_pos offset_correct, t_mini_map minimap);
static t_pos	minimap_get_player_pos(t_pos pos, t_mini_map minimap);
static void		minimap_draw_player_circle(t_img img, t_pos p_pos, float dir);
static void		minimap_draw_player_arrow(t_img img, t_pos p_pos, float dir);
static void		minimap_draw_player(t_img img, t_pos p_pos, float dir, t_mini_map minimap);


static t_pos	get_player_pos_minimap(t_pos p_pos, t_mini_map minimap);
static t_pos	get_player_pos_map_scaled(t_pos pos, t_mini_map minimap);
static void 	draw_minimap(t_img img, char **map, t_pos p_pos, t_mini_map minimap);
static t_pos	get_minimap_init_pos(t_pos p_pos, t_mini_map minimap);

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
	//minimap_draw_map(img, map, player.pos, minimap);
	draw_minimap(img, map, player.pos, minimap);
	minimap_draw_player(img, player.pos, player.dir, minimap);
}


static void draw_minimap(t_img img, char **map, t_pos p_pos, t_mini_map minimap)
{
	t_pos	init_pos;
	t_pos	draw_pos;
	t_pos	pos;
	int		color;

	p_pos = minimap_get_player_pos(p_pos, minimap);
	init_pos = get_minimap_init_pos(p_pos, minimap);
	pos.y = init_pos.y;
	while (pos.y < init_pos.y + minimap.size.y)
	{
		pos.x = init_pos.x;
		while (pos.x < init_pos.x + minimap.size.x)
		{
			color = minimap_get_pixel_color(pos, map);
			draw_pos = minimap_get_drawing_pos(pos, init_pos, minimap);
			if (color != MINIMAP_COLOR_NONE)
			draw_pixel(img, draw_pos.x, draw_pos.y, color);
			pos.x++;
		}
		pos.y++;
	}
}

/*
static void minimap_draw_map(t_img img, char **map, t_pos p_pos, t_mini_map minimap)
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
			color = minimap_get_pixel_color(pos, map);
			draw_pos = minimap_get_drawing_pos(pos, init_pos, minimap);
			if (color != MINIMAP_COLOR_NONE)
			draw_pixel(img, draw_pos.x, draw_pos.y, color);
			pos.x++;
		}
		pos.y++;
	}
}
*/

static t_pos get_minimap_init_pos(t_pos p_pos, t_mini_map minimap)
{
	t_pos	pos;
	int		y_top;
	int		y_bot;
	int		x_left;
	int		x_right;

	pos.x = p_pos.x - minimap.half_size.x;
	pos.y = p_pos.y - minimap.half_size.y;
	y_top = pos.y;
	y_bot = pos.y + minimap.size.y;
	x_left = pos.x;
	x_right = pos.x + minimap.size.x;
	if (y_top < 0)
		pos.y = 0;
	if (y_bot >= MINIMAP_SQUARE_SIZE * MAP_HEIGHT)
		pos.y = MINIMAP_SQUARE_SIZE * MAP_HEIGHT - minimap.size.y;	
	if (x_left < 0)
		pos.x = 0;
	if (x_right >= MINIMAP_SQUARE_SIZE * MAP_WIDTH)
		pos.x = MINIMAP_SQUARE_SIZE * MAP_WIDTH - minimap.size.x;
	return (pos);
}

/*
static t_pos minimap_get_init_pos(t_pos p_pos, t_mini_map minimap)
{
	t_pos	pos;
	int		y_top;
	int		y_bot;
	int		x_left;
	int		x_right;

	pos.x = p_pos.x - minimap.half_size.x;
	pos.y = p_pos.y - minimap.half_size.y;
	y_top = pos.y;
	y_bot = pos.y + minimap.size.y;
	x_left = pos.x;
	x_right = pos.x + minimap.size.x;
	if (y_top < 0)
		pos.y = 0;
	if (y_bot >= MINIMAP_SQUARE_SIZE * MAP_HEIGHT)
		pos.y = MINIMAP_SQUARE_SIZE * MAP_HEIGHT - minimap.size.y;	
	if (x_left < 0)
		pos.x = 0;
	if (x_right >= MINIMAP_SQUARE_SIZE * MAP_WIDTH)
		pos.x = MINIMAP_SQUARE_SIZE * MAP_WIDTH - minimap.size.x;
	return (pos);
}
*/

static int minimap_get_pixel_color(t_pos pos, char **map)
{
	pos = minimap_get_map_pos(pos);
	if (pos.x < 0 || pos.y < 0 || pos.x >= MAP_WIDTH || pos.y >= MAP_HEIGHT)
		return (MINIMAP_COLOR_NONE);
	else if (map[pos.y][pos.x] == ' ')
		return (MINIMAP_COLOR_WALL);
	else if (map[pos.y][pos.x] == '1')
		return (MINIMAP_COLOR_WALL);
	else
		return (MINIMAP_COLOR_GROUND);
}

static t_pos minimap_get_map_pos(t_pos pos)
{
	if (pos.x > 0)
    	pos.x = pos.x / MINIMAP_SQUARE_SIZE;
	if (pos.y > 0)
		pos.y = pos.y / MINIMAP_SQUARE_SIZE;
	return(pos);
}

/*
static t_pos minimap_get_drawing_pos(t_pos pos, t_pos p_pos, t_mini_map minimap)
{
	t_pos minimap_init_pos;

	minimap_init_pos = minimap_get_init_pos(p_pos, minimap);
	pos.x += minimap.win_pos.x - minimap_init_pos.x;
	pos.y += minimap.win_pos.y - minimap_init_pos.y;
	return (pos);
}
*/

static t_pos minimap_get_drawing_pos(t_pos pos, t_pos offset_correct, t_mini_map minimap)
{
	pos.x += minimap.win_pos.x - offset_correct.x;
	pos.y += minimap.win_pos.y - offset_correct.y;
	return (pos);
}


static t_pos get_player_pos_minimap(t_pos p_pos, t_mini_map minimap)
{
	t_pos minimap_init_pos;

	p_pos = get_player_pos_map_scaled(p_pos, minimap);
	minimap_init_pos = get_minimap_init_pos(p_pos, minimap);
	p_pos.x += minimap.win_pos.x - minimap_init_pos.x;
	p_pos.y += minimap.win_pos.y - minimap_init_pos.y;
	return (p_pos);
}

static t_pos get_player_pos_map_scaled(t_pos pos, t_mini_map minimap)
{
	pos.x = pos.x / minimap.map_scale;
	pos.y = pos.y / minimap.map_scale;
	return (pos);
}

static t_pos minimap_get_player_pos(t_pos pos, t_mini_map minimap)
{
	pos.x = pos.x / minimap.map_scale;
	pos.y = pos.y / minimap.map_scale;
	return (pos);
}

static void minimap_draw_player(t_img img, t_pos p_pos, float dir, t_mini_map minimap)
{
	p_pos = get_player_pos_minimap(p_pos, minimap);
	minimap_draw_player_circle(img, p_pos, dir);
	minimap_draw_player_arrow(img, p_pos, dir);
}

/*
static void minimap_draw_player(t_img img, t_pos p_pos, float dir, t_mini_map minimap)
{
	t_pos	init_pos;

	p_pos = minimap_get_player_pos(p_pos, minimap);
	init_pos = minimap_get_init_pos(p_pos, minimap);
	p_pos = minimap_get_drawing_pos(p_pos, init_pos, minimap);
	minimap_draw_player_circle(img, p_pos, dir);
	minimap_draw_player_arrow(img, p_pos, dir);
}
*/

static void minimap_draw_player_circle(t_img img, t_pos p_pos, float dir)
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

static void minimap_draw_player_arrow(t_img img, t_pos p_pos, float dir)
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
