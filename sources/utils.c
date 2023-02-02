/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 17:26:05 by dsilveri          #+#    #+#             */
/*   Updated: 2023/01/27 14:23:56 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"


// mudar esta função: scale_x e scale_y não se percebe que são cos e sin
t_pos get_new_pos(t_pos init, double scale_x, double scale_y, int dist)
{
	t_pos	pos;

	pos.x = dist * scale_x + init.x;
	pos.y = dist * scale_y + init.y;
	return (pos);
}

t_pos get_new_pos1(t_pos init, float dir, int dist)
{
	t_pos	pos;

	pos.x = dist * cos_degree(dir) + init.x;
	pos.y = -dist * sin_degree(dir) + init.y;
	return (pos);
}

t_pos get_map_pos(t_pos pos)
{
    int square_size;

    square_size = WIN_HEIGHT / MAP_HEIGHT;
    pos.x = pos.x / square_size;
    pos.y = pos.y / square_size;
    return (pos);
}

t_pos_dec get_map_pos_decimal(t_pos pos)
{
    t_pos_dec map_pos;
    int square_size;

    square_size = WIN_HEIGHT / MAP_HEIGHT;
    map_pos.x = (double)pos.x / square_size;
    map_pos.y = (double)pos.y / square_size;
    return (map_pos);
}

t_pos get_win_pos(t_pos pos)
{
    t_pos   win_pos;
    int     square_size;

    square_size = WIN_HEIGHT / MAP_HEIGHT;
    win_pos.x = pos.x * square_size;
    win_pos.y = pos.y * square_size;
    return (win_pos);
}

int	hex_to_int(const char *str)
{
	int	n;
	int	i;
	int	num;

	if (!str || (16 < 2 || 16 > 16))
		return (0);
	i = 0;
	num = 0;
	while (str[i])
	{
		n = str[i];
		if (n >= '0' && n <= '9')
			n -= '0';
		else if (n >= 'a' && n <= 'f')
			n -= 'a' - 10;
		else if (n >= 'A' && n <= 'F')
			n -= 'A' - 10;
		else
			return (0);
		num = num * 16 + n;
		++i;
	}
	return (num);
}