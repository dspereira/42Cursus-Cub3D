/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcandeia <dcandeia@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 12:07:31 by dsilveri          #+#    #+#             */
/*   Updated: 2023/03/08 14:50:16 by dcandeia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	is_floor(char **map, t_pos pos)
{
	if (map[pos.y][pos.x] == FLOOR)
		return (TRUE);
	else
		return (FALSE);
}

int	is_door(char **map, t_pos pos)
{
	char	c;

	c = map[pos.y][pos.x];
	if ((c >= DOOR_OPENING_START && c <= DOOR_OPENING_END)
		|| (c >= DOOR_CLOSING_START && c <= DOOR_CLOSING_END))
		return (TRUE);
	else
		return (FALSE);
}
