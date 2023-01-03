/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcandeia <dcandeia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 12:00:26 by dcandeia          #+#    #+#             */
/*   Updated: 2023/01/03 15:56:55 by dcandeia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int	main(int ac, char **av)
{
	if (ac == 2)
	{
		if (!check_file(av[1]))
			return (-1);
		if (!is_valid_map(av[1]))
			return (-1);
		printf("MAP: OK\n");
		return (0);
	}
	printf("Error: Invalid number of Arguments\n");
	return (-1);
}
