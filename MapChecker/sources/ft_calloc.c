#include "../includes/header.h"

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