/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 17:26:05 by dsilveri          #+#    #+#             */
/*   Updated: 2023/03/09 13:06:40 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

t_pos	get_new_pos(t_pos init, double scale_x, double scale_y, int dist)
{
	t_pos	pos;

	pos.x = dist * scale_x + init.x;
	pos.y = dist * scale_y + init.y;
	return (pos);
}

t_pos	get_new_dist_pos(t_pos init, float dir, int dist)
{
	t_pos	pos;

	pos.x = round(dist * cos_degree(dir) + init.x);
	pos.y = round(-dist * sin_degree(dir) + init.y);
	return (pos);
}

t_pos	get_new_dist_pos1(t_pos init, float dir, int dist)
{
	t_pos	pos;

	pos.x = round(dist * cos_degree(dir) + init.x);
	pos.y = round(-dist * sin_degree(dir) + init.y);
	return (pos);
}

t_pos_dec	get_new_dist_pos_dec(t_pos_dec init, float dir, double dist)
{
	t_pos_dec	pos;

	pos.x = dist * cos_degree(dir) + init.x;
	pos.y = -dist * sin_degree(dir) + init.y;
	return (pos);
}

t_pos	get_win_pos(t_pos pos)
{
	t_pos	win_pos;

	win_pos.x = pos.x * MAP_SQUARE_SIZE;
	win_pos.y = pos.y * MAP_SQUARE_SIZE;
	return (win_pos);
}
