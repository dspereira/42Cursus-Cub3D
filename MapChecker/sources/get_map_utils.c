#include "../includes/header.h"

static int find_big_line_len(char **src);
static char *resize_line(char *src, int max_len);

void    resize_map(t_map  *initital_map)
{
    int big_len;
    int i;

    big_len = find_big_line_len(initital_map->content);
    i = 0;
    while (initital_map->content[i])
    {
        if (ft_strlen(initital_map->content[i]) < (size_t)big_len)
            initital_map->content[i] = resize_line(initital_map->content[i], big_len);
        i++;
    }
}

static int find_big_line_len(char **src)
{
    int len;
    int i;
    int j;

    len = 0;
    i = 0;
    while (src[i])
    {
        j = 0;
        while (src[i][j])
            j++;
        if (j > len)
            len = j;
        i++;
    }
    return (len);
}

static char *resize_line(char *src, int max_len)
{
    char    *dst;
    int     i;

    if (!src)
        return (NULL);
    dst = ft_calloc(max_len + 1, sizeof(char));
    i = -1;
    if (!dst)
    {
        free(src);
        return (NULL);
    }
    while (src[++i])
        dst[i] = src[i];
    while (i < max_len)
        dst[i++] = ' ';
    free(src);
    return (dst);
}
