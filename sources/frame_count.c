/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame_count.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcandeia <dcandeia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 13:57:41 by dcandeia          #+#    #+#             */
/*   Updated: 2023/02/28 15:47:23 by dcandeia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static char	*ft_itoa(int n);

void	frame_count(t_win win)
{
	static int	frames_count = 0;
	static char	*nbr_frames = NULL;

	frames_count++;
	if (nbr_frames)
	{
		mlx_string_put(win.mlx, win.mlx_win, FRAMES_WIN_POS_X, \
			FRAMES_WIN_POS_Y, FRAMES_TEXT_COLOR, "FPS: ");
		mlx_string_put(win.mlx, win.mlx_win, FRAMES_WIN_POS_X + 28, \
			FRAMES_WIN_POS_Y + 1, FRAMES_TEXT_COLOR, nbr_frames);
	}
	if (check_time_ms(TIME_PER_FRAME))
	{
		if (nbr_frames)
			free(nbr_frames);
		nbr_frames = ft_itoa(frames_count);
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
