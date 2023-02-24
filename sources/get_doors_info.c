/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_doors_info.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcandeia < dcandeia@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 11:05:04 by dcandeia          #+#    #+#             */
/*   Updated: 2023/02/24 11:24:38 by dcandeia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int	get_nbr_doors(char **map);
static void	set_door_info(t_door *door, int x, int y);
static int	init_doors(t_door **doors, char **map);

int	get_doors_info(char **map, t_door **doors)
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
			if (map[y][x] == 'D')
			{
				set_door_info(&(*doors)[i], x, y);
				i++;
			}
			x++;
		}
		y++;
	}
	return (TRUE);
}

static int	init_doors(t_door **doors, char **map)
{
	int	nbr_doors;

	nbr_doors = get_nbr_doors(map);
	if (nbr_doors >= 1)
	{
		*doors = ft_calloc(nbr_doors + 1, sizeof(t_door));
		if (!*doors)
			return (-1);
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
			if (map[i][j] == 'D')
				counter++;
			j++;
		}
		i++;
	}
	return (counter);
}

static void	set_door_info(t_door *door, int x, int y)
{
	(*door).pos.x = x;
	(*door).pos.y = y;
}
