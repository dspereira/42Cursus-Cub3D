/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 15:09:29 by dsilveri          #+#    #+#             */
/*   Updated: 2023/03/05 18:04:53 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"


static void			raycast(t_ray *ray, t_pos_dec p_pos, char **map);
static t_value		get_step(t_ray ray);
static t_value_dec	get_init_leng(t_ray ray, t_pos m_pos, t_pos_dec p_pos);


static int			get_door_side(char map_character);
//static t_value_dec	ray_cast_get_leng(t_ray ray, t_pos m_pos, t_pos_dec p_pos);
//static t_value		ray_cast_get_step(t_ray ray);

// refactored new functions
static void		update_map_pos(t_pos *m_pos, t_value step, t_value_dec ray_leng);
static void		update_side(int *side, t_value step, t_value_dec ray_leng);
static void		update_ray_leng(t_value_dec *ray_leng, t_ray ray);
static double	get_ray_dist_to_wall(t_ray *ray, t_value_dec ray_leng);
static int		get_const_axis_collision(int side, t_pos m_pos);
static void		set_ray_leng_pixels(t_ray *ray, t_pos m_pos, t_pos p_pos);
static double	get_ray_collision_map(t_ray ray, t_pos p_pos);


static void	set_door_raycast_info(t_ray *ray, char **map, t_pos map_pos, t_value_dec ray_len);
static void set_door_raycast_info_1(t_ray *ray, t_pos_dec p_pos, t_pos map_pos);

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
		update_map_pos(&map_pos, step, ray_length);
		update_side(&(ray->side), step, ray_length);
		update_ray_leng(&ray_length, *ray);
		if (is_door(map, map_pos))
		{
			set_door_raycast_info(ray, map, map_pos, ray_length);
			set_door_raycast_info_1(ray, p_pos, map_pos);
		}
	}
	ray->dist_wall = get_ray_dist_to_wall(ray, ray_length);
	ray->door_side_wall = get_door_side(map[map_pos.y][map_pos.x]);
	set_ray_leng_pixels(ray, map_pos, (t_pos){p_pos.x, p_pos.y});
	ray->map_wall_pos = get_ray_collision_map(*ray, (t_pos){p_pos.x, p_pos.y});
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


static void	set_door_raycast_info(t_ray *ray, char **map, t_pos map_pos, t_value_dec ray_len)
{
	ray->is_door = 1;
	ray->door_dist = get_ray_dist_to_wall(ray, ray_len);
	ray->door_side = ray->side;
	ray->door_pos = map_pos;
	ray->door_tex = map[map_pos.y][map_pos.x];
}

static void set_door_raycast_info_1(t_ray *ray, t_pos_dec p_pos, t_pos map_pos)
{
	set_ray_leng_pixels(ray, map_pos, (t_pos){p_pos.x, p_pos.y});
	ray->map_door_pos = get_ray_collision_map(*ray, (t_pos){p_pos.x, p_pos.y});
}

static void	update_map_pos(t_pos *m_pos, t_value step, t_value_dec ray_leng)
{
	if (ray_leng.x < ray_leng.y)
		m_pos->x += step.x;
	else
		m_pos->y += step.y;
}

static void	update_side(int *side, t_value step, t_value_dec ray_leng)
{
	if (ray_leng.x < ray_leng.y)
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

static void update_ray_leng(t_value_dec *ray_leng, t_ray ray)
{
	if (ray_leng->x < ray_leng->y)
		ray_leng->x += ray.sx;
	else
		ray_leng->y += ray.sy;
}

static double	get_ray_dist_to_wall(t_ray *ray, t_value_dec ray_leng)
{
	double dist;

	if (ray->side == EA_SIDE || ray->side == WE_SIDE)
		dist = (ray_leng.x - ray->sx) * ray->cos2;
	if (ray->side == SO_SIDE || ray->side == NO_SIDE)
		dist = (ray_leng.y - ray->sy) * ray->cos2;
	return (dist);
}




static void set_ray_leng_pixels(t_ray *ray, t_pos m_pos, t_pos p_pos)
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

static int get_const_axis_collision(int side, t_pos m_pos)
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


static t_pos_dec get_ray_collision_pos_pixels(t_ray ray, t_pos p_pos)
{
	t_pos_dec pos;

	pos.x = ray.length_win * ray.cos + p_pos.x;
	pos.y = ray.length_win * ray.sin + p_pos.y;
	return (pos);
}


// tem de entrar aqui posição do player em decimal
static double get_ray_collision_map(t_ray ray, t_pos p_pos)
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

static void	set_distace_win(t_ray *ray, t_pos m_pos, t_pos p_pos)
{
	set_ray_leng_pixels(ray, m_pos, p_pos);
	ray->map_wall_pos = get_ray_collision_map(*ray, p_pos);
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
