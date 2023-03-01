/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_rot_mouse.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 18:23:02 by dsilveri          #+#    #+#             */
/*   Updated: 2023/03/01 10:37:52 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static void		player_update_vision_x(t_player *player, t_mouse mouse);
static void		player_update_vision_y(t_player *player, t_mouse mouse);
static int		player_get_rot_y(t_player player, t_mouse mouse);
static float	player_get_rot_x(t_player player, t_mouse mouse);

void	player_rot_mouse(t_player *player, t_mouse mouse)
{
	player_update_vision_x(player, mouse);
	player_update_vision_y(player, mouse);
}

static void	player_update_vision_x(t_player *player, t_mouse mouse)
{
	float	rot_angle;

	rot_angle = player_get_rot_x(*player, mouse);
	player->dir = normalize_angles(player->dir + rot_angle);
	player_update_rays(player->rays, rot_angle);
}

static void	player_update_vision_y(t_player *player, t_mouse mouse)
{
	int	rot_pixels;

	rot_pixels = player_get_rot_y(*player, mouse);
	player->dir_y += rot_pixels;
	if (player->dir_y > player->max_dir_y)
		player->dir_y = player->max_dir_y;
	else if (player->dir_y < player->min_dir_y)
		player->dir_y = player->min_dir_y;
}

static int	player_get_rot_y(t_player player, t_mouse mouse)
{
	int	rot_pixels;

	rot_pixels = mouse.last.y - mouse.actual.y;
	if (rot_pixels < 0 && player.dir_y <= player.min_dir_y)
		return (0);
	else if (rot_pixels > 0 && player.dir_y >= player.max_dir_y)
		return (0);
	return (rot_pixels);
}

static float	player_get_rot_x(t_player player, t_mouse mouse)
{
	int		rot_pixels;
	float	rot_angle;

	rot_pixels = (mouse.last.x - mouse.actual.x);
	rot_angle = rot_pixels * player.angle_step;
	return (rot_angle);
}
