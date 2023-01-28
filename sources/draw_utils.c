/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 16:07:38 by dsilveri          #+#    #+#             */
/*   Updated: 2023/01/28 16:18:37 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void draw_pixel(t_img img, int x, int y, int color)
{
	int *pixel;

	if (x > WIN_WIDTH || y > WIN_HEIGHT)
		return ;
	pixel = (int *)(img.addr + (img.line_len * y) + (x * img.bpp / 8));
	*pixel = color;
}

void draw_line(t_img img, t_pos init, t_pos end, int color)
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
		draw_pixel(img, x, y, color);
		x += x_inc;
		y += y_inc;
	}
	draw_pixel(img, end.x, end.y, color);
}

void draw_stroke_square(t_img img, t_pos init, int size, int color)
{
	t_pos	new_init;
	t_pos	end;

	size -= 1;
	end.y = init.y;
	end.x = init.x + size; 
	draw_line(img, init, end, color);
	new_init = end;
	end.x = new_init.x;
	end.y = new_init.y + size;
	draw_line(img, new_init, end, color);
	end.y = init.y + size;
	end.x = init.x;
	draw_line(img, init, end, color);
	new_init = end;
	end.x = new_init.x + size;
	end.y = new_init.y;	
	draw_line(img, new_init, end, color);
}

void draw_fill_square(t_img img, t_pos init, int size, int color)
{
	t_pos	end;
	int		i;
	end = init;
	end.x += size;
	i = 0;
	while (i < size)
	{
		draw_line(img, init, end, color);
		init.y++;
		end.y++;
		i++;
	}
}
