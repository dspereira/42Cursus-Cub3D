/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcandeia <dcandeia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 12:00:26 by dcandeia          #+#    #+#             */
/*   Updated: 2023/01/12 15:14:37 by dcandeia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int	main(int ac, char **av)
{
	t_file	*myfile;

	if (ac == 2)
	{
		myfile = NULL;
		myfile = get_file_info((const char *)av[1]);
		if (!myfile)
			return (-1);
		if (check_file(myfile))
		{
			myfile->tex = get_file_textures(myfile->content, &myfile->end_tex_line);
			myfile->map = get_map(myfile->content, myfile->end_tex_line);
			check_textures(myfile->tex);
			is_valid_map(myfile->map);
		}
		else
		{
			free_memory(myfile);
			return (-1);
		}
		free_memory(myfile);
		return (0);
	}
	printf("Error: Invalid number of Arguments\n");
	return (-1);
}
