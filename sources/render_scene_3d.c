/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene_3d.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcandeia < dcandeia@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 14:48:22 by dsilveri          #+#    #+#             */
/*   Updated: 2023/02/17 11:19:48 by dcandeia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static void render_ceil_and_floor(t_img img, int mid_pos_y);
static void render_ceil_and_floor_rgb(t_img img, int ceil_rgb, int floor_rgb);
static void render_walls(t_img img, t_ray *rays, int mid_pos_y);
void get_wall_data(t_ray ray, int win_x_pos, t_tex tex, t_wall_data *data);

void render_scene_3d(t_img img, t_player player)
{
	render_ceil_and_floor(img, player.dir_y);
	render_walls(img, player.rays, player.dir_y);
}

static void render_ceil_and_floor(t_img img, int mid_pos_y)
{
	t_pos	init_ceil;
	t_pos	init_floor;
	t_value	size;

	size.y = mid_pos_y;
	size.x = WIN_WIDTH;	
	draw_fill_rectangle(img, (t_pos){0, 0}, size, CEIL_COLOR);
	size.y = WIN_HEIGHT - mid_pos_y;
	draw_fill_rectangle(img, (t_pos){0, mid_pos_y}, size, FLOOR_COLOR);
}

static void render_walls(t_img img, t_ray *rays, int mid_pos_y)
{
	int		line_height;
	t_pos	pos;
	t_value size;
	int		n_rays;
	int		side;

	n_rays = NUMBER_RAYS - 1;
	pos.y = 0;
	pos.x = 0;
	while (pos.x < n_rays)
	{
		line_height = (int)((WIN_HEIGHT) / rays[pos.x].dist_wall);
		pos.y = mid_pos_y - (line_height / 2);
		if (rays[pos.x].side == 1)
			draw_vertical_line(img, pos, line_height, GREEN_COLOR);
		if (rays[pos.x].side == WE_SIDE)
			draw_vertical_line(img, pos, line_height, RED_COLOR);
		if (rays[pos.x].side == SO_SIDE)
			draw_vertical_line(img, pos, line_height, BLUE_COLOR);
		if (rays[pos.x].side == NO_SIDE)
			draw_vertical_line(img, pos, line_height, YELLOW_COLOR);
		pos.x++;
	}
} 

static void render_walls_tex(t_img img, t_ray *rays, t_tex tex)
{
	int			n_rays;
	int			pos_x;
	t_wall_data	wall_data;
	
	n_rays = NUMBER_RAYS;
	pos_x = 0;
	while (pos_x < n_rays)
	{
		get_wall_data(rays[pos_x], pos_x, tex, &wall_data);
		draw_line_tex(img, wall_data);
		pos_x++;
	}
}

void get_wall_data(t_ray ray, int win_x_pos, t_tex tex, t_wall_data *data)
{
	data->win_start_pos.x = win_x_pos;
	data->height = (int)((WIN_HEIGHT) / ray.dist_wall);
	data->win_start_pos.y = (WIN_HEIGHT / 2) - (data->height / 2);
	data->map_wall_pos = ray.map_wall_pos;
	if (ray.door_side_wall != 0 && ray.side == ray.door_side_wall)
		data->tex = tex.door_side;
	else if (ray.side == EA_SIDE)
		data->tex = tex.ea;
	else if (ray.side == WE_SIDE)
		data->tex = tex.we;
	else if (ray.side == SO_SIDE)
		data->tex = tex.so;
	else if (ray.side == NO_SIDE)
		data->tex = tex.no;
	if (ray.is_door)
	{
		data->height = (int)((WIN_HEIGHT) / ray.door_dist);
		data->win_start_pos.y = (WIN_HEIGHT / 2) - (data->height / 2);
		data->map_wall_pos = ray.map_door_pos;
		data->tex = tex.door;
	}
}

static void render_ceil_and_floor_rgb(t_img img, int ceil_rgb, int floor_rgb)
{
	t_pos	init_ceil;
	t_pos	init_floor;
	t_value	size;

	size.y = WIN_HEIGHT / 2;
	size.x = WIN_WIDTH;	
	draw_fill_rectangle(img, (t_pos){0, 0}, size, ceil_rgb);
	draw_fill_rectangle(img, (t_pos){0, size.y}, size, floor_rgb);
}

void render_scene_3d_tex(t_img img, t_player player, t_tex tex)
{
	//render_ceil_and_floor(img);
	render_ceil_and_floor_rgb(img, tex.ceil_rgb, tex.floor_rgb);
	//render_walls(img, player.rays);
	render_walls_tex(img, player.rays, tex);
}