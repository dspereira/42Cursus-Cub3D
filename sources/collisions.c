/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collisions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 10:58:37 by dsilveri          #+#    #+#             */
/*   Updated: 2023/02/07 18:04:33 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static int check_collision_wall(t_pos p_pos, t_pos check_pos, char **map);

int check_collisions(t_pos p_pos, char **map)
{
	t_pos	m_pos;
	t_pos	check_pos;
	int 	i;
	int		j;

	t_pos	c_pos;

	m_pos = get_map_pos(p_pos);
	check_pos.x = m_pos.x - 1;
	check_pos.y = m_pos.y - 1;

	printf("player : %i %i\n", p_pos.x, p_pos.y);

	i = 0;
	while (i < 3)
	{
		j = 0;
		while (j < 3)
		{
			c_pos.y = check_pos.x + j;
			c_pos.x = check_pos.y + i;
			//printf("valor %i  %i\n", check_pos.y + i, check_pos.x + j);
			if (map[c_pos.y][c_pos.x] != '0')
				check_collision_wall(p_pos, get_win_pos(c_pos), map);
			j++;
		}
		i++;
	}
	return (0);
}

static int check_collision_wall(t_pos p_pos, t_pos check_pos, char **map)
{
	int dx;
	int dy;
	double h;

	if (p_pos.x > check_pos.x)
		check_pos.x += WIN_WIDTH / 26;
	if (p_pos.y > check_pos.y)
		check_pos.y += WIN_HEIGHT / 26;
	dx = check_pos.x - p_pos.x;
	dy = check_pos.y - p_pos.y;
	h = sqrt((dx * dx) + (dy * dy));

	printf("dx: %i dy: %i\n", dx, dy);
	printf("distancia %.5f\n", h);

	if (h < 15)
	{
		printf("distancia %.5f\n", h);
		return (1);
	}
	return (0);
}
