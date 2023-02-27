/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcandeia < dcandeia@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 15:05:42 by dcandeia          #+#    #+#             */
/*   Updated: 2023/02/24 15:10:22 by dcandeia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int	map_size(char **map);

int	check_map(char **map)
{
	if (!map || map_size(map) < 3)
		return (FALSE);
	if (!check_map_elements(map))
		return (FALSE);
	if (!check_map_walls(map))
		return (FALSE);
	return (TRUE);
}

static int	map_size(char **map)
{
	int	i;

	i = 0;
	while (map && map[i])
		i++;
	return (i);
}
