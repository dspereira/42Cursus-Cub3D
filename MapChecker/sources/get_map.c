#include "../includes/header.h"

static int	is_line_empty(char *line);
static int  get_map_nbr_lines(char **cont, int begin);
static char *get_map_line(char *src);
static int  get_index(char **cont, int begin);

t_map   *get_map(char **content, int map_begin_line)
{
    t_map   *map;
    int     i;
    int     j;
    int     map_nbr_lines;

    i = get_index(content, map_begin_line);
    map = ft_calloc(1, sizeof(t_map));
    if (!map)
        return (NULL);
    map_nbr_lines = get_map_nbr_lines(content, i);
    map->content = ft_calloc(map_nbr_lines + 1, sizeof(char *));
    j = -1;
    while (++j < map_nbr_lines)
    {
        map->content[j] = get_map_line(content[i]);
        if (!map->content[j])
        {
            free_map(map);
            return (NULL);
        }
        i++;
    }
    return (map);
}

void    free_map(t_map *map)
{
    int i;

    i = 0;
    while (map->content[i])
    {
        free(map->content[i]);
        i++;
    }
    if (map->content)
        free(map->content);
    free(map);
}

static int	is_line_empty(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '\n')
	{
		if (!((line[i] >= 9 && line[i] <= 13) || line[i] == 32))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

static int  get_map_nbr_lines(char **cont, int begin)
{
    int i;
    int map_nbr_lines;

    i = begin;
    map_nbr_lines = 0;
    while (cont[i])
    {
        if (is_line_empty(cont[i]) && map_nbr_lines != 0)
            break;
        else if (!is_line_empty(cont[i]))
            map_nbr_lines += 1;
        i++;
    }
    return (map_nbr_lines);
}

static char *get_map_line(char *src)
{
    int     i;
    int     len;
    char    *result;

    i = 0;
    len = 0;
    if (!src)
        return (NULL);
    while (src[len] && src[len] != '\n')
        len++;
    result = ft_calloc(len + 1, sizeof(char));
    if (!result)
        return (NULL);
    while (src[i] != '\n' && src[i])
    {
        result[i] = src[i];
        i++;
    }
    return (result);
}

static int  get_index(char **cont, int begin)
{
    int i;

    i = begin;
    while (is_line_empty(cont[i]) && cont[i])
        i++;
    return (i);
}
