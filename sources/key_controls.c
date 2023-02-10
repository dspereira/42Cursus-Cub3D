/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_controls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 16:29:37 by dsilveri          #+#    #+#             */
/*   Updated: 2023/02/10 14:14:03 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	key(int keycode, t_data *data)
{
	if (keycode == KEY_W)
		player_move(data->player, data->map.content, FORWARD);
	else if (keycode == KEY_S)
		player_move(data->player, data->map.content, BACKWARD);
	else if (keycode == KEY_A)
		player_move(data->player, data->map.content, LEFT);
	else if (keycode == KEY_D)
		player_move(data->player, data->map.content, RIGHT);
	else if (keycode == KEY_ARROW_R)
		player_update_vision(data->player, -ROT_STEP);
	else if (keycode == KEY_ARROW_L)
		player_update_vision(data->player, ROT_STEP);
	else if (keycode == KEY_Q)
		data->mouse_state = MOUSE_CHANGE_SHOW;
	else if (keycode == KEY_ESC)
		exit(0);
	return (0);
}
