/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 15:05:42 by dcandeia          #+#    #+#             */
/*   Updated: 2023/01/04 11:49:03 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

static void	print_map(char **map);
static void	free_map(char **map);

int	is_valid_map(char *map_file)
{
	char	**map;

	map = get_map(map_file);
	if (!map)
		return (FALSE);
	if (!check_map_elements(map))
	{
		free_map(map);
		return (FALSE);
	}
	print_map(map);
	free_map(map);
	return (TRUE);
}

static void	print_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		printf("%s", map[i]);
		i++;
	}
}

static void	free_map(char **map)
{
	int	i;

	i = 0;
	if (!map)
		return ;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}
