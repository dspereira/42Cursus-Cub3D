/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcandeia <dcandeia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 14:51:29 by dcandeia          #+#    #+#             */
/*   Updated: 2023/01/03 15:02:31 by dcandeia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int	check_file(char	*file)
{
	int	fd;
	
	if (!is_valid_file_type(file))
		return (FALSE);
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		print_error_msg("Impossible to read from File");
		return (FALSE);
	}
	close(fd);
	return (TRUE);
}
