/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohouhou <mohouhou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 18:14:42 by mohouhou          #+#    #+#             */
/*   Updated: 2023/08/19 20:09:33 by mohouhou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytrace.h"

void	fill_light(t_ranger *alive, char **str)
{
	char	**tmp;

	alive->main_light.brightness = ft_atof(str[2]);
	tmp = ft_split(str[1], ',');
	alive->main_light.position.w = 1;
	alive->main_light.position.x = ft_atof(tmp[0]);
	alive->main_light.position.y = ft_atof(tmp[1]);
	alive->main_light.position.z = ft_atof(tmp[2]);
	free_2d_array_char(tmp);
	tmp = ft_split(str[3], ',');
	alive->main_light.color.red = ft_atof(tmp[0]);
	alive->main_light.color.green = ft_atof(tmp[1]);
	alive->main_light.color.blue = ft_atof(tmp[2]);
	free_2d_array_char(tmp);
}

void	fill_plane2(t_ranger *alive, char **str)
{
	char	**tmp;

	tmp = ft_split(str[1], ',');
	alive->p[alive->pl].c_point.w = 1;
	alive->p[alive->pl].c_point.x = ft_atof(tmp[0]);
	alive->p[alive->pl].c_point.y = ft_atof(tmp[1]);
	alive->p[alive->pl].c_point.z = ft_atof(tmp[2]);
	free_2d_array_char(tmp);
	tmp = ft_split(str[2], ',');
	alive->p[alive->pl].normal_v.w = 0;
	alive->p[alive->pl].normal_v.x = ft_atof(tmp[0]);
	alive->p[alive->pl].normal_v.y = ft_atof(tmp[1]);
	alive->p[alive->pl].normal_v.z = ft_atof(tmp[2]);
	norm_a_vector(&alive->p[alive->pl].normal_v);
	free_2d_array_char(tmp);
	tmp = ft_split(str[3], ',');
	alive->p[alive->pl].color.red = ft_atof(tmp[0]);
	alive->p[alive->pl].color.green = ft_atof(tmp[1]);
	alive->p[alive->pl].color.blue = ft_atof(tmp[2]);
	free_2d_array_char(tmp);
	alive->objcs[alive->obj_index].obj_id = alive->obj_index;
	alive->objcs[alive->obj_index].obj_type = plane;
	alive->objcs[alive->obj_index].the_obj = &alive->p[alive->pl];
	alive->pl++;
	alive->obj_index++;
}

void	fill_sphere2(t_ranger *alive, char **str)
{
	char	**tmp;

	tmp = ft_split(str[1], ',');
	alive->s[alive->sp].cent.w = 1;
	alive->s[alive->sp].cent.x = ft_atof(tmp[0]);
	alive->s[alive->sp].cent.y = ft_atof(tmp[1]);
	alive->s[alive->sp].cent.z = ft_atof(tmp[2]);
	free_2d_array_char(tmp);
	tmp = ft_split(str[3], ',');
	alive->s[alive->sp].color.red = ft_atof(tmp[0]);
	alive->s[alive->sp].color.green = ft_atof(tmp[1]);
	alive->s[alive->sp].color.blue = ft_atof(tmp[2]);
	alive->s[alive->sp].rad = ft_atof(str[2]) / 2;
	free_2d_array_char(tmp);
	alive->objcs[alive->obj_index].obj_id = alive->obj_index;
	alive->objcs[alive->obj_index].obj_type = sphere;
	alive->objcs[alive->obj_index].the_obj = &alive->s[alive->sp];
	alive->sp++;
	alive->obj_index++;
}

void	fill_cylinder2(t_ranger *alive, char **str)
{
	char			**tmp;

	tmp = ft_split(str[1], ',');
	alive->c[alive->cy].cnt.w = 1;
	alive->c[alive->cy].cnt.x = ft_atof(tmp[0]);
	alive->c[alive->cy].cnt.y = ft_atof(tmp[1]);
	alive->c[alive->cy].cnt.z = ft_atof(tmp[2]);
	free_2d_array_char(tmp);
	tmp = ft_split(str[2], ',');
	alive->c[alive->cy].vec.w = 0;
	alive->c[alive->cy].vec.x = ft_atof(tmp[0]);
	alive->c[alive->cy].vec.y = ft_atof(tmp[1]);
	alive->c[alive->cy].vec.z = ft_atof(tmp[2]);
	norm_a_vector(&alive->c[alive->cy].vec);
	free_2d_array_char(tmp);
	alive->c[alive->cy].rad = (ft_atof(str[3]) / 2.0);
	alive->c[alive->cy].height = ft_atof(str[4]);
	tmp = ft_split(str[5], ',');
	alive->c[alive->cy].color.red = ft_atoi(tmp[0]);
	alive->c[alive->cy].color.green = ft_atoi(tmp[1]);
	alive->c[alive->cy].color.blue = ft_atoi(tmp[2]);
	free_2d_array_char(tmp);
	fill_cylinder22(alive);
}

void	free_3d_char(char ***array)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (array[x])
	{
		y = 0;
		while (array[x][y])
			free (array[x][y++]);
		free (array[x++]);
	}
	free (array);
}
