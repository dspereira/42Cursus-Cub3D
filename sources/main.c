/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 12:14:20 by dsilveri          #+#    #+#             */
/*   Updated: 2023/02/10 15:21:52 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include "../includes/header.h"

int render_win(void *data);
static int get_game_configs(int ac, char **av, t_map *map);

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

	get_game_configs(argc, argv, &map);

	player = player_init((t_pos){100, 100}, 0);
	win.mlx = mlx_init();
	win.mlx_win = mlx_new_window(win.mlx, WIN_WIDTH, WIN_HEIGHT, "Cube3D");
	win.frame.mlx_img = mlx_new_image(win.mlx, WIN_WIDTH, WIN_HEIGHT);
	win.frame.addr = mlx_get_data_addr(win.frame.mlx_img, &(win.frame.bpp), &(win.frame.line_len), &(win.frame.endian));
	data.win = &win;
	data.player = player;
	data.map = map;
	
	mouse_init(win, &data.mouse_state);
	mlx_loop_hook(win.mlx, render_win, &data);
	mlx_mouse_move(win.mlx, win.mlx_win, WIN_WIDTH / 2, WIN_HEIGHT / 2);
	mlx_key_hook(win.mlx_win, key, &data);
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
	//render_scene_2d(win.frame, *player, map.content);

	if (((t_data*)data)->mouse_state == MOUSE_HIDE)
		player_rotation(win, player, mouse_get_pos(win));
	mouse_control(win, &((t_data*)data)->mouse_state);
	
	render_scene_3d(win.frame, *player);
	mlx_put_image_to_window(win.mlx, win.mlx_win, win.frame.mlx_img, 0, 0);



	frames_count++;
	if (check_time_ms(1000))
	{
		printf("fps: %d\n", frames_count);
		frames_count = 0;
	}
}

static int get_game_configs(int ac, char **av, t_map *map)
{
	if (ac == 2)
	{
		if (check_file(av[1]))
		{
			if (!init_map_struct(map))
				return (-1);
			if (!get_all_map_info(&map, av[1]))
				printf("Map KO\n");
			else
				printf("Map OK\n");
		}
		else
			printf("Map KO\n");
		//free_memory(map);
		return (0);
	}
	printf("Error: Invalid number of Arguments\n");
	return (-1);
}
