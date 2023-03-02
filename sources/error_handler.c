/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcandeia < dcandeia@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 14:08:15 by dcandeia          #+#    #+#             */
/*   Updated: 2023/03/01 17:24:03 by dcandeia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

void	print_error_msg(char *msg)
{
	int	i;

	i += write(2, "Error\n", 6);
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
	{
		free_alloc_mem();
		print_error_msg("Out of memory!\n");
		exit(EXIT_FAILURE);
	}
	return (p);
}
