/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene_3d.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 14:48:22 by dsilveri          #+#    #+#             */
/*   Updated: 2023/01/29 19:37:43 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static void render_ceil_and_floor(t_img img);
static void render_walls(t_img img, t_ray *rays);

void render_scene_3d(t_img img, t_player player)
{
	render_ceil_and_floor(img);
	render_walls(img, player.rays);
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
	int		n_rays;
	int 	i;
	t_value	line_size;
	t_pos	pos;

	n_rays = CAMERA_ANGLE / DIST_BTW_ANGLE;
	line_size.x = WIN_WIDTH / n_rays;
	pos.y = 0;
	pos.x = 0;
	i = 0;

	printf("N rays: %i\n", n_rays);
	printf("line size: %i\n", line_size.x);
	while (i < n_rays)
	{
		line_size.y = (int)((double)WIN_HEIGHT / rays[i].dist_wall);
		pos.x += line_size.x;
		pos.y = (WIN_HEIGHT / 2) - (line_size.y / 2);
		if (rays[i].side == 1)
			draw_fill_rectangle(img, pos, line_size, GREEN_COLOR);
		if (rays[i].side == -1)
			draw_fill_rectangle(img, pos, line_size, RED_COLOR);
		if (rays[i].side == 2)
			draw_fill_rectangle(img, pos, line_size, BLUE_COLOR);
		if (rays[i].side == -2)
			draw_fill_rectangle(img, pos, line_size, YELLOW_COLOR);
		i++;
	}
}