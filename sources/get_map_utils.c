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

static int	find_big_line_len(char **src);
static char	*resize_line(char *src, int max_len);
int			is_line_empty(char *line);

void	resize_map(t_map *initital_map)
{
	int	big_len;
	int	i;

	big_len = find_big_line_len(initital_map->content);
	i = 0;
	while (initital_map->content[i])
	{
		if (ft_strlen(initital_map->content[i]) < (size_t)big_len)
			initital_map->content[i] = resize_line(initital_map->content[i],
					big_len);
		i++;
	}
}

static int	find_big_line_len(char **src)
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

static char	*resize_line(char *src, int max_len)
{
	char	*dst;
	int		i;

	if (!src)
		return (NULL);
	dst = ft_calloc(max_len + 1, sizeof(char));
	i = -1;
	if (!dst)
	{
		free(src);
		return (NULL);
	}
	while (src[++i])
		dst[i] = src[i];
	while (i < max_len)
		dst[i++] = ' ';
	free(src);
	return (dst);
}

int	get_index(char **cont, int begin)
{
	int	i;

	i = begin;
	while (cont[i] && is_line_empty(cont[i]))
		i++;
	return (i);
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
