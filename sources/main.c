/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 12:14:20 by dsilveri          #+#    #+#             */
/*   Updated: 2023/01/23 17:20:33 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	key(int keycode, t_player *player);
int render_win(void *data);

int main(void) 
{
	t_win		win;
	t_pos		pos1;
	t_pos		pos2;
	int			red;
	int 		size;
	t_player	*player;

	char map[24][24] = {
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

	t_data *data;


	player = init_player((t_pos){60, 120}, 45);
	ray_cast(player, map);

	//data->map = map;
	//data->player = player;

	//printf("player: %i, %i, %f\n", player->pos.x, player->pos.y, player->dir);
	win.mlx = mlx_init();
	win.mlx_win = mlx_new_window(win.mlx, WIN_WIDTH, WIN_HEIGHT, "Cube3D");
	//mlx_draw_stroke_square(win, pos1, size, red);
	//mlx_draw_fill_square(win, pos2, size, red);
	render_scene_2d(win, *player, map);
	mlx_key_hook(win.mlx_win, key, player);
	mlx_loop_hook(win.mlx, render_win, (void*)data);
	mlx_loop(win.mlx);
	return (0);
}

int render_win(void *data)
{
	//t_player *player;

	//player = ((t_data*)data)->player;

	printf("teste\n");
	
}

void update_vision(t_player *player, int key)
{
	int		n_rays;
	int 	i;
	int 	rot_val;
	t_ray	*rays;

	rays = player->rays;
	if (key == KEY_ARROW_L)
		rot_val = ROT_STEP;
	else
		rot_val = -ROT_STEP;
	player->dir = normalizeAngles(player->dir + rot_val);
	n_rays = CAMERA_ANGLE / DIST_BTW_ANGLE;
	i = -1;
	while (++i < n_rays)
		rays[i].dir  = normalizeAngles(rays[i].dir + rot_val);
}

int	key(int keycode, t_player *player)
{
	
	printf("player: %f\n", player->dir);
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