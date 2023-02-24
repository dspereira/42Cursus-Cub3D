/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcandeia < dcandeia@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 12:14:20 by dsilveri          #+#    #+#             */
/*   Updated: 2023/02/24 11:01:08 by dcandeia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include "../includes/header.h"

int render_win(void *data);
static int get_game_configs(int ac, char **av, t_map *map);
void	setup_textures(char **tex_files, int *rgb, t_tex *texture, void *mlx);

int main(int argc, char **argv) 
{
	t_win		win;
	t_pos		pos1;
	t_pos		pos2;
	int			red;
	int 		size;
	t_player	*player;
	t_map		map;
	t_data		data;
	t_tex		tex;

	if (!get_game_configs(argc, argv, &map))
		return (-1);
	
	player = player_init((t_pos){100, 100}, 0);
	win.mlx = mlx_init();
	win.mlx_win = mlx_new_window(win.mlx, WIN_WIDTH, WIN_HEIGHT, "Cube3D");
	win.frame.mlx_img = mlx_new_image(win.mlx, WIN_WIDTH, WIN_HEIGHT);
	win.frame.addr = mlx_get_data_addr(win.frame.mlx_img, &(win.frame.bpp), &(win.frame.line_len), &(win.frame.endian));
	setup_textures(map.wall_textures, map.rgb_colors, &tex, win.mlx);
	data.win = &win;
	data.player = player;
	data.map = map;
	mouse_init(win, &data.mouse_state);
	data.tex = tex;
	mlx_loop_hook(win.mlx, render_win, &data);
	mlx_mouse_move(win.mlx, win.mlx_win, WIN_WIDTH / 2, WIN_HEIGHT / 2);
	mlx_hook(win.mlx_win, KEY_PRESS, KEY_PRESS_MASK, key, &data);
	mlx_mouse_hook(win.mlx_win, mouse_hook, &data);
	mlx_loop(win.mlx);
	return (0);
}

int render_win(void *data)
{
	static int	frames_count = 0;
	t_player	*player;
	t_map		map;
	t_win		win;

	player = ((t_data*)data)->player;
	map = ((t_data*)data)->map;
	win = *((t_data*)data)->win;

	raycast_all(player, map.content);
	
	//exit(0);
	if (((t_data*)data)->mouse_state == MOUSE_HIDE)
		player_rotation(win, player, mouse_get_pos(win));
	mouse_control(win, &((t_data*)data)->mouse_state);
	doors_control(map);
	//render_scene_2d(win.frame, *player, map.content);
	//render_scene_3d(win.frame, *player);
	render_scene_3d_tex(win.frame, *player, ((t_data*)data)->tex);

	//minimap_render(win.frame, *player, map.content);
	mlx_put_image_to_window(win.mlx, win.mlx_win, win.frame.mlx_img, 0, 0);
	frames_count++;
	if (check_time_ms(1000))
	{
		//printf("\033[2J\033[1;1H");
		printf("fps: %d\n", frames_count);
		frames_count = 0;
	}
	return (0);
}

static int get_game_configs(int ac, char **av, t_map *map)
{
	if (ac == 2)
	{
		printf("---------------\n");
		if (check_file(av[1]))
		{
			if (!init_map_struct(map))
				return (0);
			if (!get_all_map_info(&map, av[1]))
			{
				printf("Map KO\n");
				return (0);
			}
			else
				printf("Map OK\n");
		}
		else
		{
			printf("Map KO\n");
			return (0);
		}
		printf("---------------\n\n");
		//free_memory(map);
		return (1);
	}
	printf("Error: Invalid number of Arguments\n");
	return (0);
}

static void	init_doors_sprites_1(t_tex *tex, void *mlx)
{
	tex->doors[DOOR_CLOSE].mlx_img = mlx_xpm_file_to_image(mlx, D_TEX_CLOSE, \
		&(tex->doors[DOOR_CLOSE].width), &(tex->doors[DOOR_CLOSE].height));
	tex->doors[DOOR_CLOSE].addr = mlx_get_data_addr(tex->doors[DOOR_CLOSE].mlx_img, \
		&(tex->doors[DOOR_CLOSE].bpp), &(tex->doors[DOOR_CLOSE].line_len), \
		&(tex->doors[DOOR_CLOSE].endian));
	tex->doors[DOOR_OPEN_1].mlx_img = mlx_xpm_file_to_image(mlx, D_TEX_OPEN_1, \
		&(tex->doors[DOOR_OPEN_1].width), &(tex->doors[DOOR_OPEN_1].height));
	tex->doors[DOOR_OPEN_1].addr = mlx_get_data_addr(tex->doors[DOOR_OPEN_1].mlx_img, \
		&(tex->doors[DOOR_OPEN_1].bpp), &(tex->doors[DOOR_OPEN_1].line_len), \
		&(tex->doors[DOOR_OPEN_1].endian));
	tex->doors[DOOR_OPEN_2].mlx_img = mlx_xpm_file_to_image(mlx, D_TEX_OPEN_2, \
		&(tex->doors[DOOR_OPEN_2].width), &(tex->doors[DOOR_OPEN_2].height));
	tex->doors[DOOR_OPEN_2].addr = mlx_get_data_addr(tex->doors[DOOR_OPEN_2].mlx_img, \
		&(tex->doors[DOOR_OPEN_2].bpp), &(tex->doors[DOOR_OPEN_2].line_len), \
		&(tex->doors[DOOR_OPEN_2].endian));
	tex->doors[DOOR_OPEN_3].mlx_img = mlx_xpm_file_to_image(mlx, D_TEX_OPEN_3, \
		&(tex->doors[DOOR_OPEN_3].width), &(tex->doors[DOOR_OPEN_3].height));
	tex->doors[DOOR_OPEN_3].addr = mlx_get_data_addr(tex->doors[DOOR_OPEN_3].mlx_img, \
		&(tex->doors[DOOR_OPEN_3].bpp), &(tex->doors[DOOR_OPEN_3].line_len), \
		&(tex->doors[DOOR_OPEN_3].endian));
}

static void	init_doors_sprites_2(t_tex *tex, void *mlx)
{
	tex->doors[DOOR_OPEN_4].mlx_img = mlx_xpm_file_to_image(mlx, D_TEX_OPEN_4, \
		&(tex->doors[DOOR_OPEN_4].width), &(tex->doors[DOOR_OPEN_4].height));
	tex->doors[DOOR_OPEN_4].addr = mlx_get_data_addr(tex->doors[DOOR_OPEN_4].mlx_img, \
		&(tex->doors[DOOR_OPEN_4].bpp), &(tex->doors[DOOR_OPEN_4].line_len), \
		&(tex->doors[DOOR_OPEN_4].endian));
	tex->doors[DOOR_OPEN_5].mlx_img = mlx_xpm_file_to_image(mlx, D_TEX_OPEN_5, \
		&(tex->doors[DOOR_OPEN_5].width), &(tex->doors[DOOR_OPEN_5].height));
	tex->doors[DOOR_OPEN_5].addr = mlx_get_data_addr(tex->doors[DOOR_OPEN_5].mlx_img, \
		&(tex->doors[DOOR_OPEN_5].bpp), &(tex->doors[DOOR_OPEN_5].line_len), \
		&(tex->doors[DOOR_OPEN_5].endian));
	tex->doors[DOOR_OPEN_6].mlx_img = mlx_xpm_file_to_image(mlx, D_TEX_OPEN_6, \
		&(tex->doors[DOOR_OPEN_6].width), &(tex->doors[DOOR_OPEN_6].height));
	tex->doors[DOOR_OPEN_6].addr = mlx_get_data_addr(tex->doors[DOOR_OPEN_6].mlx_img, \
		&(tex->doors[DOOR_OPEN_6].bpp), &(tex->doors[DOOR_OPEN_6].line_len), \
		&(tex->doors[DOOR_OPEN_6].endian));
	tex->doors[DOOR_OPEN_7].mlx_img = mlx_xpm_file_to_image(mlx, D_TEX_OPEN_7, \
		&(tex->doors[DOOR_OPEN_7].width), &(tex->doors[DOOR_OPEN_7].height));
	tex->doors[DOOR_OPEN_7].addr = mlx_get_data_addr(tex->doors[DOOR_OPEN_7].mlx_img, \
		&(tex->doors[DOOR_OPEN_7].bpp), &(tex->doors[DOOR_OPEN_7].line_len), \
		&(tex->doors[DOOR_OPEN_7].endian));
	tex->doors[DOOR_OPEN].mlx_img = mlx_xpm_file_to_image(mlx, D_TEX_OPEN, \
		&(tex->doors[DOOR_OPEN].width), &(tex->doors[DOOR_OPEN].height));
	tex->doors[DOOR_OPEN].addr = mlx_get_data_addr(tex->doors[DOOR_OPEN].mlx_img, \
		&(tex->doors[DOOR_OPEN].bpp), &(tex->doors[DOOR_OPEN].line_len), \
		&(tex->doors[DOOR_OPEN].endian));
}

static void	init_doors_tex(t_tex *tex, void *mlx)
{
	tex->door_side.mlx_img = mlx_xpm_file_to_image(mlx, SIDE_DOOR_TEX, \
		&(tex->door_side.width), &(tex->door_side.height));
	tex->door_side.addr = mlx_get_data_addr(tex->door_side.mlx_img, \
		&(tex->door_side.bpp), &(tex->door_side.line_len), \
		&(tex->door_side.endian));
	init_doors_sprites_1(tex, mlx);
	init_doors_sprites_2(tex, mlx);
}

void	setup_textures(char **tex_files, int *rgb, t_tex *texture, void *mlx)
{
	texture->no.mlx_img = mlx_xpm_file_to_image(mlx, tex_files[TEX_NO], \
		&(texture->no.width), &(texture->no.height));
	texture->no.addr = mlx_get_data_addr(texture->no.mlx_img, \
		&(texture->no.bpp), &(texture->no.line_len), &(texture->no.endian));
	texture->so.mlx_img = mlx_xpm_file_to_image(mlx, tex_files[TEX_SO], \
		&(texture->so.width), &(texture->so.height));
	texture->so.addr = mlx_get_data_addr(texture->so.mlx_img, \
		&(texture->so.bpp), &(texture->so.line_len), &(texture->so.endian));
	texture->ea.mlx_img = mlx_xpm_file_to_image(mlx, tex_files[TEX_EA], \
		&(texture->ea.width), &(texture->ea.height));
	texture->ea.addr = mlx_get_data_addr(texture->ea.mlx_img, \
		&(texture->ea.bpp), &(texture->ea.line_len), &(texture->ea.endian));
	texture->we.mlx_img = mlx_xpm_file_to_image(mlx, tex_files[TEX_WE], \
		&(texture->we.width), &(texture->we.height));
	texture->we.addr = mlx_get_data_addr(texture->we.mlx_img, \
		&(texture->we.bpp), &(texture->we.line_len), &(texture->we.endian));
	init_doors_tex(texture, mlx);
	texture->ceil_rgb = rgb[RGB_C];
	texture->floor_rgb = rgb[RGB_F];
}
