/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops_on_vector.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymohamed <ymohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 14:59:12 by ymohamed          #+#    #+#             */
/*   Updated: 2023/07/23 01:58:55 by ymohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytrace.h"

int	fill_vector(t_tuple *v, float x, float y, float z)
{
	if (!v)
		return (write(2, "Error filling vector\n", 21), 0);
	v->w = 0;
	v->x = x;
	v->y = y;
	v->z = z;
	return (1);
}

t_tuple	add_vectors(const t_tuple *v1, const t_tuple *v2)
{
	t_tuple	result_vec;

	result_vec = (t_tuple){0.0, 0.0, 0.0, 0};
	if (!v1 || !v2 || v1->w == 1 || v2->w == 1)
		return (write(2, "Error Adding vectors\n", 21), result_vec);
	result_vec.w = 0;
	result_vec.x = v1->x + v2->x;
	result_vec.y = v1->y + v2->y;
	result_vec.z = v1->z + v2->z;
	return (result_vec);
}

t_tuple	subtract_vectors(const t_tuple *v1,
					const t_tuple *v2)
{
	t_tuple	result_vec;

	result_vec = (t_tuple){0.0, 0.0, 0.0, 0};
	if (!v1 || !v2 || v1->w == 1 || v2->w == 1)
		return (write(2, "Error Subtracting vectors\n", 26), result_vec);
	result_vec.w = 0;
	result_vec.x = v1->x - v2->x;
	result_vec.y = v1->y - v2->y;
	result_vec.z = v1->z - v2->z;
	return (result_vec);
}

t_tuple	vector_opposite(const t_tuple *v)
{
	t_tuple	result_vec;

	result_vec = (t_tuple){0.0, 0.0, 0.0, 0};
	if (!v || v->w == 1)
		return (write(2, "Error finding vector opposite\n", 30), result_vec);
	result_vec.w = 0;
	result_vec.x = -1 * v->x;
	result_vec.y = -1 * v->y;
	result_vec.z = -1 * v->z;
	return (result_vec);
}

t_tuple	get_vec_a_to_b(const t_tuple *a,
					const t_tuple *b)
{
	t_tuple	result_vec;

	result_vec = (t_tuple){0.0, 0.0, 0.0, 0.0};
	if (!a || !b || a->w == 0 || b->w == 0)
		return (write(2, "Error finding vector\n", 21), result_vec);
	result_vec.w = 0;
	result_vec.x = b->x - a->x;
	result_vec.y = b->y - a->y;
	result_vec.z = b->z - a->z;
	return (result_vec);
}
