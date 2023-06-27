/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   form_shapes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymohamed <ymohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 18:09:12 by ymohamed          #+#    #+#             */
/*   Updated: 2023/06/27 16:48:13 by ymohamed         ###   ########.fr       */
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
	t_cylndr		c;
	t_point_vector	tmp;

	c.cnt = cntr;
	c.vec = vec_norm(&vec);
	c.rad = h_r[1];
	c.height = h_r[0];
	c.color = clr;
	tmp = rescale_vecotr(&c.vec, c.height / 2);
	c.a = point_from_point_vector(&cntr, &tmp);
	tmp = rescale_vecotr(&tmp, -1.0);
	c.b = point_from_point_vector(&cntr, &tmp);
	c.ba_v = get_vec_a_to_b(&c.a, &c.b);
	c.baba = dot_multiplication(&c.ba_v, &c.ba_v);
	return (c);
}
