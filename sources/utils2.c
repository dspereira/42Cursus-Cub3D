/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 13:05:29 by dsilveri          #+#    #+#             */
/*   Updated: 2023/03/09 13:07:11 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

t_pos	get_map_pos(t_pos pos)
{
	pos.x = pos.x / MAP_SQUARE_SIZE;
	pos.y = pos.y / MAP_SQUARE_SIZE;
	return (pos);
}

t_pos	get_map_pos_1(t_pos_dec pos)
{
	t_pos	map_pos;

	map_pos.x = pos.x / MAP_SQUARE_SIZE;
	map_pos.y = pos.y / MAP_SQUARE_SIZE;
	return (map_pos);
}

t_pos_dec	get_map_pos_decimal(t_pos pos)
{
	t_pos_dec	map_pos;

	map_pos.x = (double)pos.x / MAP_SQUARE_SIZE;
	map_pos.y = (double)pos.y / MAP_SQUARE_SIZE;
	return (map_pos);
}

t_pos_dec	get_map_pos_decimal_1(t_pos_dec pos)
{
	t_pos_dec	map_pos;

	map_pos.x = pos.x / MAP_SQUARE_SIZE;
	map_pos.y = pos.y / MAP_SQUARE_SIZE;
	return (map_pos);
}
