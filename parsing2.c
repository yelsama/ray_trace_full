/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohouhou <mohouhou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 18:10:53 by mohouhou          #+#    #+#             */
/*   Updated: 2023/08/20 23:37:23 by mohouhou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytrace.h"

void	norm_a_vector(t_tuple *vec)
{
	(void)vec;
}

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
	int	i;

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
	char	**tmp;

	alive->ambient.brightness = ft_atof(str[1]);
	tmp = ft_split(str[2], ',');
	alive->ambient.color.red = ft_atof(tmp[0]);
	alive->ambient.color.green = ft_atof(tmp[1]);
	alive->ambient.color.blue = ft_atof(tmp[2]);
	free_2d_array_char(str);
}

void	fill_camera(t_ranger *alive, char **str)
{
	char	**tmp;

	alive->cam.field_of_view = ft_atof(str[3]);
	tmp = ft_split(str[1], ',');
	alive->cam.location.w = 1;
	alive->cam.location.x = ft_atof(tmp[0]);
	alive->cam.location.y = ft_atof(tmp[1]);
	alive->cam.location.z = ft_atof(tmp[2]);
	free_2d_array_char(tmp);
	tmp = ft_split(str[2], ',');
	alive->cam.look_forward.w = 0;
	alive->cam.look_forward.x = ft_atof(tmp[0]);
	alive->cam.look_forward.y = ft_atof(tmp[1]);
	alive->cam.look_forward.z = ft_atof(tmp[2]);
	norm_a_vector(&alive->cam.look_forward);
	free_2d_array_char(tmp);
}
