/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 16:07:38 by dsilveri          #+#    #+#             */
/*   Updated: 2023/03/08 13:08:56 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

unsigned int	get_tex_color(t_img tex, t_pos pos);

void	draw_pixel(t_img img, int x, int y, int color)
{
	int	*pixel;

	if (x >= WIN_WIDTH || y >= WIN_HEIGHT || x < 0 || y < 0)
		return ;
	pixel = (int *)(img.addr + (img.line_len * y) + (x * img.bpp / 8));
	*pixel = color;
}

void	draw_line(t_img img, t_pos init, t_pos end, int color)
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

void	draw_line_tex(t_img frame, t_tex_data wall)
{
	int					i;
	double				xperce;
	t_pos				spot;
	unsigned int		color;

	i = 0;
	xperce = (wall.map_wall_pos - (int)wall.map_wall_pos) * wall.tex.width;
	while (i < wall.height)
	{
		spot.x = xperce;
		spot.y = ((double)i / wall.height) * wall.tex.height;
		color = get_tex_color(wall.tex, spot);
		draw_pixel(frame, wall.win_start_pos.x, wall.win_start_pos.y + i, \
			color);
		i++;
	}
}

void	draw_door_tex(t_img frame, t_tex_data wall)
{
	int					i;
	double				xperce;
	t_pos				spot;
	unsigned int		color;

	i = 0;
	xperce = (wall.map_wall_pos - (int)wall.map_wall_pos) * wall.tex.width;
	while (i < wall.height)
	{
		spot.x = xperce;
		spot.y = ((double)i / wall.height) * wall.tex.height;
		color = get_tex_color(wall.tex, spot);
		if (color != NONE_COLOR_VALUE)
			draw_pixel(frame, wall.win_start_pos.x, wall.win_start_pos.y + i, \
				color);
		i++;
	}
}

unsigned int	get_tex_color(t_img tex, t_pos pos)
{
	unsigned int	*color;

	color = (unsigned int *)(tex.addr + (tex.line_len * pos.y) \
		+ (pos.x * tex.bpp / 8));
	return (*color);
}
