/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils_2d.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 12:30:46 by dsilveri          #+#    #+#             */
/*   Updated: 2023/03/08 12:34:47 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	draw_stroke_square(t_img img, t_pos init, int size, int color)
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

void	draw_fill_square(t_img img, t_pos init, int size, int color)
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
