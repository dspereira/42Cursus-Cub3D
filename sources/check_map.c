/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcandeia < dcandeia@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 15:05:42 by dcandeia          #+#    #+#             */
/*   Updated: 2023/02/24 12:13:00 by dcandeia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

static void	print_map(char **map);
int			get_map_size(char **map);

int	check_map(char **map)
{
	if (!map || get_map_size(map) < 3)
		return (FALSE);
	if (!check_map_elements(map))
		return (FALSE);
	//print_map(map);
	if (!check_map_walls(map))
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
