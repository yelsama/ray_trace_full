/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohouhou <mohouhou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 16:43:12 by mohouhou          #+#    #+#             */
/*   Updated: 2023/06/27 20:51:42 by mohouhou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytrace.h"

int	read_width(char *strt)
{
	int		fd;
	char	*str;
	int		i;

	i = 0;
	str = NULL;
	fd = open(strt, O_RDONLY);
	while (1)
	{
		str = get_next_line(fd);
		if (str == NULL)
			break ;
		free(str);
		i++;
	}
	close(fd);
	return (i);
}

void	free_2d_array_char(char **str)
{
	int i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	fill_ambient(t_ranger *alive, char **str)
{
	char **tmp;
	
	
	alive->ambient.brightness = ft_atof(str[1]);
	tmp = ft_split(str[2],',');
	alive->ambient.color.red = ft_atof(tmp[0]);
	alive->ambient.color.green = ft_atof(tmp[1]);
	alive->ambient.color.blue = ft_atof(tmp[2]);
	free_2d_array_char(str);
	
}

void	fill_camera(t_ranger *alive, char **str)
{
	
}

void	fill_light(t_ranger *alive, char **str)
{
	
}

void	fill_plane2(t_ranger *alive, char **str)
{
	
}

void	fill_sphere2(t_ranger *alive, char **str)
{
	
}

void	fill_cylinder2(t_ranger *alive, char **str)
{
	
}

void	fill(char ***argsex, t_ranger *alive, int l)
{
	int	i;

	i = 0;
	while (i < l)
	{
		if ( ft_strncmp(argsex[i][0],"A",1) == 0)
			fill_ambient(alive,argsex[i]);
		else if ( ft_strncmp(argsex[i][0],"C",1) == 0)
			fill_camera(alive, argsex[i]);
		else if ( ft_strncmp(argsex[i][0],"L",1) == 0)
			fill_light(alive, argsex[i]);
		else if ( ft_strncmp(argsex[i][0],"pl",2) == 0)
			fill_plane2(alive, argsex[i]);
		else if ( ft_strncmp(argsex[i][0],"sp",2) == 0)
			fill_sphere2(alive, argsex[i]);
		else if ( ft_strncmp(argsex[i][0],"cy",2) == 0)
			fill_cylinder2(alive, argsex[i]);
			 
	}
}

int	parsing(t_ranger *alive, char **av)
{
	int	l;
	char	**args;
	int	i;
	int	fd;
	char	***argsex;

	l = read_width(av[1]);
	args = (char**)malloc(sizeof(char*)*(l + 1));
	fd = open(av[1], O_RDONLY);
	while (i < l)
	{
		args[i] = get_next_line(fd);
		i++;
	}
	args[i] = 0;
	close(fd);
	argsex = (char***)malloc(sizeof(char**) * (i + 1));
	i = 0;
	while(args[i])
	{
		argsex[i] = ft_split(args[i],' ');
		i++;
	}
	fill(argsex, alive, l);
}