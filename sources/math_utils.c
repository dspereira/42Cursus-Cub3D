/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcandeia < dcandeia@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 14:57:54 by dsilveri          #+#    #+#             */
/*   Updated: 2023/02/24 16:50:44 by dcandeia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	math_abs(int n)
{
	if (n > 0)
		return (n);
	else
		return (n * -1);
}

float	normalize_angles(float angle)
{
	if (angle < 0)
		angle += 360;
	else if (angle >= 360)
		angle -= 360;
	return (angle);
}	

double	cos_degree(double angle)
{
	return (cos(angle * 0.0174532925));
}

double	sin_degree(double angle)
{
	return (sin(angle * 0.0174532925));
}

int	clamp(int min, int max, int value)
{
	int	result;

	if (value >= min && value <= max)
		result = value;
	else if (value < min)
		result = min;
	else if (value > max)
		result = max;
	return (result);
}
