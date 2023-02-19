/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:44:56 by dcandeia          #+#    #+#             */
/*   Updated: 2023/02/19 14:14:04 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	minimap_draw_map(t_img img, char **map, t_pos p_pos, t_mini_map minimap);
t_pos	minimap_get_map_pos(t_pos pos);
unsigned int minimap_get_pixel_color(int x, int y, char **map);
t_pos minimap_get_init_pos(t_pos p_pos, t_mini_map minimap);
t_pos minimap_get_drawing_pos(t_pos pos, t_pos offset_correct, t_mini_map minimap);
t_pos minimap_get_player_pos(t_pos pos, t_mini_map minimap);
void minimap_draw_player_circle(t_img img, t_pos p_pos, float dir);
void minimap_draw_player_arrow(t_img img, t_pos p_pos, float dir);
void minimap_draw_player(t_img img, float dir, t_mini_map minimap);
void minimap_draw_player1(t_img img, t_pos p_pos, float dir, t_mini_map minimap);

t_mini_map minimap_init(void)
{
	t_mini_map	minimap;
	int			offset_corner;

	offset_corner = 20;
	minimap.size.x = WIN_WIDTH * 0.2;
	minimap.size.y = WIN_HEIGHT * 0.2;
	minimap.half_size.x = minimap.size.x / 2;
	minimap.half_size.y = minimap.size.y / 2;
	minimap.win_pos.x = WIN_WIDTH - minimap.size.x - offset_corner;
	minimap.win_pos.y = WIN_HEIGHT - minimap.size.y - offset_corner;
	minimap.player_pos.x = minimap.win_pos.x + minimap.half_size.x;
	minimap.player_pos.y = minimap.win_pos.x + minimap.half_size.x;
	minimap.map_scale = (float) WIN_WIDTH / MAP_WIDTH / MINIMAP_SQUARE_SIZE;
	return (minimap);
}

void minimap_render(t_img img, char **map, t_player player, t_mini_map minimap)
{
	minimap_draw_map(img, map, player.pos, minimap);
	minimap_draw_player1(img, player.pos, player.dir, minimap);
}

void minimap_draw_map(t_img img, char **map, t_pos p_pos, t_mini_map minimap)
{
	t_pos	init_pos;
	t_pos	draw_pos;
	t_pos	pos;
	int		color;

	//printf("################################\n");

	p_pos = minimap_get_player_pos(p_pos, minimap);
	init_pos = minimap_get_init_pos(p_pos, minimap);
	pos.y = init_pos.y;
	pos.x = init_pos.x;

	t_pos test = minimap_get_drawing_pos(pos, init_pos, minimap);
	//printf("pos x: %i  y: %i\n", pos.x, pos.y);
	//printf("minimapa x: %i  y: %i\n", test.x, test.y);


	while (pos.y < init_pos.y + minimap.size.y)
	{
		pos.x = init_pos.x;
		while (pos.x < init_pos.x + minimap.size.x)
		{
			color = minimap_get_pixel_color(pos.x, pos.y, map);
			draw_pos = minimap_get_drawing_pos(pos, init_pos, minimap);
			//if (color != MINIMAP_COLOR_NONE)
				draw_pixel(img, draw_pos.x, draw_pos.y, color);
			pos.x++;
		}
		pos.y++;
	}
}

t_pos minimap_get_init_pos(t_pos p_pos, t_mini_map minimap)
{
	t_pos	pos;
	int		y_top;
	int		y_bot;
	int		x_left;
	int		x_right;

	pos.x = p_pos.x - minimap.half_size.x;
	pos.y = p_pos.y - minimap.half_size.y;

	

	y_top = pos.y;
	y_bot = pos.y + minimap.size.y;
	x_left = pos.x;
	x_right = pos.x + minimap.size.x;

	if (y_top < 0)
		pos.y = 0;
	if (y_bot >= MINIMAP_SQUARE_SIZE * MAP_HEIGHT)
		pos.y = MINIMAP_SQUARE_SIZE * MAP_HEIGHT - minimap.size.y;
	
	if (x_left < 0)
		pos.x = 0;
	if (x_right >= MINIMAP_SQUARE_SIZE * MAP_WIDTH)
		pos.x = MINIMAP_SQUARE_SIZE * MAP_WIDTH - minimap.size.x;

	if (pos.x < MINIMAP_SQUARE_SIZE)
		pos.x += MINIMAP_SQUARE_SIZE - pos.x;
	if (pos.y < MINIMAP_SQUARE_SIZE)
		pos.y += MINIMAP_SQUARE_SIZE - pos.y;
	if (x_right > (MINIMAP_SQUARE_SIZE * MAP_WIDTH) - MINIMAP_SQUARE_SIZE)
	{
		printf("valor da subtracao: %i\n", x_right -((MINIMAP_SQUARE_SIZE * MAP_WIDTH) - MINIMAP_SQUARE_SIZE));
		//printf("pos.x: %i", pos.x);
		//printf("final: %i", pos.x);

		if (x_right - ((MINIMAP_SQUARE_SIZE * MAP_WIDTH) - MINIMAP_SQUARE_SIZE) <= MINIMAP_SQUARE_SIZE)
			pos.x -=  x_right - ((MINIMAP_SQUARE_SIZE * MAP_WIDTH) - MINIMAP_SQUARE_SIZE);
		else 
			pos.x +=  x_right - ((MINIMAP_SQUARE_SIZE * MAP_WIDTH) - MINIMAP_SQUARE_SIZE);

	}

	//printf("get_init_pos x: %i  y: %i\n", pos.x, pos.y);
	return (pos);
}



/*
t_pos minimap_get_init_pos(t_pos p_pos, t_mini_map minimap)
{
	t_pos	pos;
	int		y_top;
	int		y_bot;
	int		x_left;
	int		x_right;

	pos.x = p_pos.x - minimap.half_size.x;
	pos.y = p_pos.y - minimap.half_size.y;

	

	y_top = pos.y;
	y_bot = pos.y + minimap.size.y;
	x_left = pos.x;
	x_right = pos.x + minimap.size.x;

	if (y_top < 0)
		pos.y = 0 + MINIMAP_SQUARE_SIZE;
	if (y_bot >= MINIMAP_SQUARE_SIZE * MAP_HEIGHT)
		pos.y = MINIMAP_SQUARE_SIZE * MAP_HEIGHT - minimap.size.y - MINIMAP_SQUARE_SIZE;
	
	if (x_left < 0)
		pos.x = 0 + MINIMAP_SQUARE_SIZE;
	if (x_right >= MINIMAP_SQUARE_SIZE * MAP_WIDTH)
		pos.x = MINIMAP_SQUARE_SIZE * MAP_WIDTH - minimap.size.x - MINIMAP_SQUARE_SIZE;

	if (pos.x < MINIMAP_SQUARE_SIZE)
		pos.x += MINIMAP_SQUARE_SIZE - pos.x;
	if (pos.y < MINIMAP_SQUARE_SIZE)
		pos.y += MINIMAP_SQUARE_SIZE - pos.y;
	if (x_right > (MINIMAP_SQUARE_SIZE * MAP_WIDTH) - MINIMAP_SQUARE_SIZE)
		pos.x -= pos.x - ((MINIMAP_SQUARE_SIZE * MAP_WIDTH) - MINIMAP_SQUARE_SIZE);

	//printf("get_init_pos x: %i  y: %i\n", pos.x, pos.y);
	return (pos);
}
*/

