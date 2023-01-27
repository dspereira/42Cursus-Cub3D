/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 15:52:23 by dsilveri          #+#    #+#             */
/*   Updated: 2023/01/27 17:09:39 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

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
