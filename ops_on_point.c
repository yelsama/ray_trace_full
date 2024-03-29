/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops_on_point.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymohamed <ymohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 14:57:38 by ymohamed          #+#    #+#             */
/*   Updated: 2023/07/23 01:58:55 by ymohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytrace.h"

int	fill_point(t_tuple *p, float x, float y, float z)
{
	if (!p)
		return (write(2, "Error fillig point\n", 19), 0);
	p->w = 1;
	p->x = x;
	p->y = y;
	p->z = z;
	return (1);
}

t_tuple	point_from_point_vector(const t_tuple *a,
					const t_tuple *v)
{
	t_tuple	result_point;

	result_point = (t_tuple){0.0, 0.0, 0.0, 1};
	if (!a || !v || a->w != 1 || v->w != 0)
		return (write(2, "Error finding the point\n", 24), result_point);
	result_point.w = 1;
	result_point.x = a->x + v->x;
	result_point.y = a->y + v->y;
	result_point.z = a->z + v->z;
	return (result_point);
}

int	elemnts_are_identical(const t_tuple *a,
					const t_tuple *b, float epsilon)
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

void	print_an_elemnt(t_tuple *e)
{
	if (!e)
	{
		write(1, "Element not exist or inintialized\n", 34);
		return ;
	}
	if (e->w == 0)
		write(1, "this is a vector, ", 18);
	if (e->w == 1)
		write(1, "this is point, ", 15);
	printf("x is %.4f, y is %.4f, z is %.4f\n", e->x, e->y, e->z);
}

void	p0_plus_t_mul_v(t_tuple *p, const t_tuple *p0,
					const t_tuple *v, float t)
{
	p->w = 1;
	p->x = p0->x + (t * v->x);
	p->y = p0->y + (t * v->y);
	p->z = p0->z + (t * v->z);
}
