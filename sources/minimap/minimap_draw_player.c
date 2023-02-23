/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_draw_player.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 20:44:57 by dsilveri          #+#    #+#             */
/*   Updated: 2023/02/23 19:00:03 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static void		draw_player_circle(t_img img, t_pos p_pos, float dir);
static void		draw_player_arrow(t_img img, t_pos p_pos, float dir);
static t_pos	get_player_pos_minimap(t_pos p_pos, t_minimap minimap);

void	minimap_draw_player(t_img img, t_player player, t_minimap minimap)
{
	t_pos	p_pos;

	p_pos = get_player_pos_minimap(player.pos, minimap);
	draw_player_circle(img, p_pos, player.dir);
	draw_player_arrow(img, p_pos, player.dir);
}

static void	draw_player_circle(t_img img, t_pos p_pos, float dir)
{
	t_pos	point;
	int		i;

	i = 0;
	while (i < 360)
	{
		point = get_new_dist_pos(p_pos, i, MINIMAP_PLAYER_RADIUS);
		draw_line(img, p_pos, point, MINIMAP_PLAYER_COLOR);
		point = get_new_dist_pos(p_pos, i, MINIMAP_PLAYER_RADIUS + 1);
		draw_pixel(img, point.x, point.y, MINIMAP_ARROW_COLOR);
		point = get_new_dist_pos(p_pos, i, MINIMAP_PLAYER_RADIUS + 2);
		draw_pixel(img, point.x, point.y, MINIMAP_ARROW_COLOR);
		i++;
	}
}

static void	draw_player_arrow(t_img img, t_pos p_pos, float dir)
{
	t_pos	new_pos;
	t_pos	point;
	float	new_dir;
	float	i;

	new_pos = get_new_dist_pos(p_pos, dir, PLAYER_RADIUS + MINIMAP_ARROW_SIZE);
	new_dir = normalizeAngles(dir + 180);
	i = new_dir;
	while (i <= new_dir + 28)
	{
		point = get_new_dist_pos(new_pos, i, MINIMAP_ARROW_SIZE);
		draw_line(img, new_pos, point, MINIMAP_ARROW_COLOR);
		i++;
	}
	i = new_dir;
	while (i >= new_dir - 28)
	{
		point = get_new_dist_pos(new_pos, i, MINIMAP_ARROW_SIZE);
		draw_line(img, new_pos, point, MINIMAP_ARROW_COLOR);
		i--;
	}
}

static t_pos	get_player_pos_minimap(t_pos p_pos, t_minimap minimap)
{
	t_pos	init_pos;

	p_pos = get_player_pos_map_scaled(p_pos, minimap);
	init_pos = get_minimap_init_pos(p_pos, minimap);
	p_pos.x += minimap.win_pos.x - init_pos.x;
	p_pos.y += minimap.win_pos.y - init_pos.y;
	return (p_pos);
}
