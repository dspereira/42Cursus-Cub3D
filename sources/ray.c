/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 15:52:23 by dsilveri          #+#    #+#             */
/*   Updated: 2023/01/28 15:19:57 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static double get_cos_btw_ray_player(float ray_dir, float p_dir);

void ray_init(t_ray *ray, float dir, float p_dir)
{
	ray_update_dir(ray, dir);
	ray->cos2 = get_cos_btw_ray_player(ray->dir, p_dir);
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

static double get_cos_btw_ray_player(float ray_dir, float p_dir)
{
	float	angle;

	angle = p_dir - ray_dir;
	if (angle > CAMERA_ANGLE / 2)
		angle = p_dir + 360 - ray_dir;
	return (cos_degree(angle));
}

/*
static void update_dist_to_wall(t_ray *ray, t_value_dec ray_len, float p_dir)
{
	float	angle;
	double	distance;

	angle = p_dir - ray->dir;
	if (angle > CAMERA_ANGLE / 2)
		angle = p_dir + 360 - ray->dir;
	ray->dist_wall = distance * cos_degree(angle);
}

*/