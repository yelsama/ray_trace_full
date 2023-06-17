/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   form_shapes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymohamed <ymohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 18:09:12 by ymohamed          #+#    #+#             */
/*   Updated: 2023/06/17 18:39:38 by ymohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytrace.h"

t_sphere	fill_sphere(t_point_vector cntr, float rad, t_color clr)
{
	t_sphere	s;

	s.cent = cntr;
	s.rad = rad;
	s.color = clr;
	return (s);
}

t_plane	fill_plane(t_point_vector cntr, t_point_vector normal_v, t_color clr)
{
	t_plane	new_plane;

	new_plane.c_point = cntr;
	new_plane.normal_v = normal_v;
	new_plane.color = clr;
	return (new_plane);
}

t_cylndr	fill_cylndr(t_point_vector cntr, t_point_vector vec, t_color clr,
	float *h_r)
{
	t_cylndr	c;

	p0_plus_t_mul_v(&c.start, &cntr, &vec, -h_r[0] / 2 );
	p0_plus_t_mul_v(&c.end, &cntr, &vec, h_r[0] / 2);
	c.color = clr;
	c.rad = h_r[1];
	return (c);
}	
