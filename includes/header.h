/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcandeia <dcandeia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 12:02:32 by dcandeia          #+#    #+#             */
/*   Updated: 2023/01/16 14:59:28 by dcandeia         ###   ########.fr       */
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

# define RGB_C			0
# define RGB_F			1
# define RGB_NO_COLOR	-1

# define ORIENTATION_N	90
# define ORIENTATION_S	270
# define ORIENTATION_E	0
# define ORIENTATION_W	180

typedef struct s_pos
{
	int	x;
	int	y;
}				t_pos;

typedef struct s_map
{
	char 		**wall_textures;
	int			*rgb_colors;
	char		**content;
	int			orientation;
	t_pos		pos;
}				t_map;

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

// void		free_memory(t_file	*file);

void		print_error_msg(char *msg);

char		*get_next_line(int fd);

int			get_map_content(char ***content, int fd);
int			get_player_info(char **map, int *orientation, t_pos *pos);


int			check_map(char **map);
int			check_map_elements(char **map);
int			check_map_walls(char **map);

t_map		*init_map_struct(void);
int			get_all_map_info(t_map **map, char *filename);

#endif
