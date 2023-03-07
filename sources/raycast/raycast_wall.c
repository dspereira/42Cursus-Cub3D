/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_wall.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 12:46:35 by dsilveri          #+#    #+#             */
/*   Updated: 2023/03/07 14:18:37 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	raycast_wall_set_dist(t_ray *ray, t_value_dec ray_len)
{
	ray->dist_wall = get_ray_dist_to_wall(ray, ray_len);
}

void	raycast_set_wall_inf(t_ray *ray, t_pos m_pos, t_pos_dec p_pos)
{
	set_ray_leng_pixels(ray, m_pos, p_pos);
	ray->map_wall_pos = get_ray_collision_map(*ray, p_pos);
}
