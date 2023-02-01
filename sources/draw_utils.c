/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 16:07:38 by dsilveri          #+#    #+#             */
/*   Updated: 2023/01/29 15:30:50 by dsilveri         ###   ########.fr       */
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
	int			steps;
	t_value		delta;
	t_value_dec	inc;
	t_pos_dec	pos;

	delta.x = end.x - init.x;
	delta.y = end.y - init.y;
	if (math_abs(delta.x) >= math_abs(delta.y))
		steps = math_abs(delta.x);
	else 
		steps = math_abs(delta.y);
	inc.x = (double)delta.x / steps;
	inc.y = (double)delta.y / steps;
	pos.x = init.x;
	pos.y = init.y;
	while (steps-- > 0)
	{
		draw_pixel(img, pos.x, pos.y, color);
		pos.x += inc.x;
		pos.y += inc.y;
	}
	draw_pixel(img, end.x, end.y, color);
}

void draw_vertical_line(t_img img, t_pos init_pos, int height, int color)
{
	int i;

	i = -1;
	while (++i < height)
		draw_pixel(img, init_pos.x, init_pos.y++, color);
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

void draw_fill_rectangle(t_img img, t_pos init, t_value size, int color)
{
	t_pos	end;
	int		i;

	i = 0;
	while (i < size.x)
	{
		draw_vertical_line(img, init, size.y, color);
		i++;
		init.x++;
	}
}
