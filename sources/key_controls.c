/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_controls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 16:29:37 by dsilveri          #+#    #+#             */
/*   Updated: 2023/03/01 19:20:08 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

t_key	key_init(void)
{
	t_key	key_status;

	key_status.w = 0;
	key_status.s = 0;
	key_status.a = 0;
	key_status.d = 0;
	key_status.arrow_l = 0;
	key_status.arrow_r = 0;
	return (key_status);
}

int	key_press_hook(int keycode, t_data *data)
{
	if (keycode == KEY_W)
		data->key_state.w = 1;
	else if (keycode == KEY_S)
		data->key_state.s = 1;
	else if (keycode == KEY_A)
		data->key_state.a = 1;
	else if (keycode == KEY_D)
		data->key_state.d = 1;
	else if (keycode == KEY_ARROW_R)
		data->key_state.arrow_r = 1;
	else if (keycode == KEY_ARROW_L)
		data->key_state.arrow_l = 1;
	else if (keycode == KEY_CTRL)
		data->mouse_state = MOUSE_CHANGE_SHOW;
	else if (keycode == KEY_ESC)
		exit(0);
	else if (keycode == KEY_E)
		doors_interaction(data->map, data->player);
	return (0);
}

int	key_release_hook(int keycode, t_data *data)
{
	if (keycode == KEY_W)
		data->key_state.w = 0;
	else if (keycode == KEY_S)
		data->key_state.s = 0;
	else if (keycode == KEY_A)
		data->key_state.a = 0;
	else if (keycode == KEY_D)
		data->key_state.d = 0;
	else if (keycode == KEY_ARROW_R)
		data->key_state.arrow_r = 0;
	else if (keycode == KEY_ARROW_L)
		data->key_state.arrow_l = 0;
	return (0);
}

void	key_move_control(t_key key, t_player *player, char **map)
{
	if (!moves_time_check_ms(MOVE_SPEED_MS))
		return ;
	if (key.w)
		player_move(player, map, FORWARD);
	if (key.s)
		player_move(player, map, BACKWARD);
	if (key.a)
		player_move(player, map, LEFT);
	if (key.d)
		player_move(player, map, RIGHT);
	if (key.arrow_r)
		player_rotation_key(player, -ROT_STEP);
	if (key.arrow_l)
		player_rotation_key(player, ROT_STEP);
}
