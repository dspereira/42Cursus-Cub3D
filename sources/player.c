/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 11:40:52 by dsilveri          #+#    #+#             */
/*   Updated: 2023/01/20 16:41:50 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static t_ray init_ray(t_pos pos, float dir);
static void add_rays_to_player(t_player *player);

/*
t_player *init_player (t_pos pos, int dir)
{
    t_player    *player;
    int         n_rays;
    int         n_rays_half;
    int         half_vision;
    float         angle;
    int         i;

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
    n_rays_half = n_rays / 2;
    half_vision = CAMERA_ANGLE / 2;
    angle = (float) dir + (float) half_vision;
    i = 0;
    while (i < n_rays)
    {
        angle -= DIST_BTW_ANGLE;
        player->rays[i] = init_ray(pos, normalizeAngles(angle));
        i++;
    }
    return (player);
}
*/


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

static t_ray init_ray(t_pos pos, float dir)
{
    t_ray ray;

    ray.pos = pos;
    ray.dir = dir;
    return (ray);
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
        player->rays[i] = init_ray(player->pos, normalizeAngles(angle));
        i++;
    }
}