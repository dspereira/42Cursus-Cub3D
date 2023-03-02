/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcandeia < dcandeia@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 12:02:32 by dcandeia          #+#    #+#             */
/*   Updated: 2023/03/01 12:42:21 by dcandeia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include "cube3d.h"

# define TEX_NO	0
# define TEX_SO	1
# define TEX_WE	2
# define TEX_EA	3

# define RGB_C			0
# define RGB_F			1
# define RGB_NO_COLOR	-1

# define ORIENTATION_N	90
# define ORIENTATION_S	270
# define ORIENTATION_E	0
# define ORIENTATION_W	180

# define BUFFER_SIZE	13

# define FALSE	0
# define TRUE	1

void		*ft_calloc(size_t count, size_t size);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
size_t		ft_strlen(const char *src);

void		putstr_error(char *str);

int			check_file(char *filename);
int			is_valid_file_type(char *file);

int			check_textures(char **textures, int *rgb_colors);
int			get_map_textures(t_map **map, int fd);

char		*get_next_line(int fd);

int			get_map_content(char ***content, int fd);
int			get_player_info(char **map, int *orientation, t_pos *pos);
int         get_map_dimensions(t_map **map);
int         get_doors_info(char **map, t_pos **doors);

int			check_map(char **map);
int			check_map_elements(char **map);
int			check_map_walls(char **map);

int			init_map_struct(t_map *init);

int			get_all_map_info(t_map **map, char *filename);

#endif
