/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 12:02:32 by dcandeia          #+#    #+#             */
/*   Updated: 2023/01/04 13:31:40 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

typedef struct s_file
{
	char		*filename;
	char		**content;
	int			nbr_lines;
}				t_file;

# define BUFFER_SIZE	13

# define FALSE	0
# define TRUE	1

void	*ft_calloc(size_t count, size_t size);

int		check_file(t_file *file_data);
t_file	*get_file_info(const char *filename);
int		is_valid_file_type(char *file);

void	free_file_mem(t_file *file);

void	print_error_msg(char *msg);

char	*get_next_line(int fd);

int		is_valid_map(char *map_file);
char	**get_map(char *file);
int		check_map_elements(char **map);

#endif
