/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcandeia <dcandeia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 10:50:11 by dsilveri          #+#    #+#             */
/*   Updated: 2023/02/16 18:08:24 by dcandeia         ###   ########.fr       */
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

// valor tem de ser defenidos consoante o mapa recebido (não pode ser define)
#define MAP_HEIGHT		26
#define MAP_WIDTH		26

#define	MINIMAP_SQUARE_SIZE	15

#define WIN_HEIGHT		1040
#define WIN_WIDTH		1040

#define CAMERA_ANGLE	50
#define	NUMBER_RAYS		WIN_WIDTH

#define KEY_W				119
#define KEY_S				115
#define KEY_A				97
#define KEY_D				100
#define KEY_Q				113
#define KEY_ESC				65307
#define KEY_CTRL			65507

#define KEY_PRESS			2
#define KEY_PRESS_MASK		1L

#define BUTTON_LEFT_CLICK	1

#define KEY_ARROW_L		65361
#define KEY_ARROW_R		65363

#define FORWARD			0
#define BACKWARD		180
#define LEFT			90
#define RIGHT			270

#define ROT_STEP		2
#define MOVE_STEP		2

// render 2D
#define PLAYER_SIZE		10
#define PLAYER_COLOR	0x00E28743
#define WALL_COLOR		0x002596BE

#define PLAYER_MINIMAP_SIZE	4

// render 3D
#define FLOOR_COLOR		0x003a2e27
#define CEIL_COLOR		0x00e4f7fa
#define WALL_COLOR1		0x00FF0000

#define RED_COLOR		0x00FF0000
#define GREEN_COLOR		0x0000FF00
#define BLUE_COLOR		0x000000FF
#define YELLOW_COLOR	0x00ff9933

//#define BGD_MINIMAP_COLOR	0x00c0c1c2
#define BGD_MINIMAP_COLOR	0x66000000

#define PLAYER_RADIUS	8

#define MOUSE_HIDE			1
#define MOUSE_SHOW			2
#define MOUSE_CHANGE_SHOW	3
#define MOUSE_CHANGE_HIDE	4

#define NO_SIDE			-2	//amarelo
#define SO_SIDE			2	//azul
#define EA_SIDE			1	//verde
#define WE_SIDE			-1	//vermelho

#define NO_DOOR			'A'
#define SO_DOOR			'B'
#define EA_DOOR			'C'
#define WE_DOOR			'D'

#define DOOR_SIDE		'3'

#define SIDE_DOOR_TEX	"./textures/door_wall.xpm"
#define DOOR_TEX	"./textures/close_door.xpm"

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

typedef struct s_tex
{
	t_img	no;
	t_img	so;
	t_img	ea;
	t_img	we;
	t_img	door_side;
	t_img	door;
	int		ceil_rgb;
	int		floor_rgb;
}				t_tex;

typedef struct s_door
{
	t_pos	pos;
	float	status;
}			t_door;

typedef struct s_map
{
	char		**wall_textures;
	int			*rgb_colors;
	char		**content;
	int			orientation;
	t_pos		pos;
	int			height;
	int			width;
	t_door		*doors;
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
	//int		length_win;
	double	length_win;
	int		length_map;
	double	dist_wall;
	int		side;
	double	cos;
	double	cos2;
	double	sin;
	double	sx;
	double	sy;
	double	map_wall_pos;
	double	map_door_pos;
	int		is_door;
	int		door_side;
	double	door_dist;
}	t_ray;

typedef struct s_player 
{
	t_pos	pos;
	float	dir;
	int		dir_y;
	float	angle_step;
	t_ray	*rays;
}	t_player;

typedef struct s_wall_data
{
	t_img		tex;
	t_pos		win_start_pos;
	double		map_wall_pos;
	int			height;
}	t_wall_data;

typedef struct s_data
{
	t_win		*win;
	t_map		map;
	t_player	*player;
	t_tex		tex;
	int			mouse_state;
}	t_data; 


// math_utils.c
int		math_abs(int n);
float	normalizeAngles(float angle);
double	cos_degree(double angle);
double	sin_degree(double angle);
int		clamp(int min, int max, int value);

//utils.c
t_pos_dec	get_new_dist_pos_dec(t_pos init, float dir, double dist);
t_pos_dec	get_map_pos_decimal_1(t_pos_dec pos);
t_pos		get_new_pos(t_pos init, double scale_x, double scale_y, int dist);
t_pos		get_map_pos(t_pos pos);
t_pos_dec	get_map_pos_decimal(t_pos pos);
t_pos		get_win_pos(t_pos pos);
t_pos 		get_new_dist_pos(t_pos init, float dir, int dist);
int			hex_to_int(const char *str);

t_pos_dec  	get_new_dist_pos_dec(t_pos init, float dir, double dist);
t_pos_dec 	get_map_pos_decimal_1(t_pos_dec pos);

void		*ft_calloc(size_t count, size_t size);

//render_scene_2d.c
void render_scene_2d(t_img img, t_player player, char **map);

// render_scene_3d.c
void render_scene_3d(t_img img, t_player player);
void render_scene_3d_tex(t_img img, t_player player, t_tex tex);

// player.c
t_player	*player_init(t_pos pos, int dir);
void		player_update_vision(t_player *player, float rot_angle);
void 		player_move(t_player *player, char **map, int dir);
void 		player_rotation(t_win win, t_player *player, t_pos mouse_pos);

// ray.c
void	ray_init(t_ray *ray, float dir, float p_dir);
void	ray_update_dir(t_ray *ray, float dir);

// raycast.c
void	raycast_all(t_player *player, char **map);

// draw_utils.c
void draw_pixel(t_img img, int x, int y, int color);
void draw_line(t_img img, t_pos init, t_pos end, int color);

void draw_line_tex(t_img frame, t_wall_data wall);

void draw_door_tex(t_img frame, t_wall_data wall);

void draw_vertical_line(t_img img, t_pos init_pos, int height, int color);
void draw_stroke_square(t_img img, t_pos init, int size, int color);
void draw_fill_square(t_img img, t_pos init, int size, int color);
void draw_fill_rectangle(t_img img, t_pos init, t_value size, int color);

// time.c
unsigned long	check_time_ms(unsigned long time);

// key_controls.c
int	key(int keycode, t_data *data);

// collisions.c
int check_collisions(t_pos p_pos, char **map);

void draw_tex_line(t_img frame, t_img tex, t_pos f_pos, t_pos tex_pos, int f_height);

// mouse.c
void	mouse_init(t_win win, int *mouse_state);
t_pos	mouse_get_pos(t_win win);
void	mouse_control(t_win win, int *mouse_state);
int		mouse_hook(int button, int x, int y, t_data *data);

// minimap.c
void	minimap_render(t_img img, t_player player, char **map);


#endif