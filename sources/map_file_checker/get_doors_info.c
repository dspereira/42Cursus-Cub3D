/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_doors_info.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcandeia <dcandeia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 11:05:04 by dcandeia          #+#    #+#             */
/*   Updated: 2023/03/02 13:31:55 by dcandeia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int	get_nbr_doors(char **map);
static int	init_doors(t_pos **doors, char **map);

int	get_doors_info(char **map, t_pos **doors)
{
	int	x;
	int	y;
	int	i;

	y = 0;
	i = 0;
	if (init_doors(doors, map) == -1)
		return (-1);
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'G')
			{
				(*doors)[i].x = x;
				(*doors)[i].y = y;
				i++;
			}
			x++;
		}
		y++;
	}
	return (TRUE);
}

static int	init_doors(t_pos **doors, char **map)
{
	int	nbr_doors;

	nbr_doors = get_nbr_doors(map);
	if (nbr_doors >= 1)
	{
		*doors = ft_calloc(nbr_doors + 1, sizeof(t_pos));
		if (!*doors)
			return (-1);
		(*doors)[nbr_doors].x = -1;
		(*doors)[nbr_doors].y = -1;
	}
	else
	{
		*doors = NULL;
		return (FALSE);
	}
	return (TRUE);
}

static int	get_nbr_doors(char **map)
{
	int	i;
	int	j;
	int	counter;

	counter = 0;
	if (!map)
		return (0);
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'G')
				counter++;
			j++;
		}
		i++;
	}
	return (counter);
}
