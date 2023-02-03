/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcandeia <dcandeia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 11:27:35 by dcandeia          #+#    #+#             */
/*   Updated: 2023/01/09 11:31:37 by dcandeia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int	find_big_line_len(char **src)
{
	int	len;
	int	i;
	int	j;

	len = 0;
	i = 0;
	while (src[i])
	{
		j = 0;
		while (src[i][j])
			j++;
		if (j > len)
			len = j;
		i++;
	}
	return (len);
}

int	is_line_empty(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '\n')
	{
		if (!((line[i] >= 9 && line[i] <= 13) || line[i] == 32))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int	get_map_size(char **map)
{
	int	i;

	i = 0;
	while (map && map[i])
		i++;
	return (i);
}
