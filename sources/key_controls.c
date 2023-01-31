/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_controls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 16:29:37 by dsilveri          #+#    #+#             */
/*   Updated: 2023/01/31 16:30:10 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	key(int keycode, t_player *player)
{
	if (keycode == KEY_W)
		player_move(player, FORWARD);
	else if (keycode == KEY_S)
		player_move(player, BACKWARD);
	else if (keycode == KEY_A)
		player_move(player, LEFT);
	else if (keycode == KEY_D)
		player_move(player, RIGHT);
	else if (keycode == KEY_ARROW_R)
		player_update_vision(player, -ROT_STEP);
	else if (keycode == KEY_ARROW_L)
		player_update_vision(player, ROT_STEP);
	return (0);
}
