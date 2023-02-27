/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_player_info.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcandeia <dcandeia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 09:13:57 by dcandeia          #+#    #+#             */
/*   Updated: 2023/02/27 16:13:23 by dcandeia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int		is_player(char c);
static int		get_player_orientation(char c);
static t_pos	get_player_pos(int x, int y);

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
				map[y][x] = '0';
				*pos = get_player_pos(x, y);
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

static t_pos	get_player_pos(int x, int y)
{
	t_pos	pos;

	pos = get_win_pos((t_pos){x, y});
	pos.x += MAP_SQUARE_SIZE / 2;
	pos.y += MAP_SQUARE_SIZE / 2;
	return (pos);
}
