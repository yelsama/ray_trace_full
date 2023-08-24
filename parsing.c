/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymohamed <ymohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 16:43:12 by mohouhou          #+#    #+#             */
/*   Updated: 2023/08/24 20:13:44 by ymohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytrace.h"

void	initiate_params(t_ranger *alive)
{
	alive->am = 0;
	alive->ca = 0;
	alive->li = 0;
	alive->pl = 0;
	alive->sp = 0;
	alive->cy = 0;
}

void	check_numbers(char ***argsex, t_ranger *alive, int l)
{
	int	i;

	i = -1;
	initiate_params(alive);
	while (++i < l)
	{
		if (!argsex[i][0])
			continue ;
		if (ft_strncmp(argsex[i][0], "A", 2) == 0)
			alive->am++;
		else if (ft_strncmp(argsex[i][0], "C", 2) == 0)
			alive->ca++;
		else if (ft_strncmp(argsex[i][0], "L", 2) == 0)
			alive->li++;
		else if (ft_strncmp(argsex[i][0], "pl", 3) == 0)
			alive->pl++;
		else if (ft_strncmp(argsex[i][0], "sp", 3) == 0)
			alive->sp++;
		else if (ft_strncmp(argsex[i][0], "cy", 3) == 0)
			alive->cy++;
		else if (argsex[i][0][0] <= 32)
			;
		else
			wrong_inputs(argsex);
	}
}

void	check_for_errors(t_ranger *alive, char ***argsex, int l)
{
	initiate_params2(alive);
	if (alive->am > 1 || alive->am == 0 || alive->ca > 1 
		|| alive->ca == 0 || alive->li > 1 || alive->li == 0)
	{
		wrong_inputs(argsex);
	}
	if (check_values(argsex, l))
		wrong_inputs(argsex);
	if (alive->sp > 0)
		alive->s = malloc(sizeof(t_sphere) * (alive->sp));
	if (alive->pl > 0)
		alive->p = malloc(sizeof(t_plane) * alive->pl);
	if (alive->cy > 0)
		alive->c = malloc(sizeof(t_cylndr) * (alive->cy));
	alive->no_of_object = alive->pl + alive->sp + alive->cy;
	if (alive->no_of_object > 0)
		alive->objcs = malloc(sizeof(t_objcs_list) * alive->no_of_object);
}

void	fill(char ***argsex, t_ranger *alive, int l)
{
	int	i;

	i = -1;
	check_numbers(argsex, alive, l);
	check_for_errors(alive, argsex, l);
	initiate_params(alive);
	alive->obj_index = 0;
	while (++i < l)
	{
		if (!argsex[i][0])
			continue ;
		if (ft_strncmp(argsex[i][0], "A", 1) == 0)
			fill_ambient(alive, argsex[i]);
		else if (ft_strncmp(argsex[i][0], "C", 1) == 0)
			fill_camera(alive, argsex[i]);
		else if (ft_strncmp(argsex[i][0], "L", 1) == 0)
			fill_light(alive, argsex[i]);
		else if (ft_strncmp(argsex[i][0], "pl", 2) == 0)
			fill_plane2(alive, argsex[i]);
		else if (ft_strncmp(argsex[i][0], "sp", 2) == 0)
			fill_sphere2(alive, argsex[i]);
		else if (ft_strncmp(argsex[i][0], "cy", 2) == 0)
			fill_cylinder2(alive, argsex[i]);
	}
}

int	parsing(t_ranger *alive, char **av)
{
	int		l;
	char	**args;
	int		i;
	int		fd;
	char	***argsex;

	i = -1;
	l = read_width(av[1]);
	args = (char **)malloc(sizeof(char *) * (l + 1));
	fd = open(av[1], O_RDONLY);
	while (++i < l)
	{
		args[i] = get_next_line(fd);
		args[i] = change_spaces(args[i]);
	}
	args[i] = 0;
	close(fd);
	argsex = (char ***)malloc(sizeof(char **) * (i + 1));
	i = -1;
	while (args[++i])
		argsex[i] = ft_split(args[i], ' ');
	argsex[i] = 0;
	free_2d_array_char(args);
	fill(argsex, alive, l);
	free_3d_char(argsex);
	return (0);
}
