/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops_on_ray.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymohamed <ymohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 19:13:52 by ymohamed          #+#    #+#             */
/*   Updated: 2023/02/18 15:59:04 by ymohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytrace.h"

t_ray	fill_ray(t_point_vector *orgn_p, t_point_vector v)
{
	t_ray	result_ray;

	result_ray.origin = NULL;
	result_ray.direction = (t_point_vector){0, 0, 0, 0};
	if (!orgn_p || orgn_p->w != 1)
		return (write(2, "Error Creating ray\n", 19), result_ray);
	result_ray.origin = orgn_p;
	result_ray.direction.w = 0;
	result_ray.direction.x = v.x;
	result_ray.direction.y = v.y;
	result_ray.direction.z = v.z;
	return (result_ray);
}

t_point_vector	intrsction_point(const t_ray *r, float t)
{
	t_point_vector	result_point;
	t_point_vector	vec_x_t;

	result_point = (t_point_vector){0, 0, 0, 1};
	if (!r)
		return (write(2, "Errro find intersection point on a ray\n", 39),
			result_point);
	vec_x_t = rescale_vecotr(&r->direction, t);
	result_point = point_from_point_vector(r->origin, &vec_x_t);
	return (result_point);
}

static void	calculate_intersecion(const t_ray *r, const t_sphere *s, float *inf)
{
	float			a;
	float			b;
	float			c;
	float			det;
	t_point_vector	tmp;

	tmp = get_vec_a_to_b(&s->cent, r->origin);
	b = 2 * dot_multiplication(&tmp, &r->direction);
	a = dot_multiplication(&r->direction, &r->direction);
	c = dot_multiplication(&tmp, &tmp) - (s->rad * s->rad);
	det = (b * b) - (4 * a * c);
	if (det < 0)
		return ;
	det = sqrtf(det) / (2 * a);
	c = (-1 * b) / (2 * a);
	inf[2] = c + det;
	inf[3] = c - det;
	if (inf[3] > 0 || inf[2] > 0)
		inf[1] = 1;
	else
		inf[1] = -1;
}

void	ray_sphare_intrsection(const t_ray *r, const t_sphere *s, float *inf)
{
	float	tmp;

	if (!r || !s)
	{
		write(2, "Error getting intersctions with sphere\n", 39);
		return ;
	}
	inf[0] = s->objct_id;
	inf[1] = 0;
	inf[2] = 0;
	inf[3] = 0;
	inf[4] = 0;
	calculate_intersecion(r, s, inf);
	if (inf[2] > inf[3])
	{
		tmp = inf[2];
		inf[2] = inf[3];
		inf[3] = tmp;
	}
}
