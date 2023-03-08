/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 14:50:07 by dcandeia          #+#    #+#             */
/*   Updated: 2023/03/08 17:01:09 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	free_tex_memory(t_tex tex, t_win *win)
{
	int	i;

	i = 0;
	if (!win)
		return ;
	if (tex.no.mlx_img)
		mlx_destroy_image(win->mlx, tex.no.mlx_img);
	if (tex.so.mlx_img)
		mlx_destroy_image(win->mlx, tex.so.mlx_img);
	if (tex.ea.mlx_img)
		mlx_destroy_image(win->mlx, tex.ea.mlx_img);
	if (tex.we.mlx_img)
		mlx_destroy_image(win->mlx, tex.we.mlx_img);
	if (tex.door_side.mlx_img)
		mlx_destroy_image(win->mlx, tex.door_side.mlx_img);
	while (i < 9)
	{
		if (tex.doors[i].mlx_img)
			mlx_destroy_image(win->mlx, tex.doors[i].mlx_img);
		i++;
	}
}

void	free_mlx_memory(t_win *win)
{
	if (win)
	{
		if (win->nbr_frames)
			free(win->nbr_frames);
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
		if (player->rays)
			free (player->rays);
		free (player);
	}
	player = NULL;
}
