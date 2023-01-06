#include "../includes/header.h"

static void free_file(t_file *file);
static void free_textures(t_textures *tex);
static void free_map(t_map *map);

void	free_memory(t_file *file)
{
    if (file)
    {
        free_map(file->map);
        free_textures(file->tex);
        free_file(file);
    }
}

static void free_file(t_file *file)
{
	int	i;

	i = 0;
	while (i < file->nbr_lines)
	{
		if (file->content[i])
			free(file->content[i]);
		i++;
	}
	free(file->content);
	free(file);
}

static void free_textures(t_textures *tex)
{
    int i;

    i = 0;
    if (!tex)
        return ;
    while (i < 4)
    {
        if (tex[i].path)
            free(tex[i].path);
        i++;
    }
    free(tex);
}

static void free_map(t_map *map)
{
    int i;

    i = 0;
    if (!map)
        return ;
    while (map->content[i])
    {
        free(map->content[i]);
        i++;
    }
    if (map->content)
        free(map->content);
    free(map);
}
