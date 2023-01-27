/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 12:14:20 by dsilveri          #+#    #+#             */
/*   Updated: 2023/01/27 17:05:19 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	key(int keycode, t_player *player);
int render_win(void *data);

// Just for debug
char **fill_map_debug(char map[MAP_WIDTH][MAP_HEIGHT]);

int main(void) 
{
	t_win		win;
	t_pos		pos1;
	t_pos		pos2;
	int			red;
	int 		size;
	t_player	*player;
	t_map		map;
	t_data		data;

	char map1[24][24] = {
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
		{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
		{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	};

	map.content = fill_map_debug(map1);
	if (map.content == NULL)
		return (0);

	player = player_init((t_pos){80, 120}, 0);
	//ray_cast(player, map);


	win.mlx = mlx_init();
	win.mlx_win = mlx_new_window(win.mlx, WIN_WIDTH, WIN_HEIGHT, "Cube3D");

	win.frame.mlx_img = mlx_new_image(win.mlx, WIN_WIDTH, WIN_HEIGHT);
	win.frame.addr = mlx_get_data_addr(win.frame.mlx_img, &(win.frame.bpp), &(win.frame.line_len), &(win.frame.endian));

	data.win = &win;
	data.player = player;
	data.map = map;

	mlx_loop_hook(win.mlx, render_win, &data);
	mlx_key_hook(win.mlx_win, key, player);
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

	ray_cast(player, map.content);
	//win.frame.mlx_img = mlx_new_image(win.mlx, WIN_WIDTH, WIN_HEIGHT);
	//win.frame.addr = mlx_get_data_addr(win.frame.mlx_img, &(win.frame.bpp), &(win.frame.line_len), &(win.frame.endian));
	//printf("--------> %c\n", *(win->frame.addr));
	render_scene_2d(&win, *player, map.content);
	//printf("--------> %c\n", (win.frame.addr)[0]);
	mlx_put_image_to_window(win.mlx, win.mlx_win, win.frame.mlx_img, 0, 0);
}

int	key(int keycode, t_player *player)
{
	if (keycode == KEY_W)
		player_move(player, FORWARD);
	else if (keycode == KEY_S)
		player_move(player, BACKWARD);
	else if (keycode == KEY_A)
		player_move(player, LEFT);
	else if (keycode == KEY_D)
		player_move(player, RIGHT);
	else if (keycode == KEY_ARROW_R)
		player_update_vision(player, -ROT_STEP);
	else if (keycode == KEY_ARROW_L)
		player_update_vision(player, ROT_STEP);
	return (0);
}

char **fill_map_debug(char map[MAP_WIDTH][MAP_HEIGHT])
{
	char	**m;
	int		i;
	int		j;

	m = malloc(sizeof(char *) * MAP_HEIGHT);
	if (!map)
		return (NULL);
	i = 0;
	while (i < MAP_HEIGHT)
	{
		m[i] = malloc(sizeof(char) * MAP_WIDTH);
		if (!m[i])
			return (NULL);
		i++; 
	}
	i = 0;
	j = 0;
	while (i < MAP_HEIGHT)
	{
		j = 0;
		while (j < MAP_WIDTH)
		{
			m[i][j] = map[i][j];
			j++;
		}
		i++;
	}
	/*i = 0;
	j = 0;
	while (i < MAP_HEIGHT)
	{
		j = 0;
		while (j < MAP_WIDTH)
		{
			printf("%i ",m[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}*/

	return (m);
}