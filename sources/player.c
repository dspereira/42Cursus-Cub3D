/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 11:40:52 by dsilveri          #+#    #+#             */
/*   Updated: 2023/01/26 17:22:08 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

//static t_ray init_ray(float dir);
static void init_ray(t_ray *ray, float dir);
static void add_rays_to_player(t_player *player);
static void get_hyp_length_scale(t_ray *ray, t_pos pos);
static void ray_cast1(t_ray *ray, t_pos pos, char **map);
static void set_distace_win(t_ray *ray, t_pos map_pos, t_pos p_pos);
static void update_ray(t_ray *ray, float rot_angle);

t_player *init_player (t_pos pos, int dir)
{
	t_player    *player;
	int         n_rays;

	n_rays = CAMERA_ANGLE / DIST_BTW_ANGLE;
	//NOTE: just for prtection in tests, remove in production
	if (n_rays > 2000)
		n_rays = 2000;

	player = malloc(sizeof(t_player));
	if (!player)
		return (0);
	player->pos = pos;
	player->dir = (float) dir;
	player->rays = malloc(n_rays * sizeof(t_ray));
	if (!(player->rays))
		return (0);
	add_rays_to_player(player);
	return (player);
}

void ray_cast(t_player *player, char **map)
{
	int i;
	int n_rays;

	n_rays = CAMERA_ANGLE / DIST_BTW_ANGLE;
	i = 0;
	while (i < n_rays)
	{
		ray_cast1(&(player->rays[i]), player->pos, map);
		i++;
	}
	//printf("ray Direction: %f\n", player->rays[0].dir);
	//printf("ray distance: %d\n", player->rays[0].length_win);
}

void update_vision(t_player *player, int key)
{
	int		n_rays;
	int 	i;
	int 	rot_val;
	t_ray	*rays;

	n_rays = CAMERA_ANGLE / DIST_BTW_ANGLE;
	rays = player->rays;
	if (key == KEY_ARROW_L)
		rot_val = ROT_STEP;
	else
		rot_val = -ROT_STEP;
	player->dir = normalizeAngles(player->dir + rot_val);
	i = -1;
	while (++i < n_rays)
		update_ray(&rays[i], rot_val);
}

static void update_ray(t_ray *ray, float rot_angle)
{
	double value;

	ray->dir = normalizeAngles(ray->dir + rot_angle);
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
	/*
	if (ray->cos != 0)
		ray->sx = 1 / ray->cos;
	else
		ray->sx = 1000000;
	if (ray->sin != 0)
		ray->sy = 1 / ray->sin;
	else
		ray->sy = 1000000;
	*/
	if (ray->sx < 0)
		ray->sx *= -1;
	if (ray->sy < 0)
		ray->sy *= -1;
}

