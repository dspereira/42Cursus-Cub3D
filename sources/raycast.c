/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcandeia < dcandeia@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 15:09:29 by dsilveri          #+#    #+#             */
/*   Updated: 2023/02/17 11:49:14 by dcandeia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static void			raycast(t_ray *ray, t_pos p_pos, char **map, float p_dir);
static t_value		ray_cast_get_step(t_ray ray);
static t_value_dec	ray_cast_get_leng(t_ray ray, t_pos m_pos, t_pos p_pos);
static void			set_distace_win(t_ray *ray, t_pos m_pos, t_pos p_pos);
static int			get_door_side(char map_character);

void	raycast_all(t_player *player, char **map)
{
	int	i;

	i = -1;
	while (++i < NUMBER_RAYS)
		raycast(&(player->rays[i]), player->pos, map, player->dir);
}

static void	set_distace_win1(t_ray *ray, t_pos m_pos, t_pos p_pos)
{
	t_pos	win_pos;
	t_pos	final_pos;
	int		square_size;

	t_pos_dec	wall_pos;

    square_size = WIN_HEIGHT / MAP_HEIGHT;
	win_pos = get_win_pos(m_pos);
	if (ray->door_side == EA_SIDE)
		final_pos.x = win_pos.x;
	else if (ray->door_side == SO_SIDE)
		final_pos.y = win_pos.y;
	else if (ray->door_side == NO_SIDE)
		final_pos.y = win_pos.y + square_size;
	else if (ray->door_side == WE_SIDE)
		final_pos.x = win_pos.x + square_size;
	if (ray->door_side == EA_SIDE)
		ray->length_win = (final_pos.x - p_pos.x) * ray->sx;
	else if (ray->door_side == SO_SIDE)
		ray->length_win = (final_pos.y - p_pos.y) * ray->sy;
	else if (ray->door_side == NO_SIDE)
		ray->length_win = (p_pos.y - final_pos.y) * ray->sy;
	else if (ray->door_side == WE_SIDE)
		ray->length_win =  (p_pos.x - final_pos.x) * ray->sx;

	wall_pos = get_new_dist_pos_dec(p_pos, ray->dir, ray->length_win);

	if (ray->door_side == EA_SIDE)
		ray->map_door_pos = get_map_pos_decimal_1(wall_pos).y;
	else if (ray->door_side == SO_SIDE)
		ray->map_door_pos = get_map_pos_decimal_1(wall_pos).x;
	else if (ray->door_side == NO_SIDE)
		ray->map_door_pos = get_map_pos_decimal_1(wall_pos).x;
	else if (ray->door_side == WE_SIDE)
		ray->map_door_pos = get_map_pos_decimal_1(wall_pos).y;
}

static void	raycast(t_ray *ray, t_pos p_pos, char **map, float p_dir)
{
	t_value		step;
	t_value_dec	ray_length;
	t_pos		map_pos;
	int			test_side;

	ray->is_door = 0;
	map_pos = get_map_pos(p_pos);
	step = ray_cast_get_step(*ray);
	ray_length = ray_cast_get_leng(*ray, map_pos, p_pos);
	while (map[map_pos.y][map_pos.x] == '0' || map[map_pos.y][map_pos.x] == 'G')
	{
		if (ray_length.x < ray_length.y)
		{
			map_pos.x += step.x;
			ray_length.x += ray->sx;
			ray->side = EA_SIDE;
		}
		else
		{
			map_pos.y += step.y;
			ray_length.y += ray->sy;
			ray->side = SO_SIDE;
		}
		if (map[map_pos.y][map_pos.x] == 'G')
		{
			ray->is_door = 1;
			if (ray->side == EA_SIDE)
				test_side = ray->side * step.x;
			else
				test_side = ray->side * step.y;
			if (test_side == EA_SIDE || test_side == WE_SIDE)
				ray->door_dist = (ray_length.x - ray->sx) * ray->cos2;
			if (test_side == SO_SIDE || test_side == NO_SIDE)
				ray->door_dist = (ray_length.y - ray->sy) * ray->cos2;
			ray->door_side = test_side;
			set_distace_win1(ray, map_pos, p_pos);
		}
	}
	if (ray->side == EA_SIDE)
		ray->side *= step.x;
	else
		ray->side *= step.y;
	if (ray->side == EA_SIDE || ray->side == WE_SIDE)
		ray->dist_wall = (ray_length.x - ray->sx) * ray->cos2;
	if (ray->side == SO_SIDE || ray->side == NO_SIDE)
		ray->dist_wall = (ray_length.y - ray->sy) * ray->cos2;
	ray->door_side_wall = get_door_side(map[map_pos.y][map_pos.x]);
	set_distace_win(ray, map_pos, p_pos);
	//printf("valor: %.5f\n",ray->map_wall_pos);
}

static t_value	ray_cast_get_step(t_ray ray)
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

static t_value_dec	ray_cast_get_leng(t_ray ray, t_pos m_pos, t_pos p_pos)
{
	t_value_dec	leng;
	t_pos_dec	map_pos_dec;

	map_pos_dec = get_map_pos_decimal(p_pos);
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

// Set distance to raycast 2D
/*
static void set_distace_win(t_ray *ray, t_pos m_pos, t_pos p_pos)
{
	t_pos	win_pos;
	t_pos	final_pos;
	int		square_size;

	t_pos_dec	wall_pos;

    square_size = WIN_HEIGHT / MAP_HEIGHT;
	win_pos = get_win_pos(m_pos);
	if (ray->side == EA_SIDE)
		final_pos.x = win_pos.x;
	else if (ray->side == SO_SIDE)
		final_pos.y = win_pos.y;
	else if (ray->side == NO_SIDE)
		final_pos.y = win_pos.y + square_size;
	else if (ray->side == WE_SIDE)
		final_pos.x = win_pos.x + square_size;
	if (ray->side == EA_SIDE)
		ray->length_win = (final_pos.x - p_pos.x) * ray->sx;
	else if (ray->side == SO_SIDE)
		ray->length_win = (final_pos.y - p_pos.y) * ray->sy;
	else if (ray->side == NO_SIDE)
		ray->length_win = (p_pos.y - final_pos.y) * ray->sy;
	else if (ray->side == WE_SIDE)
		ray->length_win =  (p_pos.x - final_pos.x) * ray->sx;
	
	wall_pos = get_new_dist_pos_dec(p_pos, ray->dir, ray->length_win);

	if (ray->side == EA_SIDE)
		ray->map_wall_pos = get_map_pos_decimal_1(wall_pos).y;
	else if (ray->side == SO_SIDE)
		ray->map_wall_pos = get_map_pos_decimal_1(wall_pos).x;
	else if (ray->side == NO_SIDE)
		ray->map_wall_pos = get_map_pos_decimal_1(wall_pos).x;
	else if (ray->side == WE_SIDE)
		ray->map_wall_pos = get_map_pos_decimal_1(wall_pos).y;
}
*/

