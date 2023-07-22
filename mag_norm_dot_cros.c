/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mag_norm_dot_cros.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymohamed <ymohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 17:08:39 by ymohamed          #+#    #+#             */
/*   Updated: 2023/07/23 02:02:34 by ymohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytrace.h"

float	vec_mag(const t_tuple *v)
{
	float	result;

	if (!v || v->w == 1)
		return (write(2, "Error getting Magnitude of vector\n", 34), 0);
	result = sqrtf(powf(v->x, 2) + powf(v->y, 2) + powf(v->z, 2));
	return (result);
}

t_tuple	vec_norm(const t_tuple *v)
{
	t_tuple	result_vec;
	float	magnitude;

	result_vec = (t_tuple){0.0, 0.0, 0.0, 0};
	magnitude = vec_mag(v);
	if (magnitude == 0 || !v || v->w == 1)
		return (write(2, "Error Normalizing vector\n", 26), result_vec);
		result_vec.w = 0;
		result_vec.x = v->x / magnitude;
		result_vec.y = v->y / magnitude;
		result_vec.z = v->z / magnitude;
	return (result_vec);
}

float	dot_multiplication(const t_tuple *v1, const t_tuple *v2)
{
	float	result;

	if (!v1 || !v2 || v1->w == 1 || v2->w == 1)
		return (write(2, "Error operating dot product\n", 28), 0);
	result = v1->x * v2->x + v1->y * v2->y + v1->z * v2->z;
	return (result);
}

t_tuple	cros_multiplication(const t_tuple *v1,
					const t_tuple *v2)
{
	t_tuple	result_vec;

	result_vec = (t_tuple){.x = 0, .y = 0, .z = 0, .w = 0};
	if (!v1 || !v2 || v1->w == 1 || v2->w == 1)
		return (write(2, "Error operating cross product\n", 30), result_vec);
	result_vec.w = 0;
	result_vec.x = v1->y * v2->z - (v1->z * v2->y);
	result_vec.y = v1->z * v2->x - (v1->x * v2->z);
	result_vec.z = v1->x * v2->y - (v1->y * v2->x);
	return (result_vec);
}

t_tuple	rescale_vecotr(const t_tuple *v, float scl)
{
	t_tuple	result_vec;

	result_vec = (t_tuple){0, 0, 0, 0};
	if (!v || v->w != 0)
		return (write(2, "Error Secaling vector\n", 22), result_vec);
	result_vec.w = 0;
	result_vec.x = v->x * scl;
	result_vec.y = v->y * scl;
	result_vec.z = v->z * scl;
	return (result_vec);
}
