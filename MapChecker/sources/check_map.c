/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcandeia <dcandeia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 15:05:42 by dcandeia          #+#    #+#             */
/*   Updated: 2023/01/09 11:32:42 by dcandeia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

static void	print_map(char **map);

int	is_valid_map(t_map *map)
{
	if (!map || !map->content)
		return (FALSE);
	if (!check_map_elements(map->content))
		return (FALSE);
	print_map(map->content);
	if (!check_map_walls(map->content))
		return (FALSE);
	return (TRUE);
}

static void	print_map(char **map)
{
	int	i;

	i = 0;
	printf("================================================\n");
	while (map[i])
		printf("\'%s\'\n", map[i++]);
	printf("================================================\n");
}
