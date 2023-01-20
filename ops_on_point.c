/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops_on_point.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymohamed <ymohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 14:57:38 by ymohamed          #+#    #+#             */
/*   Updated: 2023/01/20 20:14:19 by ymohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytrace.h"

int	fill_point(t_point_vector *p, float x, float y, float z)
{
	if (!p)
		return (write(2, "Error fillig point\n", 19), 0);
	p->w = 1;
	p->x = x;
	p->y = y;
	p->z = z;
	return (1);
}

t_point_vector	point_from_point_vector(const t_point_vector *a,
					const t_point_vector *v)
{
	t_point_vector	result_point;

	result_point = (t_point_vector){0, 0, 0, 1};
	if (!a || !v || a->w != 1 || v->w != 0)
		return (write(2, "Error finding the point\n", 24), result_point);
	result_point.w = 1;
	result_point.x = a->x + v->x;
	result_point.y = a->y + v->y;
	result_point.z = a->z + v->z;
	return (result_point);
}

int	elemnts_are_identical(const t_point_vector *a,
					const t_point_vector *b, float epsilon)
{
	float	differ;

	if (!a || !b || a->w != b->w)
		return (0);
	differ = a->x - b->x;
	if (differ < 0)
		differ = differ * -1;
	if (differ > epsilon)
		return (0);
	differ = a->y - b->y;
	if (differ < 0)
		differ = differ * -1;
	if (differ > epsilon)
		return (0);
	differ = a->z - b->z;
	if (differ < 0)
		differ = differ * -1;
	if (differ > epsilon)
		return (0);
	return (1);
}
