/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcandeia <dcandeia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 11:40:52 by dsilveri          #+#    #+#             */
/*   Updated: 2023/02/27 16:24:43 by dcandeia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static void		add_rays_to_player(t_player *player, int n_rays);

t_player	*player_init(t_pos pos, int dir)
{
	t_player	*player;

	player = malloc(sizeof(t_player));
	if (!player)
		return (0);
	player->pos = pos;
	player->pos_dec = (t_pos_dec){pos.x, pos.y};
	player->dir = (float) dir;
	player->dir_y = WIN_HEIGHT / 2;
	player->midle_dir_y = WIN_HEIGHT / 2;
	player->max_dir_y = WIN_HEIGHT - (player->midle_dir_y / 2);
	player->min_dir_y = player->midle_dir_y / 2;
	player->angle_step = (float)CAMERA_ANGLE / NUMBER_RAYS;
	player->win_half_size = WIN_WIDTH / 2;
	player->rays = malloc(NUMBER_RAYS * sizeof(t_ray));
	if (!(player->rays))
		return (0);
	add_rays_to_player(player, NUMBER_RAYS);
	return (player);
}

void	player_move(t_player *player, char **map, int dir)
{
	t_pos_dec	new_pos_dec;
	t_pos		new_pos;
	float		angle;

	angle = normalize_angles((float)dir + player->dir);
	new_pos_dec = get_new_dist_pos_dec(player->pos_dec, angle, MOVE_STEP);
	new_pos = (t_pos){round(new_pos_dec.x), round(new_pos_dec.y)};
	if (!check_collisions(new_pos, map))
	{
		player->pos_dec = new_pos_dec;
		player->pos = new_pos;
	}
}

void	player_rotation_key(t_player *player, float rot_angle)
{
	player->dir = normalize_angles(player->dir + rot_angle);
	player_update_rays(player->rays, rot_angle);
}

void	player_update_rays(t_ray *rays, float rot_angle)
{
	int	i;

	i = 0;
	while (i < NUMBER_RAYS)
	{
		ray_update_dir(&rays[i], rays[i].dir + rot_angle);
		i++;
	}
}

static void	add_rays_to_player(t_player *player, int n_rays)
{
	int		i;
	float	angle;

	angle = player->dir + (CAMERA_ANGLE / 2);
	i = 0;
	while (i < n_rays)
	{
		angle -= player->angle_step;
		ray_init(&(player->rays[i]), angle, player->dir);
		i++;
	}
}
