/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 15:09:29 by dsilveri          #+#    #+#             */
/*   Updated: 2023/01/29 19:08:41 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

//static void			raycast(t_ray *ray, t_pos p_pos, char **map);
static void raycast(t_ray *ray, t_pos p_pos, char **map, float p_dir);
static t_value		ray_cast_get_step(t_ray ray);
static t_value_dec	ray_cast_get_leng(t_ray ray, t_pos map_pos, t_pos p_pos);
static void			set_distace_win(t_ray *ray, t_pos map_pos, t_pos p_pos);

static void update_dist_to_wall(t_ray *ray, t_value_dec ray_len, float p_dir);

void raycast_all(t_player *player, char **map)
{
	int	n_rays;
	int	i;

	n_rays = CAMERA_ANGLE / DIST_BTW_ANGLE;
	i = -1;
	while (++i < n_rays)
		raycast(&(player->rays[i]), player->pos, map,player->dir);
}

static void raycast(t_ray *ray, t_pos p_pos, char **map, float p_dir)
{
	t_value		step;
	t_value_dec	ray_length;
	t_pos		map_pos;

	map_pos = get_map_pos(p_pos);
	step = ray_cast_get_step(*ray);
	ray_length = ray_cast_get_leng(*ray, map_pos, p_pos);
	while (!map[map_pos.y][map_pos.x])
	{
		if (ray_length.x < ray_length.y){
			map_pos.x += step.x;
			ray_length.x += ray->sx;
			ray->side = 1 * step.x;
		}
		else {
			map_pos.y += step.y;
			ray_length.y += ray->sy;
			ray->side = 2 * step.y;
		}
	}
	/*if (ray->side == 1 || ray->side == -1)
		ray->dist_wall = (ray_length.x - ray->sx);
	if (ray->side == 2 || ray->side == -2)
		ray->dist_wall = (ray_length.y - ray->sy);*/
	
	update_dist_to_wall(ray, ray_length, p_dir);
	set_distace_win(ray, map_pos, p_pos);
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

static t_value_dec ray_cast_get_leng(t_ray ray, t_pos map_pos, t_pos p_pos)
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
	if (ray->side == 1) 
		final_pos.x = win_pos.x;
	else if (ray->side == 2) 
		final_pos.y = win_pos.y;
	else if (ray->side == -2) 
		final_pos.y = win_pos.y + square_size;
	else if (ray->side == -1)
		final_pos.x = win_pos.x + square_size;
	if (ray->side == 1) 
		ray->length_win = (final_pos.x - p_pos.x) * ray->sx;
	else if (ray->side == 2) 
		ray->length_win = (final_pos.y - p_pos.y) * ray->sy;
	else if (ray->side == -2) 
		ray->length_win = (p_pos.y - final_pos.y) * ray->sy;
	else if (ray->side == -1) 
		ray->length_win =  (p_pos.x - final_pos.x) * ray->sx;	
}

static void update_dist_to_wall(t_ray *ray, t_value_dec ray_len, float p_dir)
{
	float	angle;
	double	distance;

	if (ray->side == 1 || ray->side == -1)
		distance = (ray_len.x - ray->sx);
	if (ray->side == 2 || ray->side == -2)
		distance = (ray_len.y - ray->sy);

	angle = p_dir - ray->dir;
	if (angle > CAMERA_ANGLE / 2)
		angle = p_dir + 360 - ray->dir;
	ray->dist_wall = distance * cos_degree(angle);
}
