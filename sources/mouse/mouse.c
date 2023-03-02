/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 12:01:17 by dsilveri          #+#    #+#             */
/*   Updated: 2023/03/01 15:26:05 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static int	mouse_checks_if_is_inside_window(int x, int y);

void	mouse_init(t_win win, int *mouse_state)
{
	*mouse_state = MOUSE_HIDE;
	mlx_mouse_hide(win.mlx, win.mlx_win);
	mlx_mouse_move(win.mlx, win.mlx_win, WIN_WIDTH / 2, WIN_HEIGHT / 2);
}

t_pos	mouse_get_pos(t_win win)
{
	t_pos	pos;

	mlx_mouse_get_pos(win.mlx, win.mlx_win, &pos.x, &pos.y);
	return (pos);
}

void	mouse_update(t_mouse *mouse, t_pos mouse_pos)
{
	mouse->last = mouse->actual;
	mouse->actual = mouse_pos;
}

void	mouse_recenter(t_win win, t_mouse *mouse)
{
	int		win_half_w;
	int		win_half_h;
	t_pos	actual;

	win_half_w = WIN_WIDTH / 2;
	win_half_h = WIN_HEIGHT / 2;
	actual = mouse->actual;
	if (actual.x >= WIN_WIDTH || actual.x <= 0)
	{
		actual.x = win_half_w;
		mouse_update(mouse, actual);
		mlx_mouse_move(win.mlx, win.mlx_win, actual.x, actual.y);
	}
	if (actual.y >= WIN_HEIGHT || actual.y <= 0)
	{
		actual.y = win_half_h;
		mouse_update(mouse, actual);
		mlx_mouse_move(win.mlx, win.mlx_win, actual.x, actual.y);
	}
}

void	mouse_state_control(t_win win, int *mouse_state)
{	
	if (*mouse_state == MOUSE_CHANGE_SHOW)
	{
		mlx_mouse_show(win.mlx, win.mlx_win);
		*mouse_state = MOUSE_SHOW;
	}
	else if (*mouse_state == MOUSE_CHANGE_HIDE)
	{
		mlx_mouse_hide(win.mlx, win.mlx_win);
		*mouse_state = MOUSE_HIDE;
	}
}
