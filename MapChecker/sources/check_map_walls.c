/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_walls.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcandeia <dcandeia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 11:39:13 by dcandeia          #+#    #+#             */
/*   Updated: 2023/01/09 12:20:13 by dcandeia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

static int	check_top_bot_lines(char **map);

int	check_map_walls(char **map)
{
	if (!check_top_bot_lines(map))
	{
		print_error_msg("The map is not surrounded by Walls");
		return (FALSE);
	}
	return (TRUE);
}

static int	check_top_bot_lines(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		if (i == 0 || !map[i + 1])
		{
			j = 0;
			while (map[i][j])
			{
				if ((map[i][j] >= 9 && map[i][j] <= 13) || map[i][j] == 32
					|| map[i][j] == '1')
					j++;
				else
					return (FALSE);
			}
		}
		i++;
	}
	return (TRUE);
}
