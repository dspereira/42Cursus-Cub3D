#include "../includes/header.h"

static int	is_line_empty(char *line);

t_textures	*get_file_textures(char **content)
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
	tex_count = 0;
	i = 0;
	while (tex_count < 6 && content[i])
	{
		if (is_line_empty(content[i]))
			i++;
		if (content[i][0] == 'C')
			tex[TEX_C].colour = ;
		else if (content[i][0] == 'F')
			tex[TEX_F].colour = ;
		else
			break ;
	}
	
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