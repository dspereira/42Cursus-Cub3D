/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_rot_mouse.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 18:23:02 by dsilveri          #+#    #+#             */
/*   Updated: 2023/02/25 18:47:48 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static void		player_update_vision_x(t_player *player, t_pos mouse_pos);
static void		player_update_vision_y(t_player *player, t_pos mouse_pos);
static float	player_get_rot_angle_x(t_player player, t_pos mouse_pos);
static int		player_get_rot_pixels_y(t_player player, t_pos mouse_pos);

void	player_rot_mouse(t_player *player, t_pos mouse_pos)
{
	player_update_vision_x(player, mouse_pos);
	player_update_vision_y(player, mouse_pos);
}

static void	player_update_vision_x(t_player *player, t_pos mouse_pos)
{
	float	rot_angle;

	rot_angle = player_get_rot_angle_x(*player, mouse_pos);
	player->dir = normalizeAngles(player->dir + rot_angle);
	player_update_rays(player->rays, rot_angle);
}

static void	player_update_vision_y(t_player *player, t_pos mouse_pos)
{
	int	rot_pixels;

	rot_pixels = player_get_rot_pixels_y(*player, mouse_pos);
	player->dir_y += rot_pixels;
	if (player->dir_y > player->max_dir_y)
		player->dir_y = player->max_dir_y;
	else if (player->dir_y < player->min_dir_y)
		player->dir_y = player->min_dir_y;
}

static float	player_get_rot_angle_x(t_player player, t_pos mouse_pos)
{
	int		rot_pixels;
	float	rot_angle;

	rot_pixels = (player.win_half_size - mouse_pos.x) * (1 + MOUSE_SENSE);
	rot_angle = rot_pixels * player.angle_step;
	return (rot_angle);
}

static int	player_get_rot_pixels_y(t_player player, t_pos mouse_pos)
{
	int	rot_pixels;

	rot_pixels = player.midle_dir_y - mouse_pos.y;
	if (rot_pixels < 0 && player.dir_y <= player.min_dir_y)
		return (0);
	else if (rot_pixels > 0 && player.dir_y >= player.max_dir_y)
		return (0);
	return (rot_pixels);
}
