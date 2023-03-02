/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcandeia <dcandeia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 14:50:07 by dcandeia          #+#    #+#             */
/*   Updated: 2023/03/02 15:45:07 by dcandeia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	free_tex_memory(t_tex tex, void *mlx)
{
	int	i;

	i = 0;
	if (tex.no.mlx_img)
		mlx_destroy_image(mlx, tex.no.mlx_img);
	if (tex.so.mlx_img)
		mlx_destroy_image(mlx, tex.so.mlx_img);
	if (tex.ea.mlx_img)
		mlx_destroy_image(mlx, tex.ea.mlx_img);
	if (tex.we.mlx_img)
		mlx_destroy_image(mlx, tex.we.mlx_img);
	if (tex.door_side.mlx_img)
		mlx_destroy_image(mlx, tex.door_side.mlx_img);
	while (i < 9)
	{
		if (tex.doors[i].mlx_img)
			mlx_destroy_image(mlx, tex.doors[i].mlx_img);
		i++;
	}
}

void	free_mlx_memory(t_win *win)
{
	mlx_destroy_image(win->mlx, win->frame.mlx_img);
	mlx_destroy_window(win->mlx, win->mlx_win);
	free (win->mlx);
	free (win);
	win = NULL;
}

void	free_player_memory(t_player *player)
{
	free (player->rays);
	free (player);
	player = NULL;
}
