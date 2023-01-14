/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops_on_vector.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymohamed <ymohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 14:59:12 by ymohamed          #+#    #+#             */
/*   Updated: 2023/01/14 17:55:00 by ymohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytrace.h"

int	fill_vector(t_point_vector *v, float x, float y, float z)
{
	if (!v)
		return (write(2, "Error filling vector\n", 21), 0);
	v->w = 0;
	v->x = x;
	v->y = y;
	v->z = z;
	return (1);
}

t_point_vector	add_vectors(const t_point_vector *v1, const t_point_vector *v2)
{
	t_point_vector	resul_vec;

	if (!v1 || !v2 || v1->w == 1 || v2->w == 1)
		return (write(2, "Error Adding victors\n", 21), NULL);
	resul_vec.w = 0;
	resul_vec.x = v1->x + v2->x;
	resul_vec.y = v1->y + v2->y;
	resul_vec.z = v1->z + v2->z;
	return (resul_vec);
}

t_point_vector	subract_vectors(const t_point_vector *v1,
					const t_point_vector *v2)
{
	t_point_vector	resul_vec;

	if (!v1 || !v2 || v1->w == 1 || v2->w == 1)
		return (write(2, "Error Subtracting victors\n", 26), NULL);
	resul_vec.w = 0;
	resul_vec.x = v1->x - v2->x;
	resul_vec.y = v1->y - v2->y;
	resul_vec.z = v1->z - v2->z;
	return (resul_vec);
}

t_point_vector	vector_opposite(const t_point_vector *v)
{
	t_point_vector	restult_vector;

	if (!v || v->w == 1)
		return (write(2, "Error finding vector opposite\n", 30), NULL);
	restult_vector.w = 0;
	restult_vector.x = -1 * v->x;
	restult_vector.y = -1 * v->y;
	restult_vector.z = -1 * v->z;
	return (restult_vector);
}

t_point_vector	get_vec_a_to_b(const t_point_vector *a,
					const t_point_vector *b)
{
	t_point_vector	result_vector;

	if (!a || !b || a->w == 0 || b->w == 0)
		return (write(2, "Error finding vector\n", 21), NULL);
	result_vector.w = 0;
	result_vector.x = b->x - a->x;
	result_vector.y = b->y - a->y;
	result_vector.z = b->z - a->z;
	return (result_vector);
}
