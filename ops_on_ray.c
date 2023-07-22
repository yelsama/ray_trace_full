/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops_on_ray.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymohamed <ymohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 19:13:52 by ymohamed          #+#    #+#             */
/*   Updated: 2023/07/23 01:58:55 by ymohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytrace.h"

t_ray	fill_ray(t_tuple *orgn_p, t_tuple v)
{
	t_ray	result_ray;

	result_ray.origin = NULL;
	result_ray.direction = (t_tuple){0.0, 0.0, 0.0, 0.0};
	if (!orgn_p || orgn_p->w != 1)
		return (write(2, "Error Creating ray\n", 19), result_ray);
	result_ray.origin = orgn_p;
	result_ray.direction.w = 0.0;
	result_ray.direction.x = v.x;
	result_ray.direction.y = v.y;
	result_ray.direction.z = v.z;
	return (result_ray);
}

t_tuple	intrsction_point(const t_ray *r, float t)
{
	t_tuple	result_point;
	t_tuple	vec_x_t;

	result_point = (t_tuple){0.0, 0.0, 0.0, 1.0};
	if (!r)
		return (write(2, "Errro find intersection point on a ray\n", 39),
			result_point);
	vec_x_t = rescale_vecotr(&r->direction, t);
	result_point = point_from_point_vector(r->origin, &vec_x_t);
	return (result_point);
}
