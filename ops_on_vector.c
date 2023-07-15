/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops_on_vector.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymohamed <ymohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 14:59:12 by ymohamed          #+#    #+#             */
/*   Updated: 2023/07/13 15:48:21 by ymohamed         ###   ########.fr       */
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
	t_point_vector	result_vec;

	result_vec = (t_point_vector){0.0, 0.0, 0.0, 0};
	if (!v1 || !v2 || v1->w == 1 || v2->w == 1)
		return (write(2, "Error Adding vectors\n", 21), result_vec);
	result_vec.w = 0;
	result_vec.x = v1->x + v2->x;
	result_vec.y = v1->y + v2->y;
	result_vec.z = v1->z + v2->z;
	return (result_vec);
}

t_point_vector	subtract_vectors(const t_point_vector *v1,
					const t_point_vector *v2)
{
	t_point_vector	result_vec;

	result_vec = (t_point_vector){0.0, 0.0, 0.0, 0};
	if (!v1 || !v2 || v1->w == 1 || v2->w == 1)
		return (write(2, "Error Subtracting vectors\n", 26), result_vec);
	result_vec.w = 0;
	result_vec.x = v1->x - v2->x;
	result_vec.y = v1->y - v2->y;
	result_vec.z = v1->z - v2->z;
	return (result_vec);
}

t_point_vector	vector_opposite(const t_point_vector *v)
{
	t_point_vector	result_vec;

	result_vec = (t_point_vector){0.0, 0.0, 0.0, 0};
	if (!v || v->w == 1)
		return (write(2, "Error finding vector opposite\n", 30), result_vec);
	result_vec.w = 0;
	result_vec.x = -1 * v->x;
	result_vec.y = -1 * v->y;
	result_vec.z = -1 * v->z;
	return (result_vec);
}

t_point_vector	get_vec_a_to_b(const t_point_vector *a,
					const t_point_vector *b)
{
	t_point_vector	result_vec;

	result_vec = (t_point_vector){0.0, 0.0, 0.0, 0.0};
	if (!a || !b || a->w == 0 || b->w == 0)
		return (write(2, "Error finding vector\n", 21), result_vec);
	result_vec.w = 0;
	result_vec.x = b->x - a->x;
	result_vec.y = b->y - a->y;
	result_vec.z = b->z - a->z;
	return (result_vec);
}
