/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsilveri <dsilveri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 14:08:15 by dcandeia          #+#    #+#             */
/*   Updated: 2023/03/09 12:39:37 by dsilveri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

void	print_error_msg(char *msg)
{
	int	i;

	i = write(2, "Error\n", 6);
	putstr_error(msg);
	i += write(2, "\n", 1);
}

void	putstr_error(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i += write(2, &str[i], 1);
}

void	*oom_guard(void *p)
{
	if (!p)
		free_alloc_mem();
	return (p);
}
