/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inspect_intersect.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymohamed <ymohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 20:29:13 by ymohamed          #+#    #+#             */
/*   Updated: 2023/07/18 20:59:48 by ymohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytrace.h"

static void	calculate_intersecion(const t_ray *r, const t_sphere *s, float *inf)
{
	float			a;
	float			b;
	float			c;
	float			det;
	t_point_vector	tmp;

	tmp = get_vec_a_to_b(&s->cent, r->origin);
	b = 2.0 * dot_multiplication(&tmp, &r->direction);
	a = dot_multiplication(&r->direction, &r->direction);
	c = dot_multiplication(&tmp, &tmp) - (s->rad * s->rad);
	det = (b * b) - (4 * a * c);
	if (det < 0.0)
		return ;
	a = 2.0 * a;
	det = sqrtf(det) / a;
	c = (-1.0 * b) / a;
	inf[1] = c + det;
	inf[2] = c - det;
	if (inf[2] > 0 || inf[1] > 0)
		inf[0] = 1;
	else
		inf[0] = 0;
}

t_hit_info	ray_sphare_intrsection(const t_ray *r, const t_sphere *s)
{
	float		tmp;
	t_hit_info	new;
	float		inf[3];

	if (!r || !s)
	{
		write(2, "Error getting intersctions with sphere\n", 39);
		return (new.hit_or_not = 0, new.t = 0, new);
	}
	inf[0] = 0;
	inf[1] = 0.0;
	inf[2] = 0.0;
	calculate_intersecion(r, s, inf);
	if (inf[1] > inf[2] && inf[2] > 0)
	{
		tmp = inf[1];
		inf[1] = inf[2];
		inf[2] = tmp;
	}
	new.hit_or_not = inf[0];
	new.t = inf[1];
	return (new);
}

t_hit_info	ray_plane_intersection(const t_ray *r, const t_plane *p)
{
	t_point_vector	oc_v;
	float			vdotn;
	float			oc_vdotn;
	t_hit_info		new;

	new.hit_or_not = 0;
	new.t = 0;
	if (!r || !p)
	{
		write(2, "Error getting intersctions with plane\n", 39);
		return (new);
	}
	oc_v = get_vec_a_to_b(r->origin, &p->c_point);
	vdotn = dot_multiplication(&r->direction, &p->normal_v);
	if (vdotn == 0.0)
		return (new);
	oc_vdotn = dot_multiplication(&oc_v, &p->normal_v);
	new.t = oc_vdotn / vdotn;
	if (new.t < 0.00001)
		return (new);
	new.hit_or_not = 1;
	return (new);
}
