/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 12:01:17 by dsilveri          #+#    #+#             */
/*   Updated: 2023/02/10 15:21:02 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static int mouse_checks_if_is_inside_window(int x, int y);

void mouse_init(t_win win, int *mouse_state)
{
	*mouse_state = MOUSE_HIDE;
	mlx_mouse_hide(win.mlx, win.mlx_win);
	mlx_mouse_move(win.mlx, win.mlx_win, WIN_WIDTH / 2, WIN_HEIGHT / 2);
}

t_pos mouse_get_pos(t_win win)
{
	t_pos pos;

	mlx_mouse_get_pos(win.mlx, win.mlx_win, &pos.x, &pos.y);
	return (pos);
}

void mouse_control(t_win win, int *mouse_state)
{
	if (*mouse_state == MOUSE_HIDE)
		mlx_mouse_move(win.mlx, win.mlx_win, WIN_WIDTH / 2, WIN_HEIGHT / 2);
	else if (*mouse_state == MOUSE_CHANGE_SHOW)
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

int	mouse_hook(int button, int x, int y, t_data *data)
{
	if (button == BUTTON_LEFT_CLICK && data->mouse_state == MOUSE_SHOW)
	{
		if (mouse_checks_if_is_inside_window(x, y))
			data->mouse_state = MOUSE_CHANGE_HIDE;
	}
	return (0);
}

static int mouse_checks_if_is_inside_window(int x, int y)
{
	if (x >= 0 && x <= WIN_WIDTH)
	{
		if (y >= 0 && y <= WIN_HEIGHT)
			return (1);
	}
	return (0);
}
