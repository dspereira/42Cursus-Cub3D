/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcandeia <dcandeia@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 12:35:08 by dsilveri          #+#    #+#             */
/*   Updated: 2023/03/08 14:55:02 by dcandeia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	draw_vertical_line(t_img img, t_pos init_pos, int height, int color)
{
	int	i;

	i = -1;
	while (++i < height)
	{
		if ((init_pos.x >= 0 && init_pos.x <= WIN_WIDTH)
			&& (init_pos.y >= 0 && init_pos.y <= WIN_HEIGHT))
			draw_pixel(img, init_pos.x, init_pos.y, color);
		init_pos.y++;
	}
}

void	draw_fill_rectangle(t_img img, t_pos init, t_value size, int color)
{
	int		i;

	i = 0;
	while (i < size.x)
	{
		draw_vertical_line(img, init, size.y, color);
		i++;
		init.x++;
	}
}
