/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 10:50:03 by dsilveri          #+#    #+#             */
/*   Updated: 2023/01/24 10:43:32 by dsilveri         ###   ########.fr       */
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

	if (math_abs(end.x - init.x) >= math_abs(end.y - init.y))
		steps = math_abs(end.x - init.x);
	else 
		steps = math_abs(end.y - init.y);
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

void mlx_draw_stroke_square(t_win win, t_pos init, int size, int color)
{
	t_pos	new_init;
	t_pos	end;

	size -= 1;
	end.y = init.y;
	end.x = init.x + size; 
	mlx_draw_line(win, init, end, color);
	new_init = end;
	end.x = new_init.x;
	end.y = new_init.y + size;
	mlx_draw_line(win, new_init, end, color);
	end.y = init.y + size;
	end.x = init.x;
	mlx_draw_line(win, init, end, color);
	new_init = end;
	end.x = new_init.x + size;
	end.y = new_init.y;	
	mlx_draw_line(win, new_init, end, color);
}

void mlx_draw_fill_square(t_win win, t_pos init, int size, int color)
{
	t_pos	end;
	int		i;
	end = init;
	end.x += size;
	i = 0;
	while (i < size)
	{
		mlx_draw_line(win, init, end, color);
		init.y++;
		end.y++;
		i++;
	}
}
