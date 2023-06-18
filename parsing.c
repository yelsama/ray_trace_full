/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohouhou <mohouhou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 16:43:12 by mohouhou          #+#    #+#             */
/*   Updated: 2023/06/18 18:14:14 by mohouhou         ###   ########.fr       */
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

void	fill_ambient(t_ranger *alive, char **str)
{
	
}

void	fill_camera(t_ranger *alive, char **str)
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