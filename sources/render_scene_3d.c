/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene_3d.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 14:48:22 by dsilveri          #+#    #+#             */
/*   Updated: 2023/01/31 14:42:03 by dsilveri         ###   ########.fr       */
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
	int		line_height;
	t_pos	pos;

	pos.y = 0;
	pos.x = 0;
	while (pos.x < NUMBER_RAYS - 1)
	{
		line_height = (int)((WIN_HEIGHT) / rays[pos.x].dist_wall);
		if (line_height > WIN_HEIGHT)
			line_height = WIN_HEIGHT;
		pos.y = (WIN_HEIGHT / 2) - (line_height / 2);
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
