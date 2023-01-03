/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcandeia <dcandeia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 15:11:35 by dcandeia          #+#    #+#             */
/*   Updated: 2023/01/03 16:28:31 by dcandeia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

static int	get_map_nbr_lines(char *map_file);

char	**get_map(char *file)
{
	char	**map;
	int		index;
	int		map_nbr_lines;
	int		fd;

	map_nbr_lines = get_map_nbr_lines(file);
	if (map_nbr_lines < 1)
		return (NULL);
	map = malloc(sizeof(char *) * (map_nbr_lines + 1));
	index = 0;
	fd = open(file, O_RDONLY);
	if (!fd)
		return (NULL);
	while (index < map_nbr_lines)
	{
		map[index] = get_next_line(fd);
		index++;
	}
	map[index] = NULL;
	return (map);
}

static int	get_map_nbr_lines(char *map_file)
{
	char	*str;
	int		nbr_lines;
	int		fd;

	nbr_lines = 0;
	fd = open(map_file, O_RDONLY);
	if (!fd)
		return (0);
	str = get_next_line(fd);
	while (str)
	{
		free(str);
		str = get_next_line(fd);
		nbr_lines += 1;
	}
	close(fd);
	return (nbr_lines);
}