/*
t_pos minimap_get_init_pos(t_pos p_pos, t_mini_map minimap)
{
	t_pos	top_r_pos;
	t_pos	top_l_pos;
	t_pos	bot_r_pos;
	t_pos	bot_l_pos;
	t_pos	res_pos;

	top_l_pos.x = p_pos.x - minimap.half_size.x;
	top_l_pos.y = p_pos.y - minimap.half_size.y;

	top_r_pos.x = top_l_pos.x + minimap.size.x;
	top_r_pos.y = top_l_pos.y;

	bot_l_pos.x = top_l_pos.x;
	bot_l_pos.y = top_l_pos.y + minimap.size.y;

	bot_r_pos.x = bot_l_pos.x + minimap.size.x;
	bot_r_pos.x = bot_l_pos.y;

	res_pos = top_l_pos;
	//canto superior esquerdo
	if (top_l_pos.y < 0 && top_l_pos.x < 0)
	{
		res_pos.x = 0;
		res_pos.y = 0;
	}
	// centro left -> tentar redizir if talvez colocar no final
	else if ((top_l_pos.y >= 0 && top_l_pos.y <= MINIMAP_SQUARE_SIZE * MAP_HEIGHT && top_l_pos.x < 0) 
			&& bot_l_pos.y >= 0 && bot_l_pos.y <= MINIMAP_SQUARE_SIZE * MAP_HEIGHT && bot_l_pos.x < 0)
	{
		res_pos.x = 0;
	}
	//canto inferior esquerdo
	else if (bot_l_pos.x <= 0 && bot_l_pos.y > MINIMAP_SQUARE_SIZE * MAP_HEIGHT)
	{
		res_pos.x = 0;
		res_pos.y = (MINIMAP_SQUARE_SIZE * MAP_HEIGHT) - minimap.size.y;	
	}


	//canto superior direito
	if (top_r_pos.y < 0 && top_r_pos.x > MINIMAP_SQUARE_SIZE * MAP_WIDTH)
	{
		res_pos.x = (MINIMAP_SQUARE_SIZE * MAP_WIDTH) - minimap.size.x;
		res_pos.y = 0;
	}
	// centro direito -> tentar redizir if talvez colocar no final
	else if ((top_r_pos.y >= 0 && top_r_pos.y <= MINIMAP_SQUARE_SIZE * MAP_HEIGHT && top_r_pos.x > MINIMAP_SQUARE_SIZE * MAP_HEIGHT)
			&& bot_r_pos.y >= 0 && bot_r_pos.y <= MINIMAP_SQUARE_SIZE * MAP_HEIGHT && bot_r_pos.x > MINIMAP_SQUARE_SIZE * MAP_HEIGHT)
	{
		printf("segundo if\n");
		res_pos.x = (MINIMAP_SQUARE_SIZE * MAP_WIDTH) - minimap.size.x;
	}
	//canto inferior direito
	else if (bot_r_pos.x <= 0 && bot_r_pos.y > MINIMAP_SQUARE_SIZE * MAP_HEIGHT)
	{
		res_pos.x = MINIMAP_SQUARE_SIZE * MAP_WIDTH;
		res_pos.y = (MINIMAP_SQUARE_SIZE * MAP_HEIGHT) - minimap.size.y;	
	}

	return (res_pos);
}

*/

