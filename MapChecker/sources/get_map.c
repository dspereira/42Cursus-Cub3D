/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcandeia <dcandeia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 11:07:59 by dcandeia          #+#    #+#             */
/*   Updated: 2023/01/12 15:28:43 by dcandeia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int			get_index(char **cont, int begin);
int			is_line_empty(char *line);
static int	get_map_nbr_lines(char **cont, int begin);
static char	*get_map_line(char *src);
static void	clear_map(t_map *map);

/*
Onde se obtem as tex
1. Loop para contar as linhas do mapa e sacar a maior linha
2. 

*/

t_map	*get_map(char **content, int map_begin_line)
{
	t_map	*map;
	int		i;
	int		j;

	i = get_index(content, map_begin_line);
	map = ft_calloc(1, sizeof(t_map));
	if (!map)
		return (NULL);
	map->nbr_lines = get_map_nbr_lines(content, i);
	map->content = ft_calloc(map->nbr_lines + 1, sizeof(char *));
	j = -1;
	while (++j < map->nbr_lines)
	{
		map->content[j] = get_map_line(content[i]);
		if (!map->content[j])
		{
			clear_map(map);
			return (NULL);
		}
		i++;
	}
	resize_map(map);
	return (map);
}

static void	clear_map(t_map *map)
{
	int	i;

	i = 0;
	if (!map)
		return ;
	while (map->content[i])
	{
		free(map->content[i]);
		i++;
	}
	if (map->content)
		free(map->content);
	free(map);
}

static int	get_map_nbr_lines(char **cont, int begin)
{
	int	i;
	int	map_nbr_lines;

	i = begin;
	map_nbr_lines = 0;
	while (cont[i])
	{
		map_nbr_lines += 1;
		i++;
	}
	return (map_nbr_lines);
}

static char	*get_map_line(char *src)
{
	int		i;
	int		len;
	char	*result;

	i = 0;
	len = 0;
	if (!src)
		return (NULL);
	while (src[len] && src[len] != '\n')
		len++;
	result = ft_calloc(len + 1, sizeof(char));
	if (!result)
		return (NULL);
	while (src[i] != '\n' && src[i])
	{
		result[i] = src[i];
		i++;
	}
	return (result);
}
