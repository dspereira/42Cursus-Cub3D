/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcandeia < dcandeia@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 14:50:07 by dcandeia          #+#    #+#             */
/*   Updated: 2023/03/03 12:17:14 by dcandeia         ###   ########.fr       */
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
	if (win)
	{
		mlx_clear_window(win->mlx, win->mlx_win);
		mlx_destroy_image(win->mlx, win->frame.mlx_img);
		mlx_destroy_window(win->mlx, win->mlx_win);
		mlx_destroy_display(win->mlx);
		free (win->mlx);
		free (win);
	}
	win = NULL;
}

void	free_player_memory(t_player *player)
{
	if (player)
	{
		free (player->rays);
		free (player);
	}
	player = NULL;
}
