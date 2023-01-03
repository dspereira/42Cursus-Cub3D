/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_elements.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcandeia <dcandeia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 16:18:39 by dcandeia          #+#    #+#             */
/*   Updated: 2023/01/03 16:31:08 by dcandeia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

static int	check_one_line_map(char *line);

int	check_map_elements(char **map)
{
	int	i;
	
	i = 0;
	while (map[i])
	{
		if (!check_one_line_map(map[i]))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

static int	check_one_line_map(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\n')
	{
		if (line[i] == '0' || line[i] == '1')
			i++;
		else if (line[i] == 'N' || line[i] == 'S'
			|| line[i] == 'E' || line[i] == 'W')
			i++;
		else if (line[i] == ' ')
			i++;
		else
			return (FALSE);
	}
	return (TRUE);
}
