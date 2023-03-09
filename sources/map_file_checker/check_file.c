/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 14:51:29 by dcandeia          #+#    #+#             */
/*   Updated: 2023/03/09 12:39:37 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static int	get_file_nbr_lines(const char *filename);

int	check_file(char *filename)
{
	int	ret;

	ret = TRUE;
	if (!is_valid_file_type(filename))
		ret = FALSE;
	else if (!filename || !get_file_nbr_lines(filename))
	{
		print_error_msg("Invalid Map File");
		ret = FALSE;
	}
	return (ret);
}

static int	get_file_nbr_lines(const char *filename)
{
	char	*str;
	int		nbr_lines;
	int		fd;

	nbr_lines = 0;
	fd = open(filename, O_RDONLY);
	if (!fd)
	{
		print_error_msg("Impossible to read from File");
		return (0);
	}
	str = get_next_line(fd);
	while (str)
	{
		free(str);
		str = get_next_line(fd);
		nbr_lines += 1;
	}
	close(fd);
	return (nbr_lines);
}
