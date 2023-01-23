/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_resizer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcandeia <dcandeia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 09:14:18 by dcandeia          #+#    #+#             */
/*   Updated: 2023/01/23 10:24:18 by dcandeia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int			find_big_line_len(char **src);
int			get_map_size(char **map);
static char	*resize_line(char *src, int max_len);
static char	*fill_first_last_line(int len);

void	map_resizer(char ***src)
{
	char	**res;
	int		big_len;
	int		i;
	int		a;

	big_len = find_big_line_len(*src);
	i = 1;
	a = 0;
	if (get_map_size(*src) < 3)
		return ;
	res = ft_calloc(get_map_size(*src) + 3, sizeof(char *));
	res[0] = fill_first_last_line(big_len);
	while (a < get_map_size(*src))
		res[i++] = resize_line((*src)[a++], big_len);
	res[i] = fill_first_last_line(big_len);
	free (*src);
	*src = res;
}

static char	*resize_line(char *src, int max_len)
{
	char	*dst;
	int		i;
	int		a;

	if (!src)
		return (NULL);
	dst = ft_calloc(max_len + 3, sizeof(char));
	i = 1;
	a = 0;
	if (!dst)
	{
		free(src);
		return (NULL);
	}
	dst[0] = ' ';
	while (src[a])
		dst[i++] = src[a++];
	while (i < max_len + 2)
		dst[i++] = ' ';
	free(src);
	return (dst);
}

static char	*fill_first_last_line(int len)
{
	char	*res;
	int		i;

	res = ft_calloc(len + 3, sizeof(char));
	i = 0;
	while (i < len + 2)
	{
		res[i] = ' ';
		i++;
	}
	return (res);
}
