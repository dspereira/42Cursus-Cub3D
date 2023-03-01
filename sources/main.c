/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 12:14:20 by dsilveri          #+#    #+#             */
/*   Updated: 2023/03/01 10:32:19 by dsilveri         ###   ########.fr       */
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
	if (!get_game_configs(argc, argv, &map))
		return (-1);

	printf("height: %i, width: %i\n", map.height, map.width);

	player = player_init(map.pos, map.orientation);

	data.mouse.actual = (t_pos){WIN_WIDTH / 2, WIN_HEIGHT / 2};
	data.mouse.last = (t_pos){0, 0};

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
	//mlx_mouse_move(win.mlx, win.mlx_win, WIN_WIDTH / 2, WIN_HEIGHT / 2);
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
	t_mouse		mouse;

	player = ((t_data*)data)->player;
	map = ((t_data*)data)->map;
	win = *((t_data*)data)->win;
	mouse = ((t_data*)data)->mouse;
	//raycast_all(player, map.content);
	
	//exit(0);
	
	t_pos aux_pos;
	if (((t_data*)data)->mouse_state == MOUSE_HIDE)
	{
		update_mouse(&mouse, mouse_get_pos(win));

		
		player_rot_mouse(player, mouse);

		if (mouse.actual.x >= WIN_WIDTH || mouse.actual.x <= 0)
		{
			mouse.actual.x = WIN_WIDTH / 2;
			
			aux_pos = mouse_get_pos(win);
			aux_pos.x = WIN_WIDTH / 2;
			update_mouse(&mouse, aux_pos);
			mlx_mouse_move(win.mlx, win.mlx_win, mouse.actual.x, mouse.actual.y);	
		}

		if (mouse.actual.y >= WIN_HEIGHT || mouse.actual.y <= 0)
		{
			mouse.actual.y = WIN_HEIGHT / 2;
			
			aux_pos = mouse_get_pos(win);
			aux_pos.y = WIN_HEIGHT / 2;
			update_mouse(&mouse, aux_pos);
			mlx_mouse_move(win.mlx, win.mlx_win, mouse.actual.x, mouse.actual.y);	
		}
		
		

		((t_data*)data)->mouse = mouse;

	}
		
	mouse_control(win, &((t_data*)data)->mouse_state);

	raycast_all(player, map.content);

	// mouse state control	
	doors_control(map);
	//render_scene_2d(win.frame, *player, map.content);
	//render_scene_3d(win.frame, *player);
	render_scene_3d_tex(win.frame, *player, ((t_data*)data)->tex);

	//minimap_render(win.frame, *player, map.content);
	minimap_render(win.frame, map.content, *player, ((t_data*)data)->minimap);
	mlx_put_image_to_window(win.mlx, win.mlx_win, win.frame.mlx_img, 0, 0);
	frames_count++;
	if (check_time_ms(1000))
	{
		//printf("\033[2J\033[1;1H");
		printf("fps: %d\n", frames_count);
		frames_count = 0;
	}
	//mouse_control(win, &((t_data*)data)->mouse_state);
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
