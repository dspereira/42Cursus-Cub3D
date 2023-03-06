/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 15:09:29 by dsilveri          #+#    #+#             */
/*   Updated: 2023/03/06 16:14:48 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static void			raycast(t_ray *ray, t_pos_dec p_pos, char **map);
static t_value		get_step(t_ray ray);
static t_value_dec	get_init_leng(t_ray ray, t_pos m_pos, t_pos_dec p_pos);

void	raycast_all(t_player *player, char **map)
{
	int	i;

	i = -1;
	while (++i < NUMBER_RAYS)
		raycast(&(player->rays[i]), player->pos_dec, map);
}

static void	raycast(t_ray *ray, t_pos_dec p_pos, char **map)
{
	t_value		step;
	t_value_dec	ray_length;
	t_pos		map_pos;

	ray->is_door = 0;
	map_pos = get_map_pos((t_pos){p_pos.x, p_pos.y});
	step = get_step(*ray);
	ray_length = get_init_leng(*ray, map_pos, p_pos);
	while(is_floor(map, map_pos) || is_door(map, map_pos))
	{
		raycast_update(ray, &map_pos, &ray_length, step);
		if (is_door(map, map_pos))
		{
			raycast_door_set_inf(ray, map_pos, (t_pos){p_pos.x, p_pos.y}, map);
			raycast_door_set_dist(ray, ray_length);
		}
	}
	raycast_door_set_wall_side(ray, map_pos, map);
	raycast_wall_set_dist(ray, ray_length);
	raycast_set_wall_inf(ray, map_pos, (t_pos){p_pos.x, p_pos.y});
}

static t_value	get_step(t_ray ray)
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

static t_value_dec	get_init_leng(t_ray ray, t_pos m_pos, t_pos_dec p_pos)
{
	t_value_dec	leng;
	t_pos_dec	map_pos_dec;

	map_pos_dec = get_map_pos_decimal_1(p_pos);
	if (ray.cos < 0)
		leng.x = (map_pos_dec.x - m_pos.x) * ray.sx;
	else 
		leng.x = ((m_pos.x + 1) - map_pos_dec.x) * ray.sx;
	if (ray.sin < 0)
		leng.y = (map_pos_dec.y - m_pos.y) * ray.sy;
	else
		leng.y = ((m_pos.y + 1) - map_pos_dec.y) * ray.sy;
	return (leng);
}
