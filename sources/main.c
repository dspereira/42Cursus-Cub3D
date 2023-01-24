/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 12:14:20 by dsilveri          #+#    #+#             */
/*   Updated: 2023/01/24 13:01:14 by dsilveri         ###   ########.fr       */
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

	player = init_player((t_pos){60, 120}, 45);
	//ray_cast(player, map);


	win.mlx = mlx_init();
	win.mlx_win = mlx_new_window(win.mlx, WIN_WIDTH, WIN_HEIGHT, "Cube3D");

	data.win = win;
	data.player = player;
	data.map = map;

	//render_scene_2d(win, *player, map);
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
	win = ((t_data*)data)->win;

	ray_cast(player, map.content);
	render_scene_2d(win, *player, map.content);
}



int	key(int keycode, t_player *player)
{
	
	//printf("player: %f\n", player->dir);
	if (keycode == KEY_W || keycode == KEY_A
		|| keycode == KEY_S || keycode == KEY_D)
	{
		printf("KEY - ");
		switch (keycode)
		{
			case KEY_W:
				printf("W\n");
				break;
			case KEY_A:
				printf("A\n");
				break;
			case KEY_S:
				printf("S\n");
				break;
			case KEY_D:
				printf("D\n");
				break;
			default:
				break;
		}
	}

	else if (keycode == KEY_ARROW_R || keycode == KEY_ARROW_L)
		update_vision(player, keycode);

	/*
	else if (keycode == KEY_ARROW_R || keycode == KEY_ARROW_L)
	{
		printf("KEY - ");
		switch (keycode)
		{
			case KEY_ARROW_R:
				update_vision(player->rays, 1);
				break;
			case KEY_ARROW_L:
				update_vision(player->rays, -1);
				break;
			default:
				break;
		}
	}
	*/
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