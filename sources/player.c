/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 11:40:52 by dsilveri          #+#    #+#             */
/*   Updated: 2023/01/20 12:30:17 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

t_player *init_player (t_pos pos, int dir)
{
    t_player *player;

    player = malloc(sizeof(t_player));
    if (!player)
        return (0);
    player->pos = pos;
    player->dir = (float) dir;
    player->rays = NULL;
    return (player);
}

static t_ray *init_ray(t_pos pos, float dir)
{
    t_ray *ray;

    ray = malloc(sizeof(ray));
    if (!ray)
        return (0);
    ray->pos = pos;
    ray->dir = dir;
    return (ray);
}