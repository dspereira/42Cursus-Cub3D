/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 10:50:11 by dsilveri          #+#    #+#             */
/*   Updated: 2023/01/27 14:18:18 by dsilveri         ###   ########.fr       */
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

#define WIN_HEIGHT		960
#define WIN_WIDTH		960

#define CAMERA_ANGLE	60
#define DIST_BTW_ANGLE	1

#define KEY_W			119
#define KEY_S			115
#define KEY_A			97
#define KEY_D			100

#define KEY_ARROW_L		65361
#define KEY_ARROW_R		65363

#define FORWARD			0
#define BACKWARD		180
#define LEFT			90
#define RIGHT			270

#define ROT_STEP		5
#define MOVE_STEP		10

typedef struct s_img
{
	void	*mlx_img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_win
{
	void	*mlx;
	void	*mlx_win;
	t_img	frame;
}	t_win;

/*
typedef struct s_mlx_data
{
	void	*mlx;
	void	*win;
	t_img	frame;
}	t_mlx_data;
*/

typedef struct s_map
{
	char **content;
}	t_map;

typedef struct s_pos
{
	int x;
	int y;
}	t_pos;

typedef struct s_pos_dec
{
	double x;
	double y;
}	t_pos_dec;

typedef struct s_ray 
{
	float	dir;
	int		length;
	int		length_win;
	int		length_map;
	int		dist_wall;
	int		side;
	double	cos;
	double	sin;
	double	sx;
	double	sy;
}	t_ray;

typedef struct s_player 
{
	t_pos	pos;
	float	dir;
	t_ray	*rays;
}	t_player;

typedef struct s_data
{
	t_win		*win;
	t_map		map;
	t_player	*player;
}	t_data; 


// math_utils.c
int		math_abs(int n);
float	normalizeAngles(float angle);
double	cos_degree(double angle);
double	sin_degree(double angle);

// mlx_utils.c
void	mlx_draw_line(t_win *win, t_pos init, t_pos end, int color);
void	mlx_draw_stroke_square(t_win *win, t_pos init, int size, int color);
void	mlx_draw_fill_square(t_win *win, t_pos init, int size, int color);
void	img_pixel_put(t_img *img, int x, int y, int color);

//utils.c
t_pos		get_new_pos(t_pos init, double scale_x, double scale_y, int dist);
t_pos		get_map_pos(t_pos pos);
t_pos_dec	get_map_pos_decimal(t_pos pos);
t_pos		get_win_pos(t_pos pos);
t_pos		get_new_pos1(t_pos init, float dir, int dist);

//render_scene_2d.c
void render_scene_2d(t_win *win, t_player player, char **map);

//player.c
t_player	*init_player (t_pos pos, int dir);
void 		ray_cast(t_player *player, char **map);
void		update_vision(t_player *player, int key);
void		player_move(t_player *player, int dir);

#endif