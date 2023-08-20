/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_vectors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymohamed <ymohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 23:07:41 by ymohamed          #+#    #+#             */
/*   Updated: 2023/08/20 23:27:12 by ymohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytrace.h"

static int	is_normalized(t_tuple v)
{
	if (vec_mag(&v) < 0.99 || vec_mag(&v) > 1.01)
		return (0);
	return (1);
}

static void	check_plane_vector(t_plane *plane, t_ranger *alive)
{
	if (!is_normalized(plane->normal_v))
	{
		ft_printf("Error\nPlane vector is not normalized\n");
		free_objects(alive);
		exit (0);
	}
}

static void	check_cylinder_vector(t_cylndr *cylinder, t_ranger *alive)
{
	if (!is_normalized(cylinder->vec))
	{
		ft_printf("Error\nCylinder vector is not normalized\n");
		free_objects(alive);
		exit (0);
	}
}

void	check_vectors(t_ranger *alive)
{
	int	i;

	i = -1;
	if (!is_normalized(alive->cam.look_forward))
	{
		ft_printf("Error\nCamera look vector is not normalized\n");
		free_objects(alive);
		exit (0);
	}
	while (++i < alive->no_of_object)
	{
		if (alive->objcs[i].obj_type == plane)
			check_plane_vector((t_plane *)alive->objcs[i].the_obj, alive);
		else if (alive->objcs[i].obj_type == cylinder)
			check_cylinder_vector((t_cylndr *)alive->objcs[i].the_obj, alive);
	}
}
