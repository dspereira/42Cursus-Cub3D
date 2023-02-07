//void draw_tex_line(t_img frame, t_img tex, t_pos f_pos, t_pos tex_pos, int f_height);
#include <cube3d.h>
#include <header.h>

void	draw_wall_1(t_img frame, t_img tex)
{
	int		f_height = 3000;
	int		i = 0;
	int		color = 0;
	float	xpercentage = 0;
	t_pos	spot;
	double	scale;

	spot.x = 0;
	spot.y = 0;500
	scale = ((double)1) / f_height;
	while (i < f_height)
	{
		xpercentage = (i * scale) * tex.width;
		for (int a = 0; a < f_height; a++)
		{
			spot.x = xpercentage;
			spot.y = (a * scale) * tex.height;
			color = get_tex_color(tex, spot);
			draw_pixel(frame,  i, a, color);
		}
		printf("[ %d ]\n", i);
		i++;
	}
}

void	draw_wall_2(t_img frame, t_img tex)
{
	int		f_height = 200;
	int		i = 0;
	int		color = 0;
	float	xpercentage = 0;
	t_pos	spot;
	double	scale;

	spot.x = 0;
	spot.y = 0;
	while (i < 100)
	{
		scale = ((double)1) / f_height;
		xpercentage = (i * scale) * tex.width;
		for (int a = 0; a < f_height; a++)
		{
			spot.x = xpercentage;
			spot.y = (a * scale) * tex.height;
			color = get_tex_color(tex, spot);
			draw_pixel(frame,  200 + i, 200 - (f_height / 2) + a , color);
		}
		f_height -= 2;
		i++;
	}
}