static void	set_distace_win(t_ray *ray, t_pos m_pos, t_pos p_pos)
{
	t_pos	win_pos;
	t_pos	final_pos;
	int		square_size;

	t_pos_dec	wall_pos;

    square_size = WIN_HEIGHT / MAP_HEIGHT;
	win_pos = get_win_pos(m_pos);
	if (ray->side == EA_SIDE)
		final_pos.x = win_pos.x;
	else if (ray->side == SO_SIDE)
		final_pos.y = win_pos.y;
	else if (ray->side == NO_SIDE)
		final_pos.y = win_pos.y + square_size;
	else if (ray->side == WE_SIDE)
		final_pos.x = win_pos.x + square_size;
	if (ray->side == EA_SIDE)
		ray->length_win = (final_pos.x - p_pos.x) * ray->sx;
	else if (ray->side == SO_SIDE)
		ray->length_win = (final_pos.y - p_pos.y) * ray->sy;
	else if (ray->side == NO_SIDE)
		ray->length_win = (p_pos.y - final_pos.y) * ray->sy;
	else if (ray->side == WE_SIDE)
		ray->length_win =  (p_pos.x - final_pos.x) * ray->sx;

	wall_pos = get_new_dist_pos_dec(p_pos, ray->dir, ray->length_win);

	if (ray->side == EA_SIDE)
		ray->map_wall_pos = get_map_pos_decimal_1(wall_pos).y;
	else if (ray->side == SO_SIDE)
		ray->map_wall_pos = get_map_pos_decimal_1(wall_pos).x;
	else if (ray->side == NO_SIDE)
		ray->map_wall_pos = get_map_pos_decimal_1(wall_pos).x;
	else if (ray->side == WE_SIDE)
		ray->map_wall_pos = get_map_pos_decimal_1(wall_pos).y;

	
}




static int	get_door_side(char map_character)
{
	if (map_character == NO_DOOR)
		return (NO_SIDE);
	else if (map_character == SO_DOOR)
		return (SO_SIDE);
	else if (map_character == EA_DOOR)
		return (EA_SIDE);
	else if (map_character == WE_DOOR)
		return (WE_SIDE);
	else
		return (0);
}
