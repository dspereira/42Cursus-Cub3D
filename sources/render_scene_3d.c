/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene_3d.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcandeia <dcandeia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 14:48:22 by dsilveri          #+#    #+#             */
/*   Updated: 2023/02/08 10:04:44 by dcandeia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static void render_ceil_and_floor(t_img img);
static void render_walls(t_img img, t_ray *rays);

static void render_walls_tex(t_img img, t_ray *rays, t_tex tex);
void get_wall_data(t_ray ray, int win_x_pos, t_tex tex, t_wall_data *data);


void render_scene_3d(t_img img, t_player player)
{
	render_ceil_and_floor(img);
	render_walls(img, player.rays);
}

void render_scene_3d_tex(t_img img, t_player player, t_tex tex)
{
	render_ceil_and_floor(img);
	render_walls(img, player.rays);
	render_walls_tex(img, player.rays, tex);
}

static void render_ceil_and_floor(t_img img)
{
	t_pos	init_ceil;
	t_pos	init_floor;
	t_value	size;

	size.y = WIN_HEIGHT / 2;
	size.x = WIN_WIDTH;	
	draw_fill_rectangle(img, (t_pos){0, 0}, size, CEIL_COLOR);
	draw_fill_rectangle(img, (t_pos){0, size.y}, size, FLOOR_COLOR);
}

 static void render_walls(t_img img, t_ray *rays)
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
		if (line_height > WIN_HEIGHT)
			line_height = WIN_HEIGHT;
		pos.y = (WIN_HEIGHT / 2) - (line_height / 2);
		if (rays[pos.x].side == EA_SIDE)
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
	t_pos		pos;
	t_wall_data	wall_data;
	
	n_rays = NUMBER_RAYS - 1;
	pos.y = 0;
	pos.x = 0;
	while (pos.x < n_rays)
	{
		get_wall_data(rays[pos.x], pos.x, tex, &wall_data);	
		draw_line_tex(img, wall_data);
		pos.x++;
	}
}

void get_wall_data(t_ray ray, int win_x_pos, t_tex tex, t_wall_data *data)
{
	data->height = (int)((WIN_HEIGHT) / ray.dist_wall);
	//if (data->height > WIN_HEIGHT)
	//	data->height = WIN_HEIGHT;
	data->win_start_pos.x = win_x_pos;
	data->win_start_pos.y = (WIN_HEIGHT / 2) - (data->height / 2);
	/* if (data->win_start_pos.y < 0) {
		data->win_start_pos.y = 0;
	} */
	
	data->map_wall_pos = ray.map_wall_pos;
	if (ray.side == EA_SIDE)
		data->tex = tex.ea;
	else if (ray.side == WE_SIDE)
		data->tex = tex.we;
	else if (ray.side == SO_SIDE)
		data->tex = tex.so;
	else if (ray.side == NO_SIDE)
		data->tex = tex.no;
}
