/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcandeia <dcandeia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 12:02:32 by dcandeia          #+#    #+#             */
/*   Updated: 2023/01/09 11:35:28 by dcandeia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

# define TEX_NO	0
# define TEX_SO	1
# define TEX_WE	2
# define TEX_EA	3
# define TEX_C	4
# define TEX_F	5

typedef struct s_map
{
	char		**content;
	int			nbr_lines;
}				t_map;

typedef struct s_textures
{
	char		*path;
	int			colour;
}				t_textures;

typedef struct s_file
{
	char			*filename;
	char			**content;
	int				nbr_lines;
	int				end_tex_line;
	t_map			*map;
	t_textures		*tex;
}				t_file;

# define BUFFER_SIZE	13

# define FALSE	0
# define TRUE	1

void		*ft_calloc(size_t count, size_t size);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
size_t		ft_strlen(const char *src);

void		putstr_error(char *str);

int			check_file(t_file *file_data);
t_file		*get_file_info(const char *filename);
int			is_valid_file_type(char *file);

int			check_textures(t_textures *tex);
t_textures	*get_file_textures(char **content, int *tex_line_end);

void		free_memory(t_file	*file);

void		print_error_msg(char *msg);

char		*get_next_line(int fd);

t_map		*get_map(char **content, int map_begin_line);
void		resize_map(t_map *initital_map);
int			is_valid_map(t_map *map);
int			check_map_elements(char **map);
int			check_map_walls(char **map);

#endif
