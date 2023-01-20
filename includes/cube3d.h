/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 10:50:11 by dsilveri          #+#    #+#             */
/*   Updated: 2023/01/20 16:02:50 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
#define CUBE3D_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mlx.h>

#define MAP_HEIGHT		24
#define MAP_WIDTH		24
#define WIN_HEIGHT		480
#define WIN_WIDTH		480

#define CAMERA_ANGLE	60
#define DIST_BTW_ANGLE	1

typedef struct s_win
{
	void	*mlx;
	void	*mlx_win;
}	t_win;

typedef struct s_pos 
{
	int x;
	int y;
}	t_pos;

typedef struct s_ray 
{
	t_pos	pos;
	float	dir;
	int		side;
	int		dist_ray;
	int		dist_wall;
}	t_ray;

typedef struct s_player 
{
	t_pos	pos;
	float	dir;
	t_ray	*rays;
}	t_player;

// math_utils.c
int math_abs(int n);
float normalizeAngles(float angle);

// mlx_utils.c
void mlx_draw_line(t_win win, t_pos init, t_pos end, int color);
void mlx_draw_stroke_square(t_win win, t_pos init, int size, int color);
void mlx_draw_fill_square(t_win win, t_pos init, int size, int color);

//render_scene_2d.c
void render_scene_2d(t_win	win, t_player player, char map[MAP_WIDTH][MAP_HEIGHT]);

//player.c
t_player *init_player (t_pos pos, int dir);

#endif