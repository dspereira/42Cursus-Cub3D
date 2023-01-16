/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_textures.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcandeia <dcandeia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 11:23:32 by dcandeia          #+#    #+#             */
/*   Updated: 2023/01/16 11:49:13 by dcandeia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int					get_rgb(char *src, int *tex_count, int act_colour);
static int			is_line_empty(char *line);
static void			get_path(char *src, int *tex_c, char *actpath);

int	get_map_textures(t_map *map, int fd)
{
	char	*line;
	int		tex_count;

	tex_count = 0;
	line = get_next_line(fd);
	while (tex_count < 6 && line)
	{
		if (!ft_strncmp(line, "NO", 2))
			get_path(line, &tex_count, map->wall_textures[TEX_NO]);
		else if (!ft_strncmp(line, "SO", 2))
			get_path(line, &tex_count, map->wall_textures[TEX_SO]);
		else if (!ft_strncmp(line, "WE", 2))
			get_path(line, &tex_count, map->wall_textures[TEX_WE]);
		else if (!ft_strncmp(line, "EA", 2))
			get_path(line, &tex_count, map->wall_textures[TEX_EA]);
		else if (line[0] == 'C')
			get_rgb(line, &tex_count, map->rgb_colors[RGB_C]);
		else if (line[0] == 'F')
			get_rgb(line, &tex_count, map->rgb_colors[RGB_F]);
		free(line);
		line = get_next_line(fd);
	}
	printf("NO -> %s\n", map->wall_textures[TEX_NO]);
	printf("SO -> %s\n", map->wall_textures[TEX_SO]);
	printf("WE -> %s\n", map->wall_textures[TEX_WE]);
	printf("EA -> %s\n", map->wall_textures[TEX_EA]);
	printf("C -> %s\n", map->rgb_colors[RGB_C]);
	printf("F -> %s\n", map->rgb_colors[RGB_F]);
	/* if (!check_textures(map->wall_textures, map->rgb_colors))
		return (FALSE); */
	return (TRUE);
}

static int	is_line_empty(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\n')
	{
		if (!((line[i] >= 9 && line[i] <= 13) || line[i] == 32))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

static void	get_path(char *src, int *tex_c, char *actpath)
{
	int		i;
	int		len;
	char	*path;

	i = 2;
	if (*actpath || is_line_empty(src))
		return ;
	while ((src[i] >= 9 && src[i] <= 13) || src[i] == 32)
		i++;
	len = i;
	while (src[len] != '\n')
		len++;
	path = ft_calloc(len - i + 1, sizeof(char));
	if (!path)
		return (NULL);
	len = 0;
	while (src[i] != '\n')
		path[len++] = src[i++];
	*tex_c += 1;
	*actpath = path;
}
