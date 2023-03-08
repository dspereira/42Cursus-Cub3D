/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_door.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 11:17:48 by dsilveri          #+#    #+#             */
/*   Updated: 2023/03/07 17:02:04 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	raycast_door_set_inf(t_ray *ray, t_pos m_pos,
	t_pos_dec p_pos, char **map)
{
	ray->is_door = 1;
	ray->door_side = ray->side;
	ray->door_pos = m_pos;
	ray->door_tex = map[m_pos.y][m_pos.x];
	set_ray_leng_pixels(ray, m_pos, p_pos);
	ray->map_door_pos = get_ray_collision_map(*ray, p_pos);
}

void	raycast_door_set_dist(t_ray *ray, t_value_dec ray_len)
{
	ray->door_dist = get_ray_dist_to_wall(ray, ray_len);
}

void	raycast_door_set_wall_side(t_ray *ray, t_pos m_pos, char **map)
{
	char	c;
	int		side;

	side = 0;
	c = map[m_pos.y][m_pos.x];
	if (c == NO_DOOR)
		side = NO_SIDE;
	else if (c == SO_DOOR)
		side = SO_SIDE;
	else if (c == EA_DOOR)
		side = EA_SIDE;
	else if (c == WE_DOOR)
		side = WE_SIDE;
	ray->door_side_wall = side;
}
