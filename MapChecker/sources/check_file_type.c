/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file_type.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 12:08:40 by dcandeia          #+#    #+#             */
/*   Updated: 2023/01/04 13:28:29 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

static int		find_last_char_index(char *file, char to_find);
static int		ft_strcmp(char *s1, char *s2);
static char		*ft_substr(char const *s, unsigned int start, size_t len);

int	is_valid_file_type(char *file)
{
	char	*extension;
	int		dot_index;

	dot_index = find_last_char_index(file, '.');
	extension = ft_substr(file, dot_index, (ft_strlen(file) - dot_index));
	if (ft_strcmp(extension, ".cub"))
	{
		free(extension);
		print_error_msg("Invalid File Type");
		return (FALSE);
	}
	free(extension);
	return (TRUE);
}

static char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	a;
	size_t	i;
	char	*substring;

	if (!s)
		return (0);
	i = start;
	a = 0;
	if (len > ft_strlen(s))
		len = ft_strlen(s) + 1;
	substring = (char *)malloc(len + 1);
	if (!substring)
		return (0);
	while (i < ft_strlen(s) && a < len)
		substring[a++] = s[i++];
	substring[a] = '\0';
	return (substring);
}

static int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

/*
	Function to find the index of the last appeereance of char in a string.
	Returns -1 if the charecter is not founded
	Returns the index of the char in the string.

	Parameters:
	file		-> string to serch the character
	to_find		-> character to find in the string
*/
static int	find_last_char_index(char *file, char to_find)
{
	int	i;
	int	exist;

	i = 0;
	exist = -1;
	while (file[i])
		i++;
	while (i >= 0)
	{
		if (file[i] == to_find)
		{
			exist = i;
			break ;
		}
		i--;
	}
	return (exist);
}
