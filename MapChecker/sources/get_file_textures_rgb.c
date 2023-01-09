/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file_textures_rgb.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcandeia <dcandeia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 11:01:43 by dcandeia          #+#    #+#             */
/*   Updated: 2023/01/09 12:02:15 by dcandeia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

static int	get_number(char *src, int *index);
static int	check_rgb_elemts(char *src);

int	get_rgb(char *src, int *tex_count, char actual_colour)
{
	int	r;
	int	g;
	int	b;
	int	index;

	if (actual_colour != -1)
		return (actual_colour);
	if (!check_rgb_elemts(src))
		return (-1);
	index = 2;
	while ((src[index] >= 9 && src[index] <= 13) || src[index] == 32)
		index++;
	r = get_number(src, &index);
	g = get_number(src, &index);
	b = get_number(src, &index);
	if (r == -1 || g == -1 || b == -1)
		return (-1);
	*tex_count += 1;
	return ((r << 16) + (g << 8) + b);
}

static int	get_number(char *src, int *index)
{
	int	nbr;
	int	i;

	i = *index;
	nbr = 0;
	if (!(src[i] >= '0' && src[i] <= '9'))
		return (-1);
	while (src[i] >= '0' && src[i] <= '9')
	{
		nbr = (nbr * 10) + (src[i] - 48);
		i++;
	}
	if (src[i] == ',')
		*index = i + 1;
	else
		*index = i;
	if (nbr > 255 || nbr < 0)
		nbr = -1;
	return (nbr);
}

static int	check_rgb_elemts(char *src)
{
	int	i;
	int	amount_nbrs;

	i = 2;
	amount_nbrs = 0;
	while ((src[i] >= 9 && src[i] <= 13) || src[i] == 32)
		i++;
	while (src[i] != '\n')
	{
		if ((src[i] < '0' || src[i] > '9') && src[i] != ',')
			return (FALSE);
		if (src[i] == ',')
			amount_nbrs++;
		i++;
	}
	if (amount_nbrs != 2)
		return (FALSE);
	return (TRUE);
}
