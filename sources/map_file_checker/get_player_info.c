/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_player_info.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcandeia < dcandeia@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 09:13:57 by dcandeia          #+#    #+#             */
/*   Updated: 2023/02/24 16:14:27 by dcandeia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int	is_player(char c);
static int	get_player_orientation(char c);

int	get_player_info(char **map, int *orientation, t_pos *pos)
{
	int	x;
	int	y;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (is_player(map[y][x]))
			{
				*orientation = get_player_orientation(map[y][x]);
				(*pos).x = x;
				(*pos).y = y;
				map[y][x] = '0';
				return (TRUE);
			}
			x++;
		}
		y++;
	}
	return (FALSE);
}

static int	is_player(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (TRUE);
	return (FALSE);
}

static int	get_player_orientation(char c)
{
	if (c == 'N')
		return (ORIENTATION_N);
	else if (c == 'S')
		return (ORIENTATION_S);
	else if (c == 'E')
		return (ORIENTATION_E);
	else
		return (ORIENTATION_W);
}
