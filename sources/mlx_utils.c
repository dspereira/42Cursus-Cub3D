/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 10:50:03 by dsilveri          #+#    #+#             */
/*   Updated: 2023/01/17 13:08:00 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void mlx_draw_line(t_win win, t_pos init, t_pos end, int color)
{
	int		steps;
	double	x_inc;
	double	y_inc;
	double	x;
	double	y;

	if (abs(end.x - init.x) >= abs(end.y - init.y))
		steps = abs(end.x - init.x);
	else 
		steps = abs(end.y - init.y);
	x_inc = (double)(end.x - init.x) / steps;
	y_inc = (double)(end.y - init.y) / steps;
	x = init.x;
	y = init.y;
	while (steps-- > 0)
	{
		mlx_pixel_put(win.mlx, win.mlx_win, x, y, color);
		x += x_inc;
		y += y_inc;
	}
	mlx_pixel_put(win.mlx, win.mlx_win, end.x, end.y, color);
}