/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohouhou <mohouhou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 17:40:54 by mohouhou          #+#    #+#             */
/*   Updated: 2023/08/19 17:42:54 by mohouhou         ###   ########.fr       */
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
	free_2d_array_char(tmp);
	return (0);
}

int	check_coordinates_float(char *array)
{
	char	**tmp;
	char	**tmp2;
	int		i;

	tmp2 = ft_split(array, '\n');
	tmp = ft_split(tmp2[0], ',');
	i = 0;
	while (tmp[i])
	{
		if (check_float(tmp[i]))
		{
			free_2d_array_char(tmp);
			free_2d_array_char(tmp2);
			return (1);
		}
		i++;
	}
	free_2d_array_char(tmp);
	free_2d_array_char(tmp2);
	return (0);
}

int	check_ambient_error(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	if (i != 3)
		return (1);
	if (check_float(array[1]))
		return (1);
	if (check_coordinates_float(array[2]))
		return (1);
	return (0);
}

int	check_light_error(char **array)
{
	int		i;

	i = 0;
	while (array[i])
		i++;
	if (i != 4)
		return (1);
	if (check_float(array[2]))
		return (1);
	if (check_coordinates_float(array[1]))
		return (1);
	if (check_coordinates_float(array[3]))
		return (1);
	return (0);
}
