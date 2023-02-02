
#include "cube3d.h"

int	key(int keycode, t_player *player);
int render_win(void *data);

// Just for debug
char **fill_map_debug(char map[MAP_WIDTH][MAP_HEIGHT]);

int main(void) 
{
	t_win		win;
	t_pos		pos1;
	t_pos		pos2;
	int			red;
	int 		size;
	t_player	*player;
	t_map		map;
	t_data		data;
    t_img       tex;

	char map1[24][24] = {
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
		{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
		{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	};

	map.content = fill_map_debug(map1);
	if (map.content == NULL)
		return (0);

	player = player_init((t_pos){80, 120}, 0);
	//ray_cast(player, map);

	win.mlx = mlx_init();
	win.mlx_win = mlx_new_window(win.mlx, WIN_WIDTH, WIN_HEIGHT, "Cube3D");


    tex.mlx_img = mlx_xpm_file_to_image(win.mlx, "textures/bricksx64.xpm", &(tex.width), &(tex.height));
    tex.addr = mlx_get_data_addr(tex.mlx_img, &(tex.bpp), &(tex.line_len), &(tex.endian));
    data.tex = tex;

    // int i = 0;
    // int j = 0;
    // while (i < 64 * tex.line_len)
    // {
    //     j = 0;
    //     while (j < tex.line_len)
    //     {
    //         printf("%d", tex.addr[i + j]);
    //         j++;
    //     }
    //     printf("\n");
    //     i += tex.line_len;
    // }
    /*printf("%d\n", tex.bpp);
    printf("%u\n", tex.addr[0]);
    printf("%u\n", tex.addr[1]);
    printf("%u\n", tex.addr[2]);
    printf("%u\n", tex.addr[3]);*/
    //return(0);

	win.frame.mlx_img = mlx_new_image(win.mlx, WIN_WIDTH, WIN_HEIGHT);
	win.frame.addr = mlx_get_data_addr(win.frame.mlx_img, &(win.frame.bpp), &(win.frame.line_len), &(win.frame.endian));
	data.win = &win;
	data.player = player;
	data.map = map;

	mlx_loop_hook(win.mlx, render_win, &data);
	mlx_key_hook(win.mlx_win, key, player);
	mlx_loop(win.mlx);
	return (0);
}

int render_win(void *data)
{
	static int	frames_count = 0;
	t_player	*player;
	t_map		map;
	t_win		win;
    t_img       tex;

	player = ((t_data*)data)->player;
	map = ((t_data*)data)->map;
	win = *((t_data*)data)->win;
    tex = ((t_data*)data)->tex;

	raycast_all(player, map.content);

    draw_fill_rectangle(win.frame, (t_pos){WIN_WIDTH / 2 - 64, WIN_HEIGHT / 2 - 64}, (t_value){64, 64}, WALL_COLOR);

    for (int i = 0; i < 64; i++)
        draw_tex_line(win.frame, tex, (t_pos){(WIN_WIDTH / 2 - 64) + i, WIN_HEIGHT / 2 - 64}, (t_pos){i, 0}, 64);

	mlx_put_image_to_window(win.mlx, win.mlx_win, win.frame.mlx_img, 0, 0);
	frames_count++;
	if (check_time_ms(1000))
	{
		printf("fps: %d\n", frames_count);
		frames_count = 0;
	}
}

char **fill_map_debug(char map[MAP_WIDTH][MAP_HEIGHT])
{
	char	**m;
	int		i;
	int		j;

	m = malloc(sizeof(char *) * MAP_HEIGHT);
	if (!map)
		return (NULL);
	i = 0;
	while (i < MAP_HEIGHT)
	{
		m[i] = malloc(sizeof(char) * MAP_WIDTH);
		if (!m[i])
			return (NULL);
		i++; 
	}
	i = 0;
	j = 0;
	while (i < MAP_HEIGHT)
	{
		j = 0;
		while (j < MAP_WIDTH)
		{
			m[i][j] = map[i][j];
			j++;
		}
		i++;
	}
	/*i = 0;
	j = 0;
	while (i < MAP_HEIGHT)
	{
		j = 0;
		while (j < MAP_WIDTH)
		{
			printf("%i ",m[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}*/

	return (m);
}

