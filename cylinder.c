/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymohamed <ymohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 10:16:36 by ymohamed          #+#    #+#             */
/*   Updated: 2023/07/18 21:41:05 by ymohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytrace.h"

typedef struct cylinder
{
	t_point_vector	oc_v;
	float			bard;
	float			baoc;
	float			k2;
	float			k1;
	float			k0;
	float			h;
	float			y;
}	t_detect_elemnts;

static int	initiate_coeficents_check(t_detect_elemnts *s, const t_cylndr *c,
const t_ray *r)
{
	s->oc_v = get_vec_a_to_b(&c->a, r->origin);
	s->bard = dot_multiplication(&c->ba_v, &r->direction);
	s->baoc = dot_multiplication(&c->ba_v, &s->oc_v);
	s->k2 = c->baba - (s->bard * s->bard);
	s->k1 = (c->baba * dot_multiplication(&s->oc_v, &r->direction))
		- (s->baoc * s->bard);
	s->k0 = (c->baba * dot_multiplication(&s->oc_v, &s->oc_v))
		- (s->baoc * s->baoc) - (c->rad * c->rad * c->baba);
	s->h = s->k1 * s->k1 - s->k2 * s->k0;
	if (s->h < 0.0)
		return (0);
	return (1);
}

t_hit_info	ray_cylinder_intersect(const t_ray *r, const t_cylndr *c)
{
	t_hit_info			inf;
	t_detect_elemnts	set;

	inf.hit_or_not = 0;
	if (!initiate_coeficents_check(&set, c, r))
		return (inf);
	set.h = sqrtf(set.h);
	inf.t = (-1.0 * set.k1 - set.h) / set.k2;
	set.y = set.baoc + inf.t * set.bard;
	if (set.y > 0.0 && set.y < c->baba)
	{
		if (inf.t >= 0)
			inf.hit_or_not = 1;
		return (inf);
	}
	if (set.y < 0.0)
		inf.t = (0.0 - set.baoc) / set.bard;
	else
		inf.t = (c->baba - set.baoc) / set.bard;
	if (fabs(set.k1 + set.k2 * inf.t) < set.h && inf.t >= 0)
	{
		inf.hit_or_not = 1;
		return (inf);
	}
	return (inf);
}
