/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 15:52:23 by dsilveri          #+#    #+#             */
/*   Updated: 2023/01/28 14:59:22 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"


static void set_distace_win(t_ray *ray, t_pos map_pos, t_pos p_pos);

static t_value ray_cast_get_step(t_ray ray);
static t_value_dec ray_cast_get_init_leng(t_ray ray, t_pos map_pos, t_pos p_pos);

void ray_init(t_ray *ray, float dir)
{
	ray_update_dir(ray, dir);
}

void ray_update_dir(t_ray *ray, float dir)
{
	ray->dir = normalizeAngles(dir);
	ray->cos = cos_degree(ray->dir);
	ray->sin = sin_degree(ray->dir) * -1;
	ray->sx = 1 / ray->cos;
	ray->sy = 1 / ray->sin;
	if (ray->dir == 0 || ray->dir == 180)
	{
		ray->sin = 0.0;
		ray->sy = 1000000;
	}
	if (ray->dir == 90 || ray->dir == 270)
	{
		ray->cos = 0.0; 
		ray->sx = 1000000;
	}
	if (ray->sx < 0)
		ray->sx *= -1;
	if (ray->sy < 0)
		ray->sy *= -1;
}

void ray_cast(t_ray *ray, t_pos pos, char **map)
{
	t_value		step;
	t_value_dec	ray_length;
	t_pos		map_pos;
	int			side;
	
	map_pos = get_map_pos(pos);
	step = ray_cast_get_step(*ray);
	ray_length = ray_cast_get_init_leng(*ray, map_pos, pos);
	while (!map[map_pos.y][map_pos.x])
	{
		if (ray_length.x < ray_length.y){
			map_pos.x += step.x;
			ray_length.x += ray->sx;
			side = 1 * step.x;
		}
		else {
			map_pos.y += step.y;
			ray_length.y += ray->sy;
			side = 2 * step.y;
		}
	}
	ray->side = side;
	set_distace_win(ray, map_pos, pos);
}

static t_value ray_cast_get_step(t_ray ray)
{
	t_value step;

	step.x = 1;
	step.y = 1;
	if (ray.cos < 0)
		step.x = -1;
	if (ray.sin < 0)
		step.y = -1;
	return (step);
}

static t_value_dec ray_cast_get_init_leng(t_ray ray, t_pos map_pos, t_pos p_pos)
{
	t_value_dec	leng;
	t_pos_dec	map_pos_dec;

	map_pos_dec = get_map_pos_decimal(p_pos);
	if (ray.cos < 0)
		leng.x = (map_pos_dec.x - (double)map_pos.x) * ray.sx;
	else 
		leng.x = ((double)(map_pos.x + 1) - map_pos_dec.x) * ray.sx;
	if (ray.sin < 0)
		leng.y = (map_pos_dec.y - (double)map_pos.y) * ray.sy;
	else
		leng.y = ((double)(map_pos.y + 1) - map_pos_dec.y) * ray.sy;
	return (leng);
}

static void set_distace_win(t_ray *ray, t_pos map_pos, t_pos p_pos)
{
	t_pos	win_pos;
	t_pos	final_pos;
	int		square_size;

    square_size = WIN_HEIGHT / MAP_HEIGHT;
	win_pos = get_win_pos(map_pos);
	if (ray->side == 1) {
		final_pos.x = win_pos.x;
		ray->length_win = (final_pos.x - p_pos.x) * ray->sx;
	}
	else if (ray->side == 2) {
		final_pos.y = win_pos.y;
		ray->length_win = (final_pos.y - p_pos.y) * ray->sy;
	}
	else if (ray->side == -2) {
		final_pos.y = win_pos.y + square_size;
		ray->length_win = (p_pos.y - final_pos.y) * ray->sy;
	}
	else if (ray->side == -1) {
		final_pos.x = win_pos.x + square_size;
		ray->length_win =  (p_pos.x - final_pos.x) * ray->sx;
	}
	if (ray->length_win < 0)
		ray->length_win *= -1;
}
