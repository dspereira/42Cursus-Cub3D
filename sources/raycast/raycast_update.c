/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_update.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 18:17:55 by dsilveri          #+#    #+#             */
/*   Updated: 2023/03/06 17:02:11 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static void	update_map_pos(t_pos *m_pos, t_value step, t_value_dec ray_len);
static void	update_side(int *side, t_value step, t_value_dec ray_len);
static void	update_ray_leng(t_value_dec *ray_len, t_ray ray);

void	raycast_update(t_ray *ray, t_pos *m_pos, t_value_dec *ray_l, t_value step)
{
	update_map_pos(m_pos, step, *ray_l);
	update_side(&ray->side, step, *ray_l);
	update_ray_leng(ray_l, *ray);
}

static void	update_map_pos(t_pos *m_pos, t_value step, t_value_dec ray_len)
{
	if (ray_len.x < ray_len.y)
		m_pos->x += step.x;
	else
		m_pos->y += step.y;
}

static void	update_side(int *side, t_value step, t_value_dec ray_len)
{
	if (ray_len.x < ray_len.y)
	{
		if (step.x < 0)
			*side = WE_SIDE;
		else
			*side = EA_SIDE;
	}
	else
	{
		if (step.y < 0)
			*side = NO_SIDE;
		else
			*side = SO_SIDE;
	}
}

static void	update_ray_leng(t_value_dec *ray_len, t_ray ray)
{
	if (ray_len->x < ray_len->y)
		ray_len->x += ray.sx;
	else
		ray_len->y += ray.sy;
}
