#include "../includes/header.h"

static int	get_file_nbr_lines(const char *filename);
static char	**get_file_content(const char *file, int file_nbr_lines);

t_file	*get_file_info(const char *filename)
{
	t_file	*newfile;

	newfile = malloc(sizeof(t_file));
	if (!newfile)
	{
		print_error_msg("Impossible to alloc memory");
		return (NULL);
	}
	newfile->filename = (char *)filename;
	newfile->nbr_lines = get_file_nbr_lines(filename);
	newfile->content = get_file_content(filename, newfile->nbr_lines);
	return (newfile);
}

static int	get_file_nbr_lines(const char *filename)
{
	char	*str;
	int		nbr_lines;
	int		fd;

	nbr_lines = 0;
	fd = open(filename, O_RDONLY);
	if (!fd)
	{
		print_error_msg("Impossible to read from File");
		return (0);
	}
	str = get_next_line(fd);
	while (str)
	{
		free(str);
		str = get_next_line(fd);
		nbr_lines += 1;
	}
	close(fd);
	return (nbr_lines);
}

static char	**get_file_content(const char *file, int file_nbr_lines)
{
	char	**resource;
	int		fd;
	int		i;

	resource = ft_calloc(file_nbr_lines + 1, sizeof(char *));
	if (!resource)
	{
		print_error_msg("Impossible to allocate memory");
		return (NULL);
	}
	fd = open(file, O_RDONLY);
	if (!fd)
	{
		print_error_msg("Impossible to allocate memory");
		return (NULL);
	}
	i = 0;
	while(i < file_nbr_lines)
	{
		resource[i] = get_next_line(fd);
		i++;
	}
	return (resource);
}
