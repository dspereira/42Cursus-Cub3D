/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 15:10:54 by dsilveri          #+#    #+#             */
/*   Updated: 2023/03/01 15:28:21 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static int	mouse_checks_if_is_inside_window(int x, int y);

int	mouse_hook(int button, int x, int y, t_data *data)
{
	if (button == BUTTON_LEFT_CLICK && data->mouse_state == MOUSE_SHOW)
	{
		if (mouse_checks_if_is_inside_window(x, y))
			data->mouse_state = MOUSE_CHANGE_HIDE;
	}
	return (0);
}

static int	mouse_checks_if_is_inside_window(int x, int y)
{
	if (x >= 0 && x <= WIN_WIDTH)
	{
		if (y >= 0 && y <= WIN_HEIGHT)
			return (1);
	}
	return (0);
}
