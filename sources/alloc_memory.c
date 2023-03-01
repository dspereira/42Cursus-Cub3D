/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcandeia < dcandeia@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 11:26:50 by dcandeia          #+#    #+#             */
/*   Updated: 2023/03/01 17:20:55 by dcandeia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static t_alloc_mem  *alloc_mem(t_data *elem);

void    init_alloc_mem(void)
{
	alloc_mem(0);
}

void    save_alloc_mem(t_data *mem)
{
	alloc_mem(mem);	
}

void	free_alloc_mem(void)
{
	t_alloc_mem	*mem;

	mem = alloc_mem(0);
	if (mem && mem->data)
	{
		free_map_memory(mem->data->map);
		free (mem);
	}
}

static t_alloc_mem  *alloc_mem(t_data *elem)
{
	static t_alloc_mem	*mem = 0;

	if (!mem)
	{
		mem = malloc(sizeof(t_alloc_mem));
		if (!mem)
		{
			print_error_msg("Out of memory!\n");
			exit(EXIT_FAILURE);
		}
		mem->data = 0;
	}
	if (elem)
		mem->data = elem;
	return (mem);
}
