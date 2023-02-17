/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:44:56 by dcandeia          #+#    #+#             */
/*   Updated: 2023/02/17 10:14:30 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static void	render_map(t_img img, char **map);
static void	render_background(t_img img);
static void	render_player(t_img img, t_player player, char **map);
static void	render_player_circle(t_img img, t_player player, char **map);
static void	draw_line_1(t_img img, t_pos init, t_pos end, char **map, float angle);

///////////////////////////////////////////////////////////////

void	minimap_draw_map(t_img img, char **map, t_pos p_pos);
void	minimap_set_frame_pos(t_pos p_pos, t_pos *init_pos, t_pos *end_pos);
t_pos	minimap_get_map_pos(t_pos pos);
unsigned int minimap_get_pixel_color(int x, int y, char **map);
void minimap_draw_line(t_img img, t_pos init_pos, int height);
unsigned int minimap_draw_pixel(t_img img, t_pos pos, int color);
t_pos minimap_get_init_pos(t_pos p_pos);
t_pos minimap_get_shifted_pos(t_pos pos, t_pos init_pos);


void minimap_render(t_img img, char **map, t_player player)
{
	minimap_draw_map(img, map, player.pos);
}

void minimap_draw_map(t_img img, char **map, t_pos p_pos)
{
	t_pos	init_pos;
	t_pos	pos;
	int		color;

	init_pos = minimap_get_init_pos(p_pos);

	//fazer loop por todas as posicoes
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
	int	offset;

	offset = 200;
	pos.x += offset - init_pos.x;
	pos.y += offset - init_pos.y;
	return (pos);
}







/*
void minimap_draw_line(t_img img, t_pos init_pos, int height)
{
	int i;

	i = -1;
	while (++i < height)
	{
		if ((init_pos.x >= 0 && init_pos.x <= WIN_WIDTH) && (init_pos.y >= 0 && init_pos.y <= WIN_HEIGHT))
			draw_pixel(img, init_pos.x, init_pos.y, );
		in*/





//////////////////////////
/*void	minimap_render(t_img img, t_player player, char **map)
{
	//render_background(img);
	//render_map(img, map);
	//render_player_circle(img, player, map);
	//render_player_circle(img, player, map);
}*/

/*
static void	render_map(t_img img, char **map)
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

static void	render_player_circle(t_img img, t_player player, char **map)
{
	t_pos	p_pos;
	t_pos	point_pos;
	float	i;
	float	resize_scale;	

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
		point_pos = get_new_dist_pos(p_pos, i, 100);
		//draw_pixel(img, point_pos.x, point_pos.y, PLAYER_COLOR);
		draw_line_1(img, p_pos, point_pos, map, i);
		// draw_line_1(img, p_pos, point_pos, map, abs(player.dir + 90));

		i += 0.01;
		//i++;
	}
	//draw_line(img, p_pos, get_new_dist_pos(p_pos, player.dir, 15), PLAYER_COLOR);
}

static void draw_pixel_1(t_img img, int x, int y, int color, t_pos init_pos_player)
{
	int *pixel;

	x = (x + 200) - init_pos_player.x;
	y = (y + 200) - init_pos_player.y;
	if (x >= WIN_WIDTH || y >= WIN_HEIGHT || x < 0 || y < 0)
		return ;
	pixel = (int *)(img.addr + (img.line_len * y) + (x * img.bpp / 8));
	*pixel = (unsigned int)color;
}

static t_pos get_map_pos_1(t_pos pos)
{
	if (pos.x > 0)
    	pos.x = pos.x / MINIMAP_SQUARE_SIZE;
	if (pos.y > 0)
		pos.y = pos.y / MINIMAP_SQUARE_SIZE;
}

static unsigned int get_pixel_map_color(int x, int y, char **map)
{
	t_pos pos;

	pos.x = x;
	pos.y = y;
	pos = get_map_pos_1(pos);
	if (pos.x < 0 || pos.y < 0 || pos.x >= MAP_WIDTH || pos.y >= MAP_HEIGHT)
		return (BGD_MINIMAP_COLOR);
	if (map[pos.y][pos.x] == '1')
		return (WALL_COLOR);
	else
		return (BGD_MINIMAP_COLOR);
}

static t_pos transform_pos(t_pos init, t_pos_dec pos, float angle)
{
	t_pos new_pos;
	
	new_pos.x = round((pos.x - init.x) * cos_degree(angle) + init.x);
	new_pos.y = round(-(pos.y - init.y) * sin_degree(angle) + init.y);
	return (new_pos);
}

static void draw_line_1(t_img img, t_pos init, t_pos end, char **map, float angle)
{
	int			steps;
	t_value		delta;
	t_value_dec	inc;
	t_pos_dec	pos;

	t_pos new_pos;

	float a;

	delta.x = end.x - init.x;
	delta.y = end.y - init.y;
	if (math_abs(delta.x) >= math_abs(delta.y))
		steps = math_abs(delta.x);
	else 
		steps = math_abs(delta.y);
	inc.x = (double)delta.x / steps;
	inc.y = (double)delta.y / steps;
	pos.x = init.x;
	pos.y = init.y;
	while (steps-- > 0)
	{

		//new_pos = transform_pos(init, pos, angle);
		//draw_pixel_1(img, new_pos.x, new_pos.y, get_pixel_map_color(pos.x, pos.y, map), init);
		draw_pixel_1(img, pos.x, pos.y, get_pixel_map_color(pos.x, pos.y, map), init);
		pos.x += inc.x;
		pos.y += inc.y;
	}
	draw_pixel_1(img, end.x, end.y, get_pixel_map_color(end.x, end.y, map), init);
}
*/