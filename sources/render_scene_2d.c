/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene_2d.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 16:07:04 by dsilveri          #+#    #+#             */
/*   Updated: 2023/01/18 18:01:59 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static void render_map(t_win win, char map[MAP_WIDTH][MAP_HEIGHT]);

void render_scene_2d(t_win win, char map[MAP_WIDTH][MAP_HEIGHT])
{
	render_map(win, map);
}

static void render_map(t_win win, char map[MAP_WIDTH][MAP_HEIGHT])
{
	int		square_size;
	int		i;
	int		j;
	t_pos	p;

	square_size = WIN_HEIGHT / MAP_HEIGHT;
	i = 0;
	while (i < MAP_HEIGHT) 
	{
		j = 0;
		while (j < MAP_WIDTH)
		{
			p.x = j * square_size;
			p.y = i * square_size;
			if (map[i][j])
				mlx_draw_fill_square(win, p, square_size, 0x002596BE);
			//else 
				//mlx_draw_stroke_square(win, p, square_size, 0x002596BE);
			j++;
		}
		i++;
	}
}

//static void render_player(t_win win, player, char map[MAP_WIDTH][MAP_HEIGHT])

