/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 14:57:54 by dsilveri          #+#    #+#             */
/*   Updated: 2023/01/21 20:09:51 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int math_abs(int n)
{
	if (n > 0)
		return (n);
	else
		return (n * -1);
}

float normalizeAngles(float angle)
{
	if (angle < 0)
		angle += 360;
	else if (angle >= 360)
		angle -= 360;
	return angle;
}	

double cos_degree(double angle)
{
	return (cos(angle * 0.0174532925));
}

double sin_degree(double angle)
{
	return (sin(angle * 0.0174532925));
}
