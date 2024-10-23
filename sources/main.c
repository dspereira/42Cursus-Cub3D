/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 12:14:20 by dsilveri          #+#    #+#             */
/*   Updated: 2023/03/09 12:39:37 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include "cube3d.h"

static void	game_win_init(t_win *win);
static int	game_init_data(int argc, char **argv, t_data *data);
static int	render_win(void *data);

int	main(int argc, char **argv)
{
	t_data	data;

	if (game_init_data(argc, argv, &data) == -1)
		return (EXIT_FAILURE);
	game_win_init(data.win);
	setup_textures(data.map.wall_textures, data.map.rgb_colors,
		&data.tex, data.win->mlx);
	data.minimap = minimap_init(data.map.width, data.map.height);
	mouse_init(*(data.win), &data.mouse_state);
	mlx_loop_hook(data.win->mlx, render_win, &data);
	mlx_hook(data.win->mlx_win, KEY_PRESS, KEY_PRESS_MASK,
		key_press_hook, &data);
	mlx_hook(data.win->mlx_win, KEY_RELEASE, KEY_RELEASE_MASK,
		key_release_hook, &data);
	mlx_mouse_hook(data.win->mlx_win, mouse_hook, &data);
	mlx_hook(data.win->mlx_win, 17, KEY_PRESS_MASK, close_game, NULL);
	mlx_loop(data.win->mlx);
	return (0);
}

static int	game_init_data(int argc, char **argv, t_data *data)
{
	init_data_pointers(data);
	if (!get_game_configs(argc, argv, &(data->map)))
		return (-1);
	init_alloc_mem();
	save_alloc_mem(data);
	player_init(&data->player, data->map.pos, data->map.orientation);
	data->key_state = key_init();
	data->mouse.actual = (t_pos){WIN_WIDTH / 2, WIN_HEIGHT / 2};
	data->mouse.last = (t_pos){0, 0};
	data->win = oom_guard(ft_calloc(1, sizeof(t_win)));
	return (0);
}

static void	game_win_init(t_win *win)
{
	win->mlx = mlx_init();
	win->mlx_win = mlx_new_window(win->mlx, WIN_WIDTH, WIN_HEIGHT, "Cube3D");
	win->frame.mlx_img = mlx_new_image(win->mlx, WIN_WIDTH, WIN_HEIGHT);
	win->frame.addr = mlx_get_data_addr(win->frame.mlx_img, &(win->frame.bpp),
			&(win->frame.line_len), &(win->frame.endian));
}

static int	render_win(void *data_src)
{
	t_data	*data;

	data = (t_data *)data_src;
	raycast_all(data->player, data->map.content);
	if (data->mouse_state == MOUSE_HIDE)
	{
		mouse_update(&data->mouse, mouse_get_pos(*data->win));
		player_rot_mouse(data->player, data->mouse);
		mouse_recenter(*data->win, &data->mouse);
	}
	mouse_state_control(*data->win, &data->mouse_state);
	key_move_control(data->key_state, data->player, data->map.content);
	mlx_clear_window(data->win->mlx, data->win->mlx_win);
	doors_control(data->map);
	//render_scene_3d_tex(data->win->frame, *data->player, data->tex);

	render_scene_2d(data->win->frame, *data->player, data->map.content);

	//minimap_render(data->win->frame, data->map.content, *data->player, data->minimap);
	mlx_put_image_to_window(data->win->mlx, data->win->mlx_win,
		data->win->frame.mlx_img, 0, 0);
	frame_count(data->win);
	return (0);
}

int	close_game(void)
{
	free_alloc_mem();
	return (0);
}
