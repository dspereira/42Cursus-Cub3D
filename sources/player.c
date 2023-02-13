/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 11:40:52 by dsilveri          #+#    #+#             */
/*   Updated: 2023/02/11 15:33:00 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static void add_rays_to_player(t_player *player, int n_rays);

t_player *player_init(t_pos pos, int dir)
{
	t_player    *player;

	player = malloc(sizeof(t_player));
	if (!player)
		return (0);
	player->pos = pos;
	player->dir = (float) dir;
	player->dir_y = WIN_WIDTH / 2;
	player->angle_step = (float)CAMERA_ANGLE / NUMBER_RAYS;
	player->rays = malloc(NUMBER_RAYS * sizeof(t_ray));
	if (!(player->rays))
		return (0);
	add_rays_to_player(player, NUMBER_RAYS);
	return (player);
}

void player_update_vision(t_player *player, float rot_angle)
{
	t_ray	*rays;
	int 	i;

	rays = player->rays;
	player->dir = normalizeAngles(player->dir + rot_angle);
	i = -1;
	while (++i < NUMBER_RAYS)
		ray_update_dir(&rays[i], rays[i].dir + rot_angle);
}

void player_rotation_y(t_win win, t_player *player, t_pos mouse_pos)
{
	int rot_pixels;
	int half_height_win;

	half_height_win = WIN_HEIGHT / 2;

	rot_pixels = half_height_win - mouse_pos.y;
	if (rot_pixels < 0 && player->dir_y < half_height_win / 2)
		return ;
	else if (rot_pixels > 0 && player->dir_y > WIN_HEIGHT - (half_height_win / 2))
		return ;
	player->dir_y += rot_pixels;
	if (player->dir_y > WIN_HEIGHT - (half_height_win / 2))
		player->dir_y = WIN_HEIGHT - (half_height_win / 2);
	else if (player->dir_y < half_height_win / 2)
		player->dir_y = half_height_win / 2;
}

void player_rotation(t_win win, t_player *player, t_pos mouse_pos)
{
	int		rot_pixels;
	float	rot_angle;

	rot_pixels = (WIN_WIDTH / 2) - mouse_pos.x;
	rot_angle = rot_pixels * ((float)CAMERA_ANGLE / NUMBER_RAYS);
	player_update_vision(player, rot_angle);
	player_rotation_y(win, player, mouse_pos);
}


void player_move(t_player *player, char **map, int dir)
{
	t_pos	new_pos;
	float	angle;

	angle = normalizeAngles((float)dir + player->dir);
	new_pos = get_new_dist_pos(player->pos, angle, MOVE_STEP);
	if (!check_collisions(new_pos, map))	
		player->pos = new_pos;
}

static void add_rays_to_player(t_player *player, int n_rays)
{
	int     i;
	float   angle;

	angle = player->dir + (CAMERA_ANGLE / 2);
	i = 0;
	while (i < n_rays)
	{
		angle -= player->angle_step;
		ray_init(&(player->rays[i]), angle, player->dir);
		i++;
	}
}
