/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcandeia <dcandeia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 15:50:11 by dcandeia          #+#    #+#             */
/*   Updated: 2023/01/03 15:53:08 by dcandeia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

static int		ft_clean(char *str);
static char		*ft_strjoin(char *s1, char *s2);
static size_t	ft_len(const char *str);

char	*get_next_line(int fd)
{
	static char	cursor[FOPEN_MAX][BUFFER_SIZE + 1];
	char		*line;

	if (fd < 0 || FOPEN_MAX < fd)
		return (NULL);
	line = NULL;
	while (cursor[fd][0] || read(fd, cursor[fd], BUFFER_SIZE) > 0)
	{
		line = ft_strjoin(line, cursor[fd]);
		if (ft_len(cursor[fd]) == 0)
			return (line);
		if (ft_clean(cursor[fd]) == 1)
			break ;
		if (read(fd, cursor[fd], 0) < 0)
		{
			free (line);
			return (NULL);
		}
	}
	return (line);
}

static size_t	ft_len(const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	return (i);
}

static char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		v;
	char	*newstr;

	i = 0;
	v = 0;
	newstr = malloc(ft_len(s1) + ft_len(s2) + 1);
	if (!newstr)
		return (NULL);
	while (s1 && s1[v])
		newstr[i++] = s1[v++];
	v = 0;
	while (s2 && s2[v])
	{
		newstr[i] = s2[v++];
		if (newstr[i++] == '\n')
			break ;
	}
	newstr[i] = '\0';
	free (s1);
	return (newstr);
}

static int	ft_clean(char *str)
{
	int	i;
	int	j;
	int	is_nwl;

	i = 0;
	j = 0;
	is_nwl = 0;
	while (str[i])
	{
		if (is_nwl)
			str[j++] = str[i];
		if (str[i] == '\n')
			is_nwl = 1;
		str[i] = '\0';
		i++;
	}
	return (is_nwl);
}
