/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 11:40:52 by dsilveri          #+#    #+#             */
/*   Updated: 2023/01/28 15:36:14 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static void add_rays_to_player(t_player *player, int n_rays);

t_player *player_init(t_pos pos, int dir)
{
	t_player    *player;
	int         n_rays;

	n_rays = CAMERA_ANGLE / DIST_BTW_ANGLE;
	player = malloc(sizeof(t_player));
	if (!player)
		return (0);
	player->pos = pos;
	player->dir = (float) dir;
	player->rays = malloc(n_rays * sizeof(t_ray));
	if (!(player->rays))
		return (0);
	add_rays_to_player(player, n_rays);
	return (player);
}

void player_update_vision(t_player *player, int rot_angle)
{
	int		n_rays;
	int 	i;
	t_ray	*rays;

	n_rays = CAMERA_ANGLE / DIST_BTW_ANGLE;
	rays = player->rays;
	player->dir = normalizeAngles(player->dir + rot_angle);
	i = -1;
	while (++i < n_rays)
		ray_update_dir(&rays[i], rays[i].dir + rot_angle);
}

void player_move(t_player *player, int dir)
{
	float angle;

	angle = normalizeAngles((float)dir + player->dir);
	player->pos = get_new_pos1(player->pos, angle, MOVE_STEP);
}

static void add_rays_to_player(t_player *player, int n_rays)
{
	int     i;
	float   angle;

	angle = player->dir + (CAMERA_ANGLE / 2);
	i = 0;
	while (i < n_rays)
	{
		angle -= DIST_BTW_ANGLE;
		ray_init(&(player->rays[i]), angle);
		i++;
	}
}
