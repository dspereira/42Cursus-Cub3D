/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 10:50:11 by dsilveri          #+#    #+#             */
/*   Updated: 2023/02/08 11:02:12 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
#define CUBE3D_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>
#include <fcntl.h>
#include <mlx.h>

#define MAP_HEIGHT		26
#define MAP_WIDTH		26

#define WIN_HEIGHT		1040
#define WIN_WIDTH		1040

#define CAMERA_ANGLE	50
#define	NUMBER_RAYS		WIN_WIDTH

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

// render 2D
#define PLAYER_SIZE		10
#define PLAYER_COLOR	0x00E28743
#define WALL_COLOR		0x002596BE

// render 3D
#define FLOOR_COLOR		0x003a2e27
#define CEIL_COLOR		0x00e4f7fa
#define WALL_COLOR1		0x00FF0000

#define RED_COLOR		0x00FF0000
#define GREEN_COLOR		0x0000FF00
#define BLUE_COLOR		0x000000FF
#define YELLOW_COLOR	0x00ff9933

#define PLAYER_RADIUS	15

typedef struct s_img
{
	void	*mlx_img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		height;
	int		width;
}	t_img;

typedef struct s_win
{
	void	*mlx;
	void	*mlx_win;
	t_img	frame;
}	t_win;

typedef struct s_pos
{
	int x;
	int y;
}	t_pos;

typedef struct s_map
{
	char		**wall_textures;
	int			*rgb_colors;
	char		**content;
	int			orientation;
	t_pos		pos;
}				t_map;

typedef struct s_pos_dec
{
	double x;
	double y;
}	t_pos_dec;

typedef struct s_value
{
	int x;
	int y;
}	t_value;

typedef struct s_value_dec
{
	double x;
	double y;
}	t_value_dec;

typedef struct s_ray
{
	float	dir;
	int		length;
	int		length_win;
	int		length_map;
	double	dist_wall;
	int		side;
	double	cos;
	double	cos2;
	double	sin;
	double	sx;
	double	sy;
}	t_ray;

typedef struct s_player 
{
	t_pos	pos;
	float	dir;
	float	angle_step;
	t_ray	*rays;
}	t_player;

typedef struct s_data
{
	t_win		*win;
	t_map		map;
	t_player	*player;
	t_img		tex;
}	t_data; 


// math_utils.c
int		math_abs(int n);
float	normalizeAngles(float angle);
double	cos_degree(double angle);
double	sin_degree(double angle);
int		clamp(int min, int max, int value);

//utils.c
t_pos		get_new_pos(t_pos init, double scale_x, double scale_y, int dist);
t_pos		get_map_pos(t_pos pos);
t_pos_dec	get_map_pos_decimal(t_pos pos);
t_pos		get_win_pos(t_pos pos);
t_pos 		get_new_dist_pos(t_pos init, float dir, int dist);
int			hex_to_int(const char *str);

//render_scene_2d.c
void render_scene_2d(t_img img, t_player player, char **map);

// render_scene_3d.c
void render_scene_3d(t_img img, t_player player);

// player.c
t_player	*player_init(t_pos pos, int dir);
void		player_update_vision(t_player *player, int rot_angle);
void		player_move(t_player *player, int dir);

// ray.c
void	ray_init(t_ray *ray, float dir, float p_dir);
void	ray_update_dir(t_ray *ray, float dir);

// raycast.c
void	raycast_all(t_player *player, char **map);

// draw_utils.c
void draw_pixel(t_img img, int x, int y, int color);
void draw_line(t_img img, t_pos init, t_pos end, int color);
void draw_vertical_line(t_img img, t_pos init_pos, int height, int color);
void draw_stroke_square(t_img img, t_pos init, int size, int color);
void draw_fill_square(t_img img, t_pos init, int size, int color);
void draw_fill_rectangle(t_img img, t_pos init, t_value size, int color);

// time.c
unsigned long	check_time_ms(unsigned long time);

// key_controls.c
int	key(int keycode, t_player *player);

// collisions.c
int check_collisions(t_pos p_pos, char **map);


void draw_tex_line(t_img frame, t_img tex, t_pos f_pos, t_pos tex_pos, int f_height);


#endif