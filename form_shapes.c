/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   form_shapes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymohamed <ymohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 18:09:12 by ymohamed          #+#    #+#             */
/*   Updated: 2023/03/21 21:23:53 by ymohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytrace.h"

t_sphere	fill_sphere(t_point_vector cntr, float rad, t_color clr,
int objct_id)
{
	t_sphere	s;

	s.objct_id = objct_id;
	s.cent = cntr;
	s.rad = rad;
	s.color = clr;
	return (s);
}

t_plane	fill_plane(t_point_vector cntr, t_point_vector normal_v, t_color clr,
int objct_id)
{
	t_plane	new_plane;

	new_plane.objct_id = objct_id;
	new_plane.c_point = cntr;
	new_plane.normal_v = normal_v;
	new_plane.color = clr;
	return (new_plane);
}
