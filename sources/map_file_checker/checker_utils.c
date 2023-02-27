/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcandeia < dcandeia@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 15:53:45 by dcandeia          #+#    #+#             */
/*   Updated: 2023/02/24 16:32:53 by dcandeia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void	*ft_memset(void *s, int c, size_t len);

void	*ft_calloc(size_t count, size_t size)
{
	void	*defmalloc;

	defmalloc = malloc(count * size);
	if (!defmalloc)
		return (NULL);
	ft_memset(defmalloc, '\0', (count * size));
	return (defmalloc);
}

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;

	i = 0;
	if (n == 0)
		return (0);
	while (i < n && s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	if (i == n)
		i--;
	return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
}

static void	*ft_memset(void *s, int c, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		((unsigned char *)s)[i] = c;
		i++;
	}
	return (s);
}
