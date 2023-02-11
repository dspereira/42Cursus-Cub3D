/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene_3d.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 14:48:22 by dsilveri          #+#    #+#             */
/*   Updated: 2023/02/11 15:17:29 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static void render_ceil_and_floor(t_img img, int mid_pos_y);
static void render_walls(t_img img, t_ray *rays, int mid_pos_y);

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
		if (rays[pos.x].side == -1)
			draw_vertical_line(img, pos, line_height, RED_COLOR);
		if (rays[pos.x].side == 2)
			draw_vertical_line(img, pos, line_height, BLUE_COLOR);
		if (rays[pos.x].side == -2)
			draw_vertical_line(img, pos, line_height, YELLOW_COLOR);
		pos.x++;
	}
}
