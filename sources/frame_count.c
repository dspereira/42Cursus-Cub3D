/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame_count.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 13:57:41 by dcandeia          #+#    #+#             */
/*   Updated: 2023/03/08 11:55:32 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static char	*ft_itoa(int n);
static void	set_nframe_str(char *frames, char *src);

void	frame_count(t_win *win)
{
	static int	frames_count = 0;
	static char	frames_str[6];
	char		*aux_frames;

	frames_count++;
	aux_frames = NULL;
	if (frames_str[0] != '\0')
	{
		mlx_string_put(win->mlx, win->mlx_win, FRAMES_WIN_POS_X, \
			FRAMES_WIN_POS_Y, FRAMES_TEXT_COLOR, "FPS: ");
		mlx_string_put(win->mlx, win->mlx_win, FRAMES_WIN_POS_X + 28, \
			FRAMES_WIN_POS_Y + 1, FRAMES_TEXT_COLOR, frames_str);
	}
	if (check_time_ms(TIME_PER_FRAME))
	{
		aux_frames = ft_itoa(frames_count);
		set_nframe_str(frames_str, aux_frames);
		printf("frames: %s\n", frames_str);
		frames_count = 0;
	}
}

static int	ft_size_0(int n)
{
	int	size;

	size = 0;
	if (n > 0)
		size = 0;
	else
		size = 1;
	return (size);
}

static int	ft_sinal(int n)
{
	int	sinal;

	sinal = 0;
	if (n < 0)
		sinal = -1;
	else
		sinal = 1;
	return (sinal);
}

static char	*ft_itoa(int n)
{
	char	*str;
	long	nbr;
	size_t	size;

	size = ft_size_0(n);
	nbr = (long)n * ft_sinal(n);
	while (n)
	{
		n /= 10;
		size++;
	}
	str = (char *)malloc(size + 1);
	if (!str)
		return (0);
	*(str + size--) = '\0';
	while (nbr > 0)
	{
		*(str + size--) = nbr % 10 + '0';
		nbr /= 10;
	}
	if (size == 0 && str[1] == '\0')
		*(str + size) = '0';
	else if (size == 0 && str[1] != '\0')
		*(str + size) = '-';
	return (str);
}

static void	set_nframe_str(char *frames, char *src)
{
	int	i;

	i = -1;
	while (++i < 5)
		frames[i] = '\0';
	if (!src)
		return ;
	i = 0;
	while (src[i])
		i++;
	if (i >= 6)
	{
		i = -1;
		while (++i < 5)
			frames[i] = '9';
	}
	else
	{
		i = 0;
		while (src[i])
			frames[i++] = src[i];
	}
	free(src);
}
