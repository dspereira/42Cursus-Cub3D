/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_resizer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 09:14:18 by dcandeia          #+#    #+#             */
/*   Updated: 2023/03/09 12:39:37 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int			find_big_line_len(char **src);
int			get_map_size(char **map);
void		clear_map(char ***map);
static char	*resize_line(char *src, int max_len);
static char	*fill_first_last_line(int len);
static int	fill_midle_lines(char **res, char ***src, int big_len);
static void	free_resizer_memory(char **res, char ***map, int map_len);

void	map_resizer(char ***src)
{
	char	**res;
	int		big_len;
	int		map_size;

	big_len = find_big_line_len(*src);
	map_size = get_map_size(*src);
	if (map_size < 3)
		return ;
	res = ft_calloc(map_size + 3, sizeof(char *));
	if (!res)
	{
		free_resizer_memory(res, src, map_size + 3);
		return ;
	}
	res[0] = fill_first_last_line(big_len);
	res[map_size + 1] = fill_first_last_line(big_len);
	if (!res[0] || !res[map_size + 1]
		|| !fill_midle_lines(res, src, big_len))
	{
		free_resizer_memory(res, src, map_size + 3);
		return ;
	}
	clear_map(src);
	*src = res;
}

static char	*resize_line(char *src, int max_len)
{
	char	*dst;
	int		i;
	int		a;

	i = 1;
	a = 0;
	if (!src)
		return (NULL);
	dst = ft_calloc(max_len + 3, sizeof(char));
	if (!dst)
		return (NULL);
	dst[0] = ' ';
	while (src[a])
		dst[i++] = src[a++];
	while (i < max_len + 2)
		dst[i++] = ' ';
	return (dst);
}

static char	*fill_first_last_line(int len)
{
	char	*res;
	int		i;

	res = ft_calloc(len + 3, sizeof(char));
	if (!res)
		return (NULL);
	i = 0;
	while (i < len + 2)
		res[i++] = ' ';
	return (res);
}

static void	free_resizer_memory(char **res, char ***map, int map_len)
{
	int	i;

	i = 0;
	if (res)
	{
		while (i < map_len)
		{
			if (res[i])
				free(res[i]);
			i++;
		}
		free(res);
	}
	i = 0;
	if (*map)
	{
		while ((*map)[i])
			free((*map)[i++]);
		free(*map);
		*map = NULL;
	}
}

static int	fill_midle_lines(char **res, char ***src, int big_len)
{
	int	i;
	int	a;

	i = 1;
	a = 0;
	while (a < get_map_size(*src))
	{
		res[i] = resize_line((*src)[a], big_len);
		if (!res[i])
			return (0);
		i++;
		a++;
	}
	return (1);
}
