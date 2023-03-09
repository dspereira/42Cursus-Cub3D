/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_walls.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 11:39:13 by dcandeia          #+#    #+#             */
/*   Updated: 2023/03/09 13:03:04 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static int	check_top_bot_lines(char **map);
static int	check_left_right_borders(char **map);
static int	check_mid_lines(char **map);
static int	check_nearby_pos(char **map, int x, int y);
int			is_wall(char c);

int	check_map_walls(char **map)
{
	int	ret;

	ret = TRUE;
	if (!check_top_bot_lines(map) || !check_left_right_borders(map))
		ret = FALSE;
	if (!check_mid_lines(map))
		ret = FALSE;
	if (ret == FALSE)
		print_error_msg("The map is not surrounded by Walls");
	return (ret);
}

static int	check_top_bot_lines(char **map)
{
	int	i;
	int	j;

	j = 0;
	while (map[0][j])
	{
		if (is_wall(map[1][j]))
			j++;
		else
			return (FALSE);
	}
	i = 0;
	while (map[i + 1])
		i++;
	j = 0;
	while (map[i][j])
	{
		if (is_wall(map[i - 1][j]))
			j++;
		else
			return (FALSE);
	}
	return (TRUE);
}

static int	check_left_right_borders(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		if (is_wall(map[i][1]))
			i++;
		else
			return (FALSE);
	}
	j = 0;
	while (map[0][j])
		j++;
	i = 0;
	while (map[i])
	{
		if (is_wall(map[i][j - 2]))
			i++;
		else
			return (FALSE);
	}
	return (TRUE);
}

static int	check_mid_lines(char **map)
{
	int	i;
	int	j;

	i = 1;
	while (map[i + 1])
	{
		j = 1;
		while (map[i + 1][j + 1])
		{
			if (map[i][j] == ' ')
			{
				if (!check_nearby_pos(map, j, i))
					return (FALSE);
			}
			j++;
		}
		i++;
	}
	return (TRUE);
}

static int	check_nearby_pos(char **map, int x, int y)
{
	if (!is_wall(map[y][x + 1]))
		return (FALSE);
	if (!is_wall(map[y][x - 1]))
		return (FALSE);
	if (!is_wall(map[y + 1][x]))
		return (FALSE);
	if (!is_wall(map[y - 1][x]))
		return (FALSE);
	return (TRUE);
}
