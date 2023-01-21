/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 11:40:52 by dsilveri          #+#    #+#             */
/*   Updated: 2023/01/21 16:44:28 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static t_ray init_ray(float dir);
static void add_rays_to_player(t_player *player);
static void get_hyp_length_scale(t_ray *ray, t_pos pos);

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


static void ray_cast(t_ray *ray, t_pos pos)
{

}


static void get_hyp_length_scale(t_ray *ray, t_pos pos)
{
    t_pos   final_pos;
    int     dx;
    int     dy;
    
    //sx = 1 / cos
    //sy = 1 / sen

    final_pos = get_new_pos(pos, ray->cos, ray->sin, 2000);
    dx = final_pos.x - pos.x;
    dy = final_pos.y - pos.y;
    ray->sx = sqrt(1 + (((double)dy/dx) * ((double)dy/dx)));
    ray->sy = sqrt(1 + (((double)dx/dy) * ((double)dx/dy)));


    printf("================================\n");
    printf("ray->dir : %f\n", ray->dir);
    /*printf("ray->sx : %0.10f\n", ray->sx);
    printf("ray->sy : %0.10f\n", ray->sy);*/
    printf("ray->sin: %0.10f\n", ray->sin);
    printf("ray->cos: %0.10f\n", ray->cos);
}

static t_ray init_ray(float dir)
{
    t_ray ray;

    ray.dir = dir;
    ray.cos = cos_degree(dir);
    ray.sin = sin_degree(dir);
    ray.sx = 1 / ray.cos;
    ray.sy = 1 / ray.sin;
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
        player->rays[i] = init_ray(normalizeAngles(angle));
        //get_hyp_length_scale(&(player->rays[i]), player->pos);
        i++;
    }
}
