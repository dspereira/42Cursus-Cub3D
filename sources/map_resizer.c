#include "../includes/header.h"

int         find_big_line_len(char **src);
int         get_map_size(char **map);
static char	*resize_line(char *src, int max_len);
static char *fill_first_last_line(int len);

void	map_resizer(char ***src)
{
    char    **res;
	int	    big_len;
	int	    i;

	big_len = find_big_line_len(*src);
	i = 0;
    if (get_map_size(*src) < 3)
        return ;
    res = ft_calloc(get_map_size(*src) + 3, sizeof(char *));
    res[0] = fill_first_last_line(big_len);
	while (++i < get_map_size(*src))
		res[i] = resize_line((*src)[i], big_len);
    res[i] = fill_first_last_line(big_len);
    *src = res;
}

static char	*resize_line(char *src, int max_len)
{
	char	*dst;
	int		i;

	if (!src)
		return (NULL);
	dst = ft_calloc(max_len + 3, sizeof(char));
	i = 0;
	if (!dst)
	{
		free(src);
		return (NULL);
	}
    dst[0] = ' ';
	while (src[++i])
		dst[i] = src[i];
	while (i < max_len + 1)
		dst[i++] = ' ';
	free(src);
	return (dst);
}

static char *fill_first_last_line(int len)
{
    char    *res;
    int     i;

    res = ft_calloc(len + 3, sizeof(char));
    i = 0;
    while (i < len + 1)
    {
        res[i] = ' ';
        i++;
    }
    return (res);
}
