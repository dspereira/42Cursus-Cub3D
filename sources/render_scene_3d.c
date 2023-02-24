/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene_3d.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcandeia < dcandeia@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 14:48:22 by dsilveri          #+#    #+#             */
/*   Updated: 2023/02/24 14:47:37 by dcandeia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static void	render_ceil_floor(t_img img, int c_rgb, int f_rgb, int mid_y);
static void	render_walls_tex(t_img img, t_ray *rays, t_tex tex);
void		get_tex_data(t_ray ray, int x_pos, t_tex tex, t_tex_data *data);
void		get_d_tex_data(t_ray ray, int x_pos, t_tex tex, t_tex_data *data);

void	render_scene_3d_tex(t_img img, t_player player, t_tex tex)
{
	render_ceil_floor(img, tex.ceil_rgb, tex.floor_rgb, player.dir_y);
	render_walls_tex(img, player.rays, tex);
}

static void	render_ceil_floor(t_img img, int c_rgb, int f_rgb, int mid_y)
{
	t_pos	init_ceil;
	t_pos	init_floor;
	t_value	size;

	size.y = mid_y;
	size.x = WIN_WIDTH;
	draw_fill_rectangle(img, (t_pos){0, 0}, size, c_rgb);
	size.y = WIN_HEIGHT - mid_y;
	draw_fill_rectangle(img, (t_pos){0, size.y}, size, f_rgb);
}

static void	render_walls_tex(t_img img, t_ray *rays, t_tex tex)
{
	int			n_rays;
	int			pos_x;
	t_tex_data	tex_data;

	n_rays = NUMBER_RAYS;
	pos_x = 0;
	while (pos_x < n_rays)
	{
		get_tex_data(rays[pos_x], pos_x, tex, &tex_data);
		draw_line_tex(img, tex_data);
		if (rays[pos_x].is_door)
		{
			get_d_tex_data(rays[pos_x], pos_x, tex, &tex_data);
			draw_door_tex(img, tex_data);
		}
		pos_x++;
	}
}

void	get_tex_data(t_ray ray, int x_pos, t_tex tex, t_tex_data *data)
{
	data->win_start_pos.x = x_pos;
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
}

void	get_d_tex_data(t_ray ray, int x_pos, t_tex tex, t_tex_data *data)
{
	data->win_start_pos.x = x_pos;
	data->height = ((int)((WIN_HEIGHT) / ray.door_dist));
	data->win_start_pos.y = (WIN_HEIGHT / 2) - (data->height / 2);
	data->map_wall_pos = ray.map_door_pos;
	if (ray.door_tex == 'G')
		data->tex = tex.doors[DOOR_CLOSE];
	else if (ray.door_tex == 'H' || ray.door_tex == 'h')
		data->tex = tex.doors[DOOR_OPEN_1];
	else if (ray.door_tex == 'I' || ray.door_tex == 'i')
		data->tex = tex.doors[DOOR_OPEN_2];
	else if (ray.door_tex == 'J' || ray.door_tex == 'j')
		data->tex = tex.doors[DOOR_OPEN_3];
	else if (ray.door_tex == 'K' || ray.door_tex == 'k')
		data->tex = tex.doors[DOOR_OPEN_4];
	else if (ray.door_tex == 'L' || ray.door_tex == 'l')
		data->tex = tex.doors[DOOR_OPEN_5];
	else if (ray.door_tex == 'M' || ray.door_tex == 'm')
		data->tex = tex.doors[DOOR_OPEN_6];
	else if (ray.door_tex == 'N' || ray.door_tex == 'n')
		data->tex = tex.doors[DOOR_OPEN_7];
	else if (ray.door_tex == 'g')
		data->tex = tex.doors[DOOR_OPEN];
}
