/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inspect_intersect.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymohamed <ymohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 20:29:13 by ymohamed          #+#    #+#             */
/*   Updated: 2023/03/22 16:00:14 by ymohamed         ###   ########.fr       */
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
	if (det < 0)
		return ;
	det = sqrtf(det) / (2.0 * a);
	c = (-1.0 * b) / (2.0 * a);
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
	inf[2] = 0.0;
	inf[3] = 0.0;
	inf[4] = 0;
	calculate_intersecion(r, s, inf);
	if (inf[2] > inf[3])
	{
		tmp = inf[2];
		inf[2] = inf[3];
		inf[3] = tmp;
	}
}

void	ray_plane_intersection(const t_ray *r, const t_plane *p, float *inf)
{
	t_point_vector	oc_v;
	float			vdotn;
	float			oc_vdotn;
	float			t;

	if (!r || !p)
	{
		write(2, "Error getting intersctions with plane\n", 39);
		return ;
	}
	inf[0] = p->objct_id;
	inf[1] = 0;
	inf[2] = 0.0;
	inf[3] = 0.0;
	inf[4] = 0;
	oc_v = get_vec_a_to_b(r->origin, &p->c_point);
	// oc_v = vec_norm(&oc_v);
	vdotn = dot_multiplication(&r->direction, &p->normal_v);
	if (vdotn == 0.0)
		return ;
	oc_vdotn = dot_multiplication(&oc_v, &p->normal_v);
	t = oc_vdotn / vdotn;
	if (t < 0.0)
		return ;
	inf[1] = 1;
	inf[2] = t;
}
