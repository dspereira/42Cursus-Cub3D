#include "../includes/header.h"

int 		get_rgb_colour(char *src, int *tex_count, int actual_colour);
static int	is_line_empty(char *line);
static char	*get_texture_path(char *src, int *tex_counter, char *actpath);

t_textures	*get_file_textures(char **content, int *tex_line_end)
{
	t_textures	*tex;
	int			tex_count;
	int			i;

	tex = ft_calloc(6, sizeof(t_textures));
	if (!tex)
	{
		print_error_msg("Impossible to Aloc Memory");
		return (NULL);
	}
	tex[TEX_C].colour = -1;
	tex[TEX_F].colour = -1;
	tex_count = 0;
	i = 0;
	while (tex_count < 6 && content[i])
	{
		if (is_line_empty(content[i]))
			i++;
		if (!ft_strncmp(content[i], "NO", 2))
			tex[TEX_NO].path = get_texture_path(content[i], &tex_count, tex[TEX_NO].path);
		else if (!ft_strncmp(content[i], "SO", 2))
			tex[TEX_SO].path = get_texture_path(content[i], &tex_count, tex[TEX_SO].path);
		else if (!ft_strncmp(content[i], "WE", 2))
			tex[TEX_WE].path = get_texture_path(content[i], &tex_count, tex[TEX_WE].path);
		else if (!ft_strncmp(content[i], "EA", 2))
			tex[TEX_EA].path = get_texture_path(content[i], &tex_count, tex[TEX_EA].path);
		else if (content[i][0] == 'C')
			tex[TEX_C].colour = get_rgb_colour(content[i], &tex_count, tex[TEX_C].colour);
		else if (content[i][0] == 'F')
			tex[TEX_F].colour = get_rgb_colour(content[i], &tex_count, tex[TEX_F].colour);
		i++;
	}
	*tex_line_end = i;
	return (tex);
}

static int	is_line_empty(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\n')
	{
		if (!((line[i] >= 9 && line[i] <= 13) || line[i] == 32))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

static char	*get_texture_path(char *src, int *tex_counter, char *actpath)
{
	int		i;
	int		len;
	char	*path;

	i = 2;
	if (actpath)
		return (actpath);
	while ((src[i] >= 9 && src[i] <= 13) || src[i] == 32)
		i++;
	len = i;
	while (src[len] != '\n')
		len++;
	path = ft_calloc(len - i + 1, sizeof(char));
	if (!path)
		return (NULL);
	len = 0;
	while (src[i] != '\n')
		path[len++] = src[i++];
	*tex_counter += 1;
	return (path);
}
