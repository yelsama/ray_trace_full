/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_vectors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymohamed <ymohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 23:07:41 by ymohamed          #+#    #+#             */
/*   Updated: 2023/08/24 05:31:10 by ymohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytrace.h"

static int	is_normalized(t_tuple v)
{
	if (vec_mag(&v) < 0.99 || vec_mag(&v) > 1.01)
		return (0);
	return (1);
}

static int	errocheck_plane(t_plane *plane)
{
	if (!is_normalized(plane->normal_v))
	{
		ft_printf("Error\nPlane vector is not normalized\n");
		return (1);
	}
	if (plane->color.red < 0 || plane->color.red > 255
		|| plane->color.green < 0 || plane->color.green > 255
		|| plane->color.blue < 0 || plane->color.blue > 255)
	{
		ft_printf("Error\nPlane color is not in range [0, 255]\n");
		return (1);
	}
	return (0);
}

static int	errocheck_cylindr(t_cylndr *cylinder)
{
	if (!is_normalized(cylinder->vec))
	{
		ft_printf("Error\nCylinder vector is not normalized\n");
		return (1);
	}
	if (cylinder->color.red < 0 || cylinder->color.red > 255
		|| cylinder->color.green < 0 || cylinder->color.green > 255
		|| cylinder->color.blue < 0 || cylinder->color.blue > 255)
	{
		ft_printf("Error\nCylinder color is not in range [0, 255]\n");
		return (1);
	}
	if (cylinder->rad <= 0 || cylinder->height <= 0)
	{
		ft_printf("Error\nCylinder radius or height is negative or zero\n");
		return (1);
	}
	return (0);
}

static int	errocheck_sphere(t_sphere *sphere)
{
	if (sphere->color.red < 0 || sphere->color.red > 255
		|| sphere->color.green < 0 || sphere->color.green > 255
		|| sphere->color.blue < 0 || sphere->color.blue > 255)
	{
		ft_printf("Error\nSphere color is not in range [0, 255]\n");
		return (1);
	}
	if (sphere->rad <= 0)
	{
		ft_printf("Error\nSphere radius is negative or zero\n");
		return (1);
	}
	return (0);
}

void	check_vectors(t_ranger *alive)
{
	int	i;
	int	err;

	i = -1;
	err = 0;
	if (!is_normalized(alive->cam.look_forward))
		err = ft_printf("Error\nCamera look vector is not normalized\n");
	if (alive->cam.field_of_view <= 0 || alive->cam.field_of_view >= 180)
		err = ft_printf("Error\nCamera fov is not in range (0, 180)\n");
	while (++i < alive->no_of_object && !err)
	{
		if (alive->objcs[i].obj_type == plane)
			err = errocheck_plane((t_plane *)alive->objcs[i].the_obj);
		else if (alive->objcs[i].obj_type == cylinder)
			err = errocheck_cylindr((t_cylndr *)alive->objcs[i].the_obj);
		else if (alive->objcs[i].obj_type == sphere)
			err = errocheck_sphere((t_sphere *)alive->objcs[i].the_obj);
	}
	if (err)
	{
		free_objects(alive);
		exit (0);
	}
}
