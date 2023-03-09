/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 10:50:11 by dsilveri          #+#    #+#             */
/*   Updated: 2023/03/09 13:36:33 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include <sys/time.h>
# include <fcntl.h>
# include <mlx.h>

# define FALSE					0
# define TRUE					1

# define FLOOR 					'0'
# define WALL					'1'
# define DOOR_OPENING_START 	'G'
# define DOOR_OPENING_END 	 	'N'
# define DOOR_CLOSING_START 	'g'
# define DOOR_CLOSING_END 	 	'n'

# define MAP_HEIGHT		26
# define MAP_WIDTH		26

# define MAP_SQUARE_SIZE	40

# define WIN_HEIGHT		720
# define WIN_WIDTH		1080

# define CAMERA_ANGLE		60
# define NUMBER_RAYS		WIN_WIDTH

# define KEY_W				119
# define KEY_S				115
# define KEY_A				97
# define KEY_D				100
# define KEY_Q				113
# define KEY_E				101
# define KEY_ESC			65307
# define KEY_CTRL			65507

# define KEY_PRESS			2
# define KEY_RELEASE		3

# define BUTTON_LEFT_CLICK	1

# define KEY_ARROW_L		65361
# define KEY_ARROW_R		65363

# define FORWARD			0
# define BACKWARD			180
# define LEFT				90
# define RIGHT				270

# define ROT_STEP			2
# define MOVE_STEP			3

# define PLAYER_MINIMAP_SIZE	4

# define FLOOR_COLOR			0x003a2e27
# define CEIL_COLOR				0x00e4f7fa
# define WALL_COLOR1			0x00FF0000

# define RED_COLOR				0x00FF0000
# define GREEN_COLOR			0x0000FF00
# define BLUE_COLOR				0x000000FF
# define YELLOW_COLOR			0x00ff9933

# define BGD_MINIMAP_COLOR		0x66000000

# define PLAYER_RADIUS		4

# define MOUSE_HIDE			1
# define MOUSE_SHOW			2
# define MOUSE_CHANGE_SHOW	3
# define MOUSE_CHANGE_HIDE	4

# define NO_SIDE			-2
# define SO_SIDE			2
# define EA_SIDE			1
# define WE_SIDE			-1

# define NO_DOOR			'A'
# define SO_DOOR			'B'
# define EA_DOOR			'C'
# define WE_DOOR			'D'

# define DOOR_SIDE			'3'

# define DOOR_CLOSE			0
# define DOOR_OPEN_1		1
# define DOOR_OPEN_2		2
# define DOOR_OPEN_3		3
# define DOOR_OPEN_4		4
# define DOOR_OPEN_5		5
# define DOOR_OPEN_6		6
# define DOOR_OPEN_7		7
# define DOOR_OPEN			8

# define SIDE_DOOR_TEX		"./textures/door_walls_1.xpm"
# define D_TEX_CLOSE		"./textures/door_sprites/close_door.xpm"
# define D_TEX_OPEN			"./textures/door_sprites/open_door.xpm"
# define D_TEX_OPEN_1		"./textures/door_sprites/door_open_1.xpm"
# define D_TEX_OPEN_2		"./textures/door_sprites/door_open_2.xpm"
# define D_TEX_OPEN_3		"./textures/door_sprites/door_open_3.xpm"
# define D_TEX_OPEN_4		"./textures/door_sprites/door_open_4.xpm"
# define D_TEX_OPEN_5		"./textures/door_sprites/door_open_5.xpm"
# define D_TEX_OPEN_6		"./textures/door_sprites/door_open_6.xpm"
# define D_TEX_OPEN_7		"./textures/door_sprites/door_open_7.xpm"

# define D_FRAME_OPEN_0		'G'
# define D_FRAME_OPEN_1		'H'
# define D_FRAME_OPEN_2		'I'
# define D_FRAME_OPEN_3		'J'
# define D_FRAME_OPEN_4		'K'
# define D_FRAME_OPEN_5		'L'
# define D_FRAME_OPEN_6		'M'
# define D_FRAME_OPEN_7		'N'

# define D_FRAME_CLOSE_0	'g'
# define D_FRAME_CLOSE_1	'h'
# define D_FRAME_CLOSE_2	'i'
# define D_FRAME_CLOSE_3	'j'
# define D_FRAME_CLOSE_4	'k'
# define D_FRAME_CLOSE_5	'l'
# define D_FRAME_CLOSE_6	'm'
# define D_FRAME_CLOSE_7	'n'

# define NONE_COLOR_VALUE	0x00FFFFFF

# define DOOR_TIME_SPRITES	75
# define DIST_OPEN_DOOR		1.5

# define MOVE_SPEED_MS		25

# define MINIMAP_SQUARE_SIZE	15
# define MINIMAP_PLAYER_RADIUS	4
# define MINIMAP_ARROW_SIZE		10
# define MINIMAP_PLAYER_COLOR 	0x00FFFFFF
# define MINIMAP_ARROW_COLOR  	0x00880606
# define MINIMAP_COLOR_NONE		0xFFFFFFFF
# define MINIMAP_COLOR_GROUND	0x00668284
# define MINIMAP_COLOR_WALL		0x002A2829

# define MINIMAP_COLOR_DOOR_CLOSE	0x00D92525
# define MINIMAP_COLOR_DOOR_OPEN		0x0002A676

# define TIME_PER_FRAME		1000
# define FRAMES_TEXT_COLOR	0
# define FRAMES_WIN_POS_X	20
# define FRAMES_WIN_POS_Y	20

# define TEX_NO		0
# define TEX_SO		1
# define TEX_WE		2
# define TEX_EA		3

# define RGB_C			0
# define RGB_F			1
# define RGB_NO_COLOR	-1

# define ORIENTATION_N	90
# define ORIENTATION_S	270
# define ORIENTATION_E	0
# define ORIENTATION_W	180

# define BUFFER_SIZE	13

# define FALSE	0
# define TRUE	1

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
	char	*nbr_frames;
}	t_win;

typedef struct s_pos
{
	int	x;
	int	y;
}	t_pos;

typedef struct s_tex
{
	t_img	no;
	t_img	so;
	t_img	ea;
	t_img	we;
	t_img	door_side;
	t_img	doors[9];
	int		ceil_rgb;
	int		floor_rgb;
}				t_tex;

typedef struct s_map
{
	char		**wall_textures;
	int			*rgb_colors;
	char		**content;
	int			orientation;
	t_pos		pos;
	int			height;
	int			width;
	t_pos		*doors;
}				t_map;

typedef struct s_pos_dec
{
	double	x;
	double	y;
}	t_pos_dec;

typedef struct s_value
{
	int	x;
	int	y;
}	t_value;

typedef struct s_value_dec
{
	double	x;
	double	y;
}	t_value_dec;

typedef struct s_ray
{
	float	dir;
	int		length;
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
	int		door_side_wall;
	int		door_side;
	double	door_dist;
	t_pos	door_pos;
	char	door_tex;
}	t_ray;

typedef struct s_player
{
	t_pos		pos;
	t_pos_dec	pos_dec;
	float		dir;
	float		angle_step;
	t_ray		*rays;
	int			dir_y;
	int			midle_dir_y;
	int			max_dir_y;
	int			min_dir_y;
	int			win_half_size;

}	t_player;

typedef struct s_tex_data
{
	t_img		tex;
	t_pos		win_start_pos;
	double		map_wall_pos;
	int			height;
}	t_tex_data;

typedef struct s_minimap
{
	t_value	size;
	t_value	half_size;
	t_value	scaled_map_size;
	t_value	map_size;
	t_pos	win_pos;
	float	map_scale;
}	t_minimap;

typedef struct s_mouse
{
	t_pos	actual;
	t_pos	last;
}	t_mouse;

typedef struct s_key
{
	int	w;
	int	s;
	int	a;
	int	d;
	int	arrow_r;
	int	arrow_l;
}	t_key;

typedef struct s_data
{
	t_win		*win;
	t_map		map;
	t_player	*player;
	t_tex		tex;
	t_minimap	minimap;
	int			mouse_state;
	t_mouse		mouse;
	t_key		key_state;
}	t_data;

typedef struct s_alloc_mem
{
	t_data		*data;
}				t_alloc_mem;

// main.c
int				close_game(void);

// math_utils.c
int				math_abs(int n);
float			normalize_angles(float angle);
double			cos_degree(double angle);
double			sin_degree(double angle);
int				clamp(int min, int max, int value);

// utils.c
t_pos_dec		get_new_dist_pos_dec(t_pos_dec init, float dir, double dist);
t_pos_dec		get_map_pos_decimal_1(t_pos_dec pos);
t_pos			get_new_pos(t_pos init, double scale_x, double scale_y, int dist);
t_pos			get_map_pos(t_pos pos);
t_pos			get_map_pos_1(t_pos_dec pos);
t_pos_dec		get_map_pos_decimal(t_pos pos);
t_pos			get_win_pos(t_pos pos);
t_pos			get_new_dist_pos(t_pos init, float dir, int dist);
t_pos_dec		get_map_pos_decimal_1(t_pos_dec pos);

// render_scene_3d.c
void			render_scene_3d_tex(t_img img, t_player player, t_tex tex);

// player.c
void			player_init(t_player **player, t_pos pos, int dir);
void			player_move(t_player *player, char **map, int dir);
void			player_rotation_key(t_player *player, float rot_angle);
void			player_update_rays(t_ray *rays, float rot_angle);

// ray.c
void			ray_init(t_ray *ray, float dir, float p_dir);
void			ray_update_dir(t_ray *ray, float dir);

// raycast/raycast.c
void			raycast_all(t_player *player, char **map);

// raycast/raycast_update.c
void			raycast_update(t_ray *ray, t_pos *m_pos, t_value_dec *ray_l, t_value step);

// raycast/raycast_door.c
void			raycast_door_set_inf(t_ray *ray, t_pos m_pos, t_pos_dec p_pos, char **map);
void			raycast_door_set_dist(t_ray *ray, t_value_dec ray_len);
void			raycast_door_set_wall_side(t_ray *ray, t_pos m_pos, char **map);

// raycast/raycast_wall.c
void			raycast_wall_set_dist(t_ray *ray, t_value_dec ray_len);
void			raycast_set_wall_inf(t_ray *ray, t_pos m_pos, t_pos_dec p_pos);

// raycast/raycast_utils.c
int				is_floor(char **map, t_pos pos);
int				is_door(char **map, t_pos pos);

// raycast/raycast_utils2.c
int				get_const_axis_collision(int side, t_pos m_pos);
t_pos_dec		get_ray_collision_pos_pixels(t_ray ray, t_pos_dec p_pos);
void			set_ray_leng_pixels(t_ray *ray, t_pos m_pos, t_pos_dec p_pos);
double			get_ray_collision_map(t_ray ray, t_pos_dec p_pos);
double			get_ray_dist_to_wall(t_ray *ray, t_value_dec ray_leng);

// draw_utils/draw_utils.c
void			draw_pixel(t_img img, int x, int y, int color);
void			draw_line(t_img img, t_pos init, t_pos end, int color);
void			draw_line_tex(t_img frame, t_tex_data wall);
void			draw_door_tex(t_img frame, t_tex_data wall);

// draw_utils/draw_utils2.c
void			draw_vertical_line(t_img img, t_pos init_pos, int height, int color);
void			draw_fill_rectangle(t_img img, t_pos init, t_value size, int color);

// time.c
unsigned long	check_time_ms(unsigned long time);
unsigned long	doors_time_check_ms(unsigned long time);
unsigned long	moves_time_check_ms(unsigned long time);

// key_controls.c
t_key			key_init(void);
int				key_press_hook(int keycode, t_data *data);
int				key_release_hook(int keycode, t_data *data);
void			key_move_control(t_key key, t_player *player, char **map);

// collisions.c
int				check_collisions(t_pos p_pos, char **map);

// mouse.c
void			mouse_init(t_win win, int *mouse_state);
t_pos			mouse_get_pos(t_win win);
void			mouse_update(t_mouse *mouse, t_pos mouse_pos);
void			mouse_recenter(t_win win, t_mouse *mouse);
void			mouse_state_control(t_win win, int *mouse_state);

// mouse_hook.c
int				mouse_hook(int button, int x, int y, t_data *data);

// player_rot_mouse.c
void			player_rot_mouse(t_player *player, t_mouse mouse);

// minimap.c
t_minimap		minimap_init(int map_width, int map_height);
void			minimap_render(t_img img, char **map, t_player pl, t_minimap minimap);

// minimap_draw_player.c
void			minimap_draw_player(t_img img, t_player player, t_minimap minimap);

// minimap_utils.c
t_pos			get_player_pos_map_scaled(t_pos pos, t_minimap minimap);
t_pos			get_minimap_init_pos(t_pos p_pos, t_minimap minimap);
int				get_pixel_color(t_pos pos, char **map, t_value map_size);
t_pos			get_scaled_map_pos(t_pos pos);
t_pos			get_minimap_pos(t_pos pos, t_pos p_pos, t_minimap minimap);

// doors.c
void			doors_interaction(t_map map, t_player *player);
void			doors_control(t_map map);

// setup_textures.c
void			setup_textures(char **tex_files, int *rgb, t_tex *texture, void *mlx);
t_pos			get_new_dist_pos1(t_pos init, float dir, int dist);

// frame_count.c
void			frame_count(t_win *win);

// free_map_memory.c
void			free_map_memory(t_map map);

// free_memory_utils.c
void			free_tex_memory(t_tex tex, t_win *win);
void			free_mlx_memory(t_win *win);
void			free_player_memory(t_player *player);

// error_handler.c
void			print_error_msg(char *msg);
void			free_alloc_mem(void);
void			*oom_guard(void *p);

// init_data_pointers.c
void			init_data_pointers(t_data *data);

// alloc_memory.c
void			init_alloc_mem(void);
void			save_alloc_mem(t_data *data);
void			free_alloc_mem(void);

// map_filr_checker
int				get_game_configs(int ac, char **av, t_map *map);
void			*ft_calloc(size_t count, size_t size);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
size_t			ft_strlen(const char *src);
void			putstr_error(char *str);
int				check_file(char *filename);
int				is_valid_file_type(char *file);
int				check_textures(char **textures, int *rgb_colors);
int				get_map_textures(t_map **map, int fd);
char			*get_next_line(int fd);
int				get_map_content(char ***content, int fd);
int				get_player_info(char **map, int *orientation, t_pos *pos);
int         	get_map_dimensions(t_map **map);
int         	get_doors_info(char **map, t_pos **doors);
int				check_map(char **map);
int				check_map_elements(char **map);
int				check_map_walls(char **map);
int				init_map_struct(t_map *init);
int				get_all_map_info(t_map **map, char *filename);

#endif
