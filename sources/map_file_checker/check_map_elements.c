/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_elements.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcandeia < dcandeia@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 16:18:39 by dcandeia          #+#    #+#             */
/*   Updated: 2023/02/24 15:05:48 by dcandeia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int	check_empty_map(const char **map);
static int	check_nbr_player_start_pos(const char **map);
static int	check_one_line_map(char *line);
static int	check_doors(const char **map);

int	check_map_elements(char **map)
{
	int	i;

	i = 0;
	if (!check_empty_map((const char **)map))
	{
		print_error_msg("The Map is Empty");
		return (FALSE);
	}
	while (map[i])
	{
		if (!check_one_line_map(map[i]))
			return (FALSE);
		i++;
	}
	if (!check_nbr_player_start_pos((const char **)map))
		return (FALSE);
	if (!check_doors((const char **)map))
	{
		print_error_msg("Incorrect doors position");
		return (FALSE);
	}
	return (TRUE);
}

static int	check_one_line_map(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '0' || line[i] == '1')
			i++;
		else if (line[i] == 'N' || line[i] == 'S'
			|| line[i] == 'E' || line[i] == 'W')
			i++;
		else if (line[i] == ' ' || line[i] == 'A' || line[i] == 'B' \
				|| line[i] == 'C' || line[i] == 'D' || line[i] == 'G')
			i++;
			
		else
		{
			print_error_msg("Invalid elements in the Map");
			return (FALSE);
		}
	}
	return (TRUE);
}

static int	check_nbr_player_start_pos(const char **map)
{
	int	i;
	int	j;
	int	nbr_player_start_pos;

	nbr_player_start_pos = 0;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S'
				|| map[i][j] == 'W' || map[i][j] == 'E')
				nbr_player_start_pos += 1;
			j++;
		}
		i++;
	}
	if (nbr_player_start_pos != 1)
	{
		print_error_msg("The game is only Single Player Mode");
		return (FALSE);
	}
	return (TRUE);
}

static int	check_empty_map(const char **map)
{
	int	i;
	int	j;
	int	nbr_map_elem;

	nbr_map_elem = 0;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S'
				|| map[i][j] == 'W' || map[i][j] == 'E'
				|| map[i][j] == '0' || map[i][j] == '1')
				nbr_map_elem += 1;
			j++;
		}
		i++;
	}
	if (nbr_map_elem < 1)
		return (FALSE);
	return (TRUE);
}

static int	check_doors(const char **map)
{
	int	x;
	int	y;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'G')
			{
				if (map[y + 1][x] == 'G' || map[y - 1][x] == 'G' \
					|| map[y][x + 1] == 'G' || map[y][x - 1] == 'G')
					return (FALSE);
				else if (!((map[y][x + 1] == 'C' && map[y][x - 1] == 'D')
					|| (map[y + 1][x] == 'B' && map[y - 1][x] == 'A')))
					return (FALSE);
			}
			x++;
		}
		y++;
	}
	return (TRUE);
}
