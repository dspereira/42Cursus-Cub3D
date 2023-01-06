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
	if (!is_valid_file_type(file_data->filename))
		ret = FALSE;
	else if (!file_data || !file_data->nbr_lines || !file_data->content)
	{
		print_error_msg("Invalid Map File");
		ret = FALSE;
	}
	if (file_data)
		print_file_info(file_data);
	return (ret);
}

static void	print_file_info(t_file *file)
{
	if (!file->content || !file->nbr_lines)
		return ;
	printf("File Name: %s\n", file->filename);
	printf("Nbr Lines: %d\n", file->nbr_lines);
	printf("File Content:\n");
	for (int i = 0; i < file->nbr_lines; i++)
		printf("%s", file->content[i]);
	printf("\n");
	return ;
}
