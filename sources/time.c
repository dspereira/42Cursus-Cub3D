/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 15:05:36 by dsilveri          #+#    #+#             */
/*   Updated: 2023/03/01 19:03:08 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static unsigned long	get_actual_time_ms(void);
static unsigned long	get_offset_time(void);

unsigned long	check_time_ms(unsigned long time)
{
	static unsigned long	buff = 0;
	unsigned long			actual;

	if (!buff)
		buff = get_actual_time_ms();
	actual = get_actual_time_ms();
	if ((actual - buff) >= time)
	{
		buff = 0;
		return (actual);
	}
	return (0);
}

unsigned long	doors_time_check_ms(unsigned long time)
{
	static unsigned long	buff = 0;
	unsigned long			actual;

	if (!buff)
		buff = get_actual_time_ms();
	actual = get_actual_time_ms();
	if ((actual - buff) >= time)
	{
		buff = 0;
		return (actual);
	}
	return (0);
}

unsigned long	moves_time_check_ms(unsigned long time)
{
	static unsigned long	buff = 0;
	unsigned long			actual;

	if (!buff)
		buff = get_actual_time_ms();
	actual = get_actual_time_ms();
	if ((actual - buff) >= time)
	{
		buff = 0;
		return (actual);
	}
	return (0);
}

static unsigned long	get_actual_time_ms(void)
{
	struct timeval	t;
	unsigned long	time_ms;
	unsigned long	offset;

	gettimeofday(&t, NULL);
	offset = get_offset_time();
	time_ms = ((t.tv_sec * 1000) + (t.tv_usec / 1000)) - offset;
	return (time_ms);
}

static unsigned long	get_offset_time(void)
{
	static unsigned long	offset = 0;
	unsigned long			buffer;
	struct timeval			t;

	if (!offset)
	{
		gettimeofday(&t, NULL);
		buffer = (t.tv_sec * 1000) + (t.tv_usec / 1000);
		offset = buffer;
		while (1)
		{
			gettimeofday(&t, NULL);
			offset = (t.tv_sec * 1000) + (t.tv_usec / 1000);
			if (offset > buffer)
				break ;
		}
	}
	return (offset);
}
