/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 12:14:20 by dsilveri          #+#    #+#             */
/*   Updated: 2023/01/17 16:01:47 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"


int main(void) 
{
	t_win	win;
	t_pos	pos1;
	t_pos	pos2;
	int		red;
	int 	size;

	red = 0x00FF0000;
	
	size = 150;
	pos1.x = 50;
	pos1.y = 50;

	pos2.x = pos1.x + size + 5;
	pos2.y = 50;

	win.mlx = mlx_init();
	win.mlx_win = mlx_new_window(win.mlx, 640, 360, "Cube3D");
	mlx_draw_stroke_square(win, pos1, size, red);
	mlx_draw_fill_square(win, pos2, size, red);
	mlx_loop(win.mlx);
	return (0);
}