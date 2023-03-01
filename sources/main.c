/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcandeia < dcandeia@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 12:14:20 by dsilveri          #+#    #+#             */
/*   Updated: 2023/03/01 17:46:15 by dcandeia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include "../includes/header.h"

int			render_win(void *data);
static int	get_game_configs(int ac, char **av, t_map *map);

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

	if (argc < 2)
	{
		printf("Invalid number of arguments\n");
		return (-1);
	}
	init_data_pointers(&data);
	if (!get_game_configs(argc, argv, &map))
		return (-1);

	player = player_init(map.pos, map.orientation);

	win.mlx = mlx_init();
	win.mlx_win = mlx_new_window(win.mlx, WIN_WIDTH, WIN_HEIGHT, "Cube3D");
	win.frame.mlx_img = mlx_new_image(win.mlx, WIN_WIDTH, WIN_HEIGHT);
	win.frame.addr = mlx_get_data_addr(win.frame.mlx_img, &(win.frame.bpp), &(win.frame.line_len), &(win.frame.endian));
	setup_textures(map.wall_textures, map.rgb_colors, &tex, win.mlx);
	data.win = &win;
	data.player = player;
	data.map = map;
	data.minimap = minimap_init(map.width, map.height);
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
	t_player	*player;
	t_map		map;
	t_win		win;

	player = ((t_data*)data)->player;
	map = ((t_data*)data)->map;
	win = *((t_data*)data)->win;

	raycast_all(player, map.content);

	//exit(0);
	if (((t_data*)data)->mouse_state == MOUSE_HIDE)
		player_rot_mouse(player, mouse_get_pos(win));
		//player_rotation(win, player, mouse_get_pos(win));

	// mouse state control	
	mouse_control(win, &((t_data*)data)->mouse_state);
	doors_control(map);
	//render_scene_2d(win.frame, *player, map.content);
	//render_scene_3d(win.frame, *player);
	mlx_clear_window(win.mlx, win.mlx_win);
	render_scene_3d_tex(win.frame, *player, ((t_data*)data)->tex);

	//minimap_render(win.frame, *player, map.content);
	minimap_render(win.frame, map.content, *player, ((t_data*)data)->minimap);
	mlx_put_image_to_window(win.mlx, win.mlx_win, win.frame.mlx_img, 0, 0);
	frame_count(win);
	//mlx_destroy_image(win.mlx, win.frame.mlx_img);
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
				//free_map_memory(*map);
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
		return (1);
	}
	printf("Error: Invalid number of Arguments\n");
	return (0);
}
