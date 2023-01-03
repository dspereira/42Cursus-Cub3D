/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcandeia <dcandeia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 12:02:32 by dcandeia          #+#    #+#             */
/*   Updated: 2023/01/03 15:53:23 by dcandeia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

# define BUFFER_SIZE	13

# define FALSE	0
# define TRUE	1

int		check_file(char	*file);
int		is_valid_file_type(char *file);
void	print_error_msg(char *msg);

char	*get_next_line(int fd);

int		is_valid_map(char *map_file);
char	**get_map(char *file);

#endif
