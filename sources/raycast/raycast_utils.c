/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 12:07:31 by dsilveri          #+#    #+#             */
/*   Updated: 2023/03/06 15:59:55 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	is_floor(char **map, t_pos pos)
{
	if (map[pos.y][pos.x] == FLOOR)
		return (TRUE);
	else
		return (FALSE);
}

int	is_door(char **map, t_pos pos)
{
	char	c;

	c = map[pos.y][pos.x];
	if (c >= DOOR_OPENING_START && c <= DOOR_OPENING_END
		|| c >= DOOR_CLOSING_START && c <= DOOR_CLOSING_END)
		return (TRUE);
	else
		return (FALSE);
}

int get_const_axis_collision(int side, t_pos m_pos)
{
	t_pos	w_pos;
	int		value;

	w_pos = get_win_pos(m_pos);
	if (side == EA_SIDE)
		value = w_pos.x;
	else if (side == SO_SIDE)
		value = w_pos.y;
	else if (side == NO_SIDE)
		value = w_pos.y + MAP_SQUARE_SIZE;
	else if (side == WE_SIDE)
		value = w_pos.x + MAP_SQUARE_SIZE;
	return (value);
}

// precisa ser acessivel em vários ficheiros
t_pos_dec get_ray_collision_pos_pixels(t_ray ray, t_pos p_pos)
{
	t_pos_dec pos;

	pos.x = ray.length_win * ray.cos + p_pos.x;
	pos.y = ray.length_win * ray.sin + p_pos.y;
	return (pos);
}

// precisa ser acessivel em vários ficheiros
void set_ray_leng_pixels(t_ray *ray, t_pos m_pos, t_pos p_pos)
{
	int final_pos;

	final_pos = get_const_axis_collision(ray->side, m_pos);
	if (ray->side == EA_SIDE)
		ray->length_win = (final_pos - p_pos.x) * ray->sx;
	else if (ray->side == SO_SIDE)
		ray->length_win = (final_pos - p_pos.y) * ray->sy;
	else if (ray->side == NO_SIDE)
		ray->length_win = (p_pos.y - final_pos) * ray->sy;
	else if (ray->side == WE_SIDE)
		ray->length_win =  (p_pos.x - final_pos) * ray->sx;
}

// precisa ser acessivel em vários ficheiros
double get_ray_collision_map(t_ray ray, t_pos p_pos)
{
	t_pos_dec	pos;
	double		value;

	pos = get_ray_collision_pos_pixels(ray, p_pos);
	pos = get_map_pos_decimal_1(pos);
	if (ray.side == EA_SIDE)
		value = pos.y;
	else if (ray.side == SO_SIDE)
		value = pos.x;
	else if (ray.side == NO_SIDE)
		value = pos.x;
	else if (ray.side == WE_SIDE)
		value = pos.y;
	return (value);
}

// precisa ser acessivel em vários ficheiros
double	get_ray_dist_to_wall(t_ray *ray, t_value_dec ray_leng)
{
	double dist;

	if (ray->side == EA_SIDE || ray->side == WE_SIDE)
		dist = (ray_leng.x - ray->sx) * ray->cos2;
	if (ray->side == SO_SIDE || ray->side == NO_SIDE)
		dist = (ray_leng.y - ray->sy) * ray->cos2;
	return (dist);
}
