/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam_inside.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymohamed <ymohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 20:21:23 by ymohamed          #+#    #+#             */
/*   Updated: 2023/08/20 20:25:45 by ymohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytrace.h"

static int	more_detailed_cylndr_cam_inside(t_cylndr *cylndr,
			t_tuple cam_to_cylndr_center)
{
	float	dot;	
	t_tuple	perpendecular_vec;

	dot = dot_multiplication(&cam_to_cylndr_center, &cylndr->vec);
	if (fabs(dot) < cylndr->height / 2)
		return (1);
	perpendecular_vec
		= cros_multiplication(&cylndr->vec, &cam_to_cylndr_center);
	perpendecular_vec = vec_norm(&perpendecular_vec);
	dot = dot_multiplication(&perpendecular_vec, &cam_to_cylndr_center);
	if (fabs(dot) < cylndr->rad)
		return (1);
	return (0);
}

static int	cylinder_cam_inside(t_tuple cam_location, t_cylndr *cylndr)
{
	t_tuple	cam_to_cylndr_center;
	float	distance;
	float	dot;

	cam_to_cylndr_center = get_vec_a_to_b(&cam_location, &cylndr->cnt);
	distance = vec_mag(&cam_to_cylndr_center);
	if (fabs(distance) > (sqrtf(powf(cylndr->height / 2, 2)
				+ powf(cylndr->rad, 2))))
		return (0);
	dot = dot_multiplication(&cam_to_cylndr_center, &cylndr->vec);
	if (fabs(dot) < 0.00001 && distance < cylndr->rad)
		return (1);
	if (fabs(dot) < 0.00001 && distance > cylndr->rad)
		return (0);
	dot = fabs(dot) - fabs(vec_mag(&cam_to_cylndr_center));
	if (fabs(dot) < 0.00001 && distance < cylndr->height / 2)
		return (1);
	if (fabs(dot) < 0.00001 && distance > cylndr->height / 2)
		return (0);
	return (more_detailed_cylndr_cam_inside(cylndr, cam_to_cylndr_center));
}

static int	sphere_cam_inside(t_tuple cam_location, t_sphere *sphere)
{
	t_tuple	cam_to_sphere_center;
	float	distance;

	cam_to_sphere_center = get_vec_a_to_b(&cam_location, &sphere->cent);
	distance = vec_mag(&cam_to_sphere_center);
	if (fabs(distance) < sphere->rad)
		return (1);
	return (0);
}

static int	plane_cam_inside(t_tuple cam_location, t_plane *plane)
{
	t_tuple	cam_to_plane_center;
	float	distance;
	float	dot;

	cam_to_plane_center = get_vec_a_to_b(&cam_location, &plane->c_point);
	distance = vec_mag(&cam_to_plane_center);
	if (fabs(distance) < 0.00001)
		return (1);
	dot = dot_multiplication(&cam_to_plane_center, &plane->normal_v);
	if (fabs(dot) < 0.00001)
		return (1);
	return (0);
}

int	verify_camera_inside(t_ranger *alive)
{
	int	i;
	int	cam_inside;

	i = -1;
	cam_inside = 0;
	while (++i < alive->no_of_object)
	{
		if (alive->objcs[i].obj_type == sphere)
			cam_inside = sphere_cam_inside(alive->cam.location,
					(t_sphere *)alive->objcs[i].the_obj);
		else if (alive->objcs[i].obj_type == plane)
			cam_inside = plane_cam_inside(alive->cam.location,
					(t_plane *)alive->objcs[i].the_obj);
		else if (alive->objcs[i].obj_type == cylinder)
			cam_inside = cylinder_cam_inside(alive->cam.location,
					(t_cylndr *)alive->objcs[i].the_obj);
		else
			continue ;
		if (cam_inside)
			return (1);
	}
	return (0);
}
