/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymohamed <ymohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 22:19:03 by ymohamed          #+#    #+#             */
/*   Updated: 2023/08/24 08:28:30 by ymohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytrace.h"

static void	free_line(char **line)
{
	free(*line);
	*line = NULL;
}

static int	dot_errors(char *line, int i)
{
	if (!ft_isdigit(line[i - 1])
		|| !ft_isdigit(line[i + 1]))
		return (1);
	i++;
	while (line[i] && ft_isdigit(line[i]))
		i++;
	if (line[i] == '.')
		return (1);
	return (0);
}

static int	check_line(char *line)
{
	int	i;
	int	err;

	i = 0;
	err = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (!line[i] || line[i] == '\n' || line[i] == '#')
		return (0);
	if (!ft_isdigit(line[i]) && !ft_strchr("\n\t ,.-+ACLcypls", line[i]))
		err++;
	i = 1;
	while (line[i] && !err)
	{
		if (!ft_isdigit(line[i]) && !ft_strchr("\n\t ,.-+ACLcypls", line[i]))
			err++;
		else if (line[i] == '.')
			err = dot_errors(line, i);
		else if (line[i] == ',' && (!ft_isdigit(line[i - 1])
				|| (!ft_isdigit(line[i + 1]) && line[i + 1] != '-'
					&& line[i + 1] != '+')))
			err++;
		i++;
	}
	return (err);
}

static void	contents_check(char *file)
{
	int		fd;
	char	*line;
	int		err;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		ft_printf("Error\nIvalid Dirctory");
		exit (0);
	}
	err = 0;
	line = get_next_line(fd);
	while (line)
	{
		err += check_line(line);
		if (line)
			free_line(&line);
		line = get_next_line(fd);
	}
	close(fd);
	if (err)
	{
		ft_printf("Error invalid format\n");
		exit (0);
	}
}

void	exam_the_map_file(char *file, char *extention)
{
	char	*name_ext;

	if (!file || file[0] == 0)
	{
		ft_printf("Error\nIvalid Dirctory");
		exit (0);
	}
	name_ext = ft_strrchr(file, '.');
	if (!name_ext)
	{
		ft_printf("Error\nIvalid Dirctory");
		exit (0);
	}
	if (ft_strlen(name_ext) != 3 || ft_strlen(file) < 4)
	{
		ft_printf("Error\nIvalid extention\n");
		exit (0);
	}
	if (ft_strncmp(extention, name_ext, 3))
	{
		ft_printf("Error\nIvalid extention\n");
		exit (0);
	}
	contents_check(file);
}
