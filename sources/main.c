/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 12:14:20 by dsilveri          #+#    #+#             */
/*   Updated: 2023/01/16 14:34:38 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdio.h>
#include <mlx.h>

typedef struct	s_vars {
	void	*mlx;
	void	*win;
}	t_vars;

int main(void) 
{
	t_vars	vars;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 400, 400, "Cube3D");
	mlx_loop(vars.mlx);
	return (0);
}