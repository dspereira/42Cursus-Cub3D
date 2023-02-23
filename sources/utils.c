/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 17:26:05 by dsilveri          #+#    #+#             */
/*   Updated: 2023/02/23 16:12:16 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

// mudar esta função: scale_x e scale_y não se percebe que são cos e sin
// usado em 2D
t_pos get_new_pos(t_pos init, double scale_x, double scale_y, int dist)
{
	t_pos	pos;

	pos.x = dist * scale_x + init.x;
	pos.y = dist * scale_y + init.y;
	return (pos);
}

t_pos get_new_dist_pos(t_pos init, float dir, int dist)
{
	t_pos	pos;

	pos.x = round(dist * cos_degree(dir) + init.x);
	pos.y = round(-dist * sin_degree(dir) + init.y);
	return (pos);
}


t_pos get_new_dist_pos1(t_pos init, float dir, int dist)
{
	t_pos	pos;

    pos.x = round(dist * cos_degree(dir) + init.x);
    pos.y = round(-dist * sin_degree(dir) + init.y);

    //printf("X: %i  Y: %i\n", pos.x, pos.y);

	return (pos);
}

t_pos_dec get_new_dist_pos_dec(t_pos_dec init, float dir, double dist)
{
	t_pos_dec   pos;

	pos.x = dist * cos_degree(dir) + init.x;
	pos.y = -dist * sin_degree(dir) + init.y;
	return (pos);
}

t_pos get_map_pos(t_pos pos)
{
    pos.x = pos.x / MAP_SQUARE_SIZE;
    pos.y = pos.y / MAP_SQUARE_SIZE;
    return (pos);
}

t_pos_dec get_map_pos_decimal(t_pos pos)
{
    t_pos_dec map_pos;

    map_pos.x = (double)pos.x / MAP_SQUARE_SIZE;
    map_pos.y = (double)pos.y / MAP_SQUARE_SIZE;
    return (map_pos);
}

t_pos_dec get_map_pos_decimal_1(t_pos_dec pos)
{
    t_pos_dec map_pos;

    map_pos.x = (double)pos.x / MAP_SQUARE_SIZE;
    map_pos.y = (double)pos.y / MAP_SQUARE_SIZE;
    return (map_pos);
}

t_pos get_win_pos(t_pos pos)
{
    t_pos   win_pos;

    win_pos.x = pos.x * MAP_SQUARE_SIZE;
    win_pos.y = pos.y * MAP_SQUARE_SIZE;
    return (win_pos);
}
