/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohouhou <mohouhou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 01:10:32 by mohouhou          #+#    #+#             */
/*   Updated: 2023/08/19 03:15:43 by mohouhou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytrace.h"

int	check_float(char *array)
{
	char	**tmp;
	int		i;
	int		x;

	i = 0;
	x = 0;
	tmp = ft_split(array, '.');
	while (tmp[i])
	{
		x = 0;
		while (tmp[i][x])
		{
			if (x == 0 && i == 0 && (tmp[i][x] == '-' || tmp[i][x] == '+'))
				;
			else if (ft_isdigit(tmp[i][x]) == 0)
			{
				free_2d_array_char(tmp);
				return (1);
			}
			x++;
		}
		i++;
	}
	return (0);
}

int	check_ambient_error(char **array)
{
	int		i;
	char	**tmp;
	char	**tmp2;

	i = 0;
	while (array[i])
		i++;
	if (i != 3)
		return (1);
	if (check_float(array[1]))
		return (1);
	tmp2 = ft_split(array[2], '\n');
	tmp = ft_split(tmp2[0], ',');
	i = 0;
	while (tmp[i])
	{
		if (check_float(tmp[i]))
			return (1);
		i++;
	}
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
		// if (ft_strncmp(argsex[i][0], "L", 1) == 0)
		// 	if (check_light_error(argsex[i]))
		// 		return (1);
		// if (ft_strncmp(argsex[i][0], "C", 1) == 0)
		// 	if (check_camera_error(argsex[i]))
		// 		return (1);
		// if (ft_strncmp(argsex[i][0], "pl", 2) == 0)
		// 	if (check_plane_error(argsex[i]))
		// 		return (1);
		// if (ft_strncmp(argsex[i][0], "sp", 2) == 0)
		// 	if (check_sphere_error(argsex[i]))
		// 		return (1);
		// if (ft_strncmp(argsex[i][0], "cy", 2) == 0)
		// 	if (check_cylinder_error(argsex[i]))
		// 		return (1);
	}
	return (0);
}