/*
t_pos minimap_get_init_pos(t_pos p_pos, t_mini_map minimap)
{
	t_pos	pos;

	pos.x = p_pos.x - minimap.half_size.x;
	pos.y = p_pos.y - minimap.half_size.y;
	
	//canto superior esquerdo
	if (pos.y < 0 && pos.x < 0)
	{
		pos.x = 0;
		pos.y = 0;
	}
	//lateral esquerda
	else if (pos.y >= 0 && pos.y <= MINIMAP_SQUARE_SIZE * MAP_HEIGHT && pos.x < 0)
	{
		pos.x = 0;
	}
	//canto inferior esquerdo
	else if (pos.x <= 0 && pos.y > MINIMAP_SQUARE_SIZE * MAP_HEIGHT)
	{
		printf("entra aqui \n");
		pos.x = 0;
		pos.y = (MINIMAP_SQUARE_SIZE * MAP_HEIGHT) - minimap.size.y;	
	}
	printf("player        x: %i y: %i\n", p_pos.x, p_pos.y);
	printf("map           x: %i y: %i\n", pos.x, pos.y);
	printf("map_size %i \n", MINIMAP_SQUARE_SIZE * MAP_HEIGHT);

	
	return (pos);
}
*/
/*
t_pos minimap_get_init_pos(t_pos p_pos, t_mini_map minimap)
{
	t_pos	pos;

	pos.x = p_pos.x - minimap.half_size.x;
	pos.y = p_pos.y - minimap.half_size.y;
	return (pos);
}
*/

