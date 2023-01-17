/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 10:50:11 by dsilveri          #+#    #+#             */
/*   Updated: 2023/01/17 15:30:42 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
#define CUBE3D_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mlx.h>

typedef struct s_win
{
	void	*mlx;
	void	*mlx_win;
}	t_win;

typedef struct s_pos 
{
	int x;
	int y;
}	t_pos;

// math_utils.c
int math_abs(int n);

// mlx_utils.c
void mlx_draw_line(t_win win, t_pos init, t_pos end, int color);
void mlx_draw_stroke_square(t_win win, t_pos init, int size, int color);
void mlx_draw_fill_square(t_win win, t_pos init, int size, int color);

#endif