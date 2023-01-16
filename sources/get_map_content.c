/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_content.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcandeia <dcandeia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 11:07:59 by dcandeia          #+#    #+#             */
/*   Updated: 2023/01/16 16:01:04 by dcandeia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

// int			get_index(char **cont, int begin);
int			is_line_empty(char *line);
static void	get_map_line(char **content, char *src);
static void	realloc_map(int	actual_len, char ***content);

int	get_map_content(char ***content, int fd)
{
	char	*line;
	int		i;

	*content = ft_calloc(2, sizeof(char *));
	if (!*content)
		return (FALSE);
	line = get_next_line(fd);
	while (is_line_empty(line))
	{
		free(line);
		line = get_next_line(fd);
	}
	i = 0;
	while (line && !is_line_empty(line))
	{
		get_map_line(&((*content)[i]), line);
		/* if (!(*content)[i])
		{
			//free previos memory and return;
			return (FALSE);
		} */
		free(line);
		line = get_next_line(fd);
		realloc_map(i + 2, content);
		i++;
	}
	for (int a = 0; a < i; a++)
		printf("\'%s\'\n", (*content)[a]);
	return (TRUE);
}

/* static void	clear_map(t_map *map)
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

static int	get_map_nbr_lines(char *cont, int begin)
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
} */

static void	get_map_line(char **content, char *src)
{
	int	i;
	

	i = 0;
	*content = ft_calloc(ft_strlen(src), sizeof(char));
	if (!(*content))
		return ;
	while (src[i] != '\n' && src[i])
	{
		(*content)[i] = src[i];
		i++;
	}
}

static void	realloc_map(int	actual_len, char ***content)
{
	char	**new_content;
	int		i;

	new_content = ft_calloc(actual_len + 1, sizeof(char *));
	if (!new_content)
		return ;
	i = 0;
	while (i < actual_len)
	{
		new_content[i] = (*content)[i];
		i++;
	}
	free(*content);
	*content = new_content;
}