unsigned int minimap_get_pixel_color(int x, int y, char **map)
{
	t_pos pos;

	pos.x = x;
	pos.y = y;
	pos = minimap_get_map_pos(pos);
	if (pos.x < 0 || pos.y < 0 || pos.x >= MAP_WIDTH || pos.y >= MAP_HEIGHT)
		return (MINIMAP_COLOR_NONE);
	else if (map[pos.y][pos.x] == ' ')
		return (MINIMAP_COLOR_NONE);
	else if (map[pos.y][pos.x] == '1')
		return (MINIMAP_COLOR_WALL);
	else
		return (MINIMAP_COLOR_GROUND);
}

t_pos minimap_get_map_pos(t_pos pos)
{
	if (pos.x > 0)
    	pos.x = pos.x / MINIMAP_SQUARE_SIZE;
	if (pos.y > 0)
		pos.y = pos.y / MINIMAP_SQUARE_SIZE;
	return(pos);
}

t_pos minimap_get_drawing_pos(t_pos pos, t_pos offset_correct, t_mini_map minimap)
{
	pos.x += minimap.win_pos.x - offset_correct.x;
	pos.y += minimap.win_pos.y - offset_correct.y;
	return (pos);
}

t_pos minimap_get_player_pos(t_pos pos, t_mini_map minimap)
{
	pos.x = pos.x / minimap.map_scale;
	pos.y = pos.y / minimap.map_scale;
	return (pos);
}


void minimap_draw_player1(t_img img, t_pos p_pos, float dir, t_mini_map minimap)
{
	t_pos	init_pos;

	p_pos = minimap_get_player_pos(p_pos, minimap);
	init_pos = minimap_get_init_pos(p_pos, minimap);
	p_pos = minimap_get_drawing_pos(p_pos, init_pos, minimap);
	minimap_draw_player_circle(img, p_pos, dir);
	minimap_draw_player_arrow(img, p_pos, dir);
}


/*
void minimap_draw_player(t_img img, float dir, t_mini_map minimap)
{
	minimap_draw_player_circle(img, minimap.player_pos, dir);
	minimap_draw_player_arrow(img, minimap.player_pos, dir);
}
*/
void minimap_draw_player_circle(t_img img, t_pos p_pos, float dir)
{
	t_pos point;
	int	i;

	i = -1;
	while (++i < 360)
	{
		point = get_new_dist_pos(p_pos, i, PLAYER_RADIUS);
		draw_line(img, p_pos, point, MINIMAP_PLAYER_COLOR);
		point = get_new_dist_pos(p_pos, i, PLAYER_RADIUS + 1);
		draw_pixel(img, point.x, point.y, MINIMAP_ARROW_COLOR);
		point = get_new_dist_pos(p_pos, i, PLAYER_RADIUS + 2);
		draw_pixel(img, point.x, point.y, MINIMAP_ARROW_COLOR);
	}
}

void minimap_draw_player_arrow(t_img img, t_pos p_pos, float dir)
{
	t_pos	new_pos;
	t_pos	point;
	float	new_dir;
	float 	i;

	new_pos = get_new_dist_pos(p_pos, dir, PLAYER_RADIUS + MINIMAP_ARROW_SIZE);
	new_dir = normalizeAngles(dir + 180);
	i = new_dir;
	while (i <= new_dir + 28)
	{
		point = get_new_dist_pos(new_pos, i, MINIMAP_ARROW_SIZE - 1);
		draw_line(img, new_pos, point, MINIMAP_ARROW_COLOR);
		i ++;
	}
	i = new_dir;
	while (i >= new_dir - 28)
	{
		point = get_new_dist_pos(new_pos, i, MINIMAP_ARROW_SIZE - 1);
		draw_line(img, new_pos, point, MINIMAP_ARROW_COLOR);
		i--;
	}
}