static void ray_cast1(t_ray *ray, t_pos pos, char **map)
{
	int		step_x;
	int		step_y;
	double	ray_length_x;
	double	ray_length_y;
	int 	side;
	t_pos	map_pos;
	t_pos_dec map_pos_dec;

	map_pos = get_map_pos(pos);
	map_pos_dec = get_map_pos_decimal(pos);

	//printf("mapa inicial map_pos.x: %i  map_pos.y: %i\n", map_pos.x, map_pos.y);
	//printf("sx: %f  sy: %f", ray->sx, ray->sy);
	
	if (ray->cos < 0)
	{
		step_x = -1;
		ray_length_x = (map_pos_dec.x - (double)map_pos.x) * ray->sx;
	}
	else 
	{
		step_x = 1;
		ray_length_x = ((double)(map_pos.x + 1) - map_pos_dec.x) * ray->sx;
	}
	if (ray->sin < 0)
	{
		step_y = -1;
		ray_length_y = (map_pos_dec.y - (double)map_pos.y) * ray->sy;
	}
	else
	{
		step_y = 1;
		ray_length_y = ((double)(map_pos.y + 1) - map_pos_dec.y) * ray->sy;
	}


	/*if (ray->dir == 105)
	{
		printf("map_pos.x: %i\n", map_pos.x);
		printf("map_pos.y: %i\n", map_pos.y);
		printf("map_pos_dec.x: %f\n", map_pos_dec.x);
		printf("map_pos_dec.y: %f\n", map_pos_dec.y);
		printf("ray_length_x: %f\n", ray_length_x);
		printf("ray_length_x: %f\n", ray_length_x);
		printf("ray_length_y: %f\n", ray_length_y);
	}*/
	
	while (!map[map_pos.y][map_pos.x])
	{
		if (ray_length_x < ray_length_y){
			map_pos.x += step_x;
			ray_length_x += ray->sx;
			side = 1 * step_x;
		}
		else {
			map_pos.y += step_y;
			ray_length_y += ray->sy;
			side = 2 * step_y;
		}
	}
	ray->side = side;

	set_distace_win(ray, map_pos, pos);
	//ray->length_win = 20;


	
	/* printf("===========================\n");
	printf("angle: %f\n", ray->dir);
	printf("cos: %f  sin: %f\n", ray->cos, ray->sin);
	printf("sx: %f  sy: %f\n", ray->sx, ray->sy);
	printf("step_x: %i step_y: %i\n", step_x, step_y);
	printf("ray->dir: %f\n", ray->dir);
	printf("map_pos.x: %i  map_pos.y: %i\n", map_pos.x, map_pos.y);
	printf("destance: %i\n", ray->length_win); */
}

static void set_distace_win(t_ray *ray, t_pos map_pos, t_pos p_pos)
{
	t_pos	win_pos;
	t_pos	final_pos;
	int		square_size;

	//printf("Ray scale x: %f  y: %f\n", ray->sx, ray->sy);
    square_size = WIN_HEIGHT / MAP_HEIGHT;
	win_pos = get_win_pos(map_pos);

	if (ray->side == 1) {
		final_pos.x = win_pos.x;
		ray->length_win = (final_pos.x - p_pos.x) * ray->sx;
		/*
		printf("===========================\n");
		printf("map_pos.x: %i  map_pos.y: %i\n", map_pos.x, map_pos.y);
		printf("end point win_pos.x: %i  win_pos.y: %i\n", win_pos.x, win_pos.y);
		*/
	}
	else if (ray->side == 2) {
		final_pos.y = win_pos.y;
		ray->length_win = (final_pos.y - p_pos.y) * ray->sy;
	}
	else if (ray->side == -2) {
		final_pos.y = win_pos.y + square_size;
		ray->length_win = (p_pos.y - final_pos.y) * ray->sy;
	}
	else if (ray->side == -1) {
		final_pos.x = win_pos.x + square_size;
		ray->length_win =  (p_pos.x - final_pos.x) * ray->sx;
	}
	if (ray->length_win < 0)
		ray->length_win *= -1;
}

/*
static t_ray init_ray(float dir)
{
	t_ray ray;

	ray.dir = dir;
	ray.cos = cos_degree(dir);
	ray.sin = sin_degree(dir) * -1;
	ray.sx = 1 / ray.cos;
	ray.sy = 1 / ray.sin;

	if (ray.sx < 0)
		ray.sx *= -1;
	if (ray.sy < 0)
		ray.sy *= -1;
	return (ray);
}
*/

static void init_ray(t_ray *ray, float dir)
{
	ray->dir = dir;
	ray->cos = cos_degree(dir);
	ray->sin = sin_degree(dir) * -1;
	ray->sx = 1 / ray->cos;
	ray->sy = 1 / ray->sin;

	if (ray->sx < 0)
		ray->sx *= -1;
	if (ray->sy < 0)
		ray->sy *= -1;
}

static void add_rays_to_player(t_player *player)
{
	int     i;
	int     n_rays;
	float   angle;

	n_rays = CAMERA_ANGLE / DIST_BTW_ANGLE;
	angle = player->dir + (float) (CAMERA_ANGLE / 2);
	i = 0;
	while (i < n_rays)
	{
		angle -= DIST_BTW_ANGLE;
		init_ray(&(player->rays[i]), normalizeAngles(angle));
		i++;
	}
}
