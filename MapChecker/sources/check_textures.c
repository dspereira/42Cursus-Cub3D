#include "../includes/header.h"

static int  check_tex_files(char *filename);

int check_textures(t_textures *tex)
{
    if (!check_tex_files(tex[TEX_NO].path) || !check_tex_files(tex[TEX_SO].path)
        || !check_tex_files(tex[TEX_WE].path) ||!check_tex_files(tex[TEX_EA].path))
    {
        free_textures(tex);
        return (FALSE);
    }
    return (TRUE);
}

void    free_textures(t_textures *tex)
{
    int i;

    i = 0;
    while (i < 4)
    {
        if (tex[i].path)
            free(tex[i].path);
        i++;
    }
    free(tex);
}

static int  check_tex_files(char *filename)
{
    int fd;

    if (!filename)
        return (FALSE);
    fd = open(filename, O_RDONLY);
    if (fd == -1)
        return (FALSE);
    close(fd);
    return (TRUE);
}