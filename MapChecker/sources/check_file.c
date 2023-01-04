/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 14:51:29 by dcandeia          #+#    #+#             */
/*   Updated: 2023/01/04 13:33:05 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

static void	print_file_info(t_file *file);

int	check_file(t_file *file_data)
{
	int	ret;

	ret = TRUE;
	if (!file_data)
		ret = FALSE;
	if (!is_valid_file_type(file_data->filename))
		ret = FALSE;
	if (!file_data->nbr_lines)
		ret = FALSE;
	if (!file_data->content)
		ret = FALSE;
	if (ret == FALSE)
	{
		free_file_mem(file_data);
		return (ret);
	}
	print_file_info(file_data);
	return (ret);
}

void	free_file_mem(t_file *file)
{
	int	i;

	i = 0;
	if (file)
	{
		while (i < file->nbr_lines)
		{
			if (file->content[i])
				free(file->content[i]);
			i++;
		}
		free(file->content);
		free(file);
	}
}

static void	print_file_info(t_file *file)
{
	printf("File Name: %s\n", file->filename);
	printf("Nbr Lines: %d\n", file->nbr_lines);
	printf("File Content:\n");
	for (int i = 0; i < file->nbr_lines; i++)
		printf("%s", file->content[i]);
	return ;
}
