/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohouhou <mohouhou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 01:10:32 by mohouhou          #+#    #+#             */
/*   Updated: 2023/08/21 01:59:55 by mohouhou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytrace.h"

int	check_camera_error(char **array)
{
	int		i;
	char	**tmp;

	i = 0;
	while (array[i])
		i++;
	if (i != 4)
		return (1);
	--i;
	if (ft_strncmp(array[i], "\n", 1) == 0)
		return (1);
	tmp = ft_split(array[3], '\n');
	free(array[3]);
	array[3] = ft_strdup(tmp[0]);
	free_2d_array_char(tmp);
	if (check_float(array[3]))
		return (1);
	if (check_coordinates_float(array[1]))
		return (1);
	if (check_coordinates_float(array[2]))
		return (1);
	return (0);
}

int	check_plane_error(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	if (i != 4)
		return (1);
	--i;
	if (ft_strncmp(array[i], "\n", 1) == 0)
		return (1);
	if (check_coordinates_float(array[1]))
		return (1);
	if (check_coordinates_float(array[2]))
		return (1);
	if (check_coordinates_float(array[3]))
		return (1);
	return (0);
}

int	check_sphere_error(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	if (i != 4)
		return (1);
	--i;
	if (ft_strncmp(array[i], "\n", 1) == 0)
		return (1);
	if (check_float(array[2]))
		return (1);
	if (check_coordinates_float(array[1]))
		return (1);
	if (check_coordinates_float(array[3]))
		return (1);
	return (0);
}

int	check_cylinder_error(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	if (i != 6)
		return (1);
	--i;
	if (ft_strncmp(array[i], "\n", 1) == 0)
		return (1);
	if (check_coordinates_float(array[1]))
		return (1);
	if (check_coordinates_float(array[2]))
		return (1);
	if (check_float(array[3]))
		return (1);
	if (check_float(array[4]))
		return (1);
	if (check_coordinates_float(array[5]))
		return (1);
	return (0);
}

int	check_values(char ***argsex, int l)
{
	int	i;

	i = -1;
	while (++i < l)
	{
		if (ft_strncmp(argsex[i][0], "A", 1) == 0)
			if (check_ambient_error(argsex[i]))
				return (1);
		if (ft_strncmp(argsex[i][0], "L", 1) == 0)
			if (check_light_error(argsex[i]))
				return (1);
		if (ft_strncmp(argsex[i][0], "C", 1) == 0)
			if (check_camera_error(argsex[i]))
				return (1);
		if (ft_strncmp(argsex[i][0], "pl", 2) == 0)
			if (check_plane_error(argsex[i]))
				return (1);
		if (ft_strncmp(argsex[i][0], "sp", 2) == 0)
			if (check_sphere_error(argsex[i]))
				return (1);
		if (ft_strncmp(argsex[i][0], "cy", 2) == 0)
			if (check_cylinder_error(argsex[i]))
				return (1);
	}
	return (0);
}
