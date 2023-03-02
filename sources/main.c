/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 12:14:20 by dsilveri          #+#    #+#             */
/*   Updated: 2023/03/02 12:54:32 by dsilveri         ###   ########.fr       */
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
	if (!get_game_configs(argc, argv, &(data.map)))
		return (-1);

	data.player = player_init(data.map.pos, data.map.orientation);
	data.key_state = key_init();
	data.mouse.actual = (t_pos){WIN_WIDTH / 2, WIN_HEIGHT / 2};
	data.mouse.last = (t_pos){0, 0};
	data.win = ft_calloc(1, sizeof(t_win));
	data.win->mlx = mlx_init();
	data.win->mlx_win = mlx_new_window(data.win->mlx, WIN_WIDTH, WIN_HEIGHT, "Cube3D");
	data.win->frame.mlx_img = mlx_new_image(data.win->mlx, WIN_WIDTH, WIN_HEIGHT);
	data.win->frame.addr = mlx_get_data_addr(data.win->frame.mlx_img, &(data.win->frame.bpp),
		&(data.win->frame.line_len), &(data.win->frame.endian));
	setup_textures(data.map.wall_textures, data.map.rgb_colors, &data.tex, data.win->mlx);
	//data.win = &win;
	//data.player = player;
	//data.map = map;
	data.minimap = minimap_init(data.map.width, data.map.height);
	mouse_init(*(data.win), &data.mouse_state);
	//data.tex = tex;
	mlx_loop_hook(data.win->mlx, render_win, &data);
	//mlx_mouse_move(data.win->mlx, data.win->mlx_win, WIN_WIDTH / 2, WIN_HEIGHT / 2);
	//mlx_hook(data.win->mlx_win, KEY_PRESS, KEY_PRESS_MASK, key, &data);
	mlx_hook(data.win->mlx_win, KEY_PRESS, KEY_PRESS_MASK, key_press_hook, &data);
	mlx_hook(data.win->mlx_win, KEY_RELEASE, KEY_RELEASE_MASK, key_release_hook, &data);
	mlx_mouse_hook(data.win->mlx_win, mouse_hook, &data);
	mlx_loop(data.win->mlx);
	return (0);
}

int render_win(void *data)
{
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
	
	raycast_all(player, map.content);

	if (((t_data*)data)->mouse_state == MOUSE_HIDE)
	{
		mouse_update(&mouse, mouse_get_pos(win));
		player_rot_mouse(player, mouse);
		mouse_recenter(win, &mouse);
		((t_data*)data)->mouse = mouse;
	}
	mouse_state_control(win, &((t_data*)data)->mouse_state);

	key_move_control(((t_data*)data)->key_state, player, map.content);

	// mouse state control	
	mlx_clear_window(win.mlx, win.mlx_win);
	//mouse_control(win, &((t_data*)data)->mouse_state);
	doors_control(map);
	//render_scene_2d(win.frame, *player, map.content);
	//render_scene_3d(win.frame, *player);
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
