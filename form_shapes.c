/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   form_shapes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymohamed <ymohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 18:09:12 by ymohamed          #+#    #+#             */
/*   Updated: 2023/02/12 17:43:29 by ymohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytrace.h"

t_sphere	fill_sphare(t_point_vector cntr, float rad, int objct_id)
{
	t_sphere	s;

	s.objct_id = objct_id;
	s.cent = cntr;
	s.rad = rad;
	return (s);
}
