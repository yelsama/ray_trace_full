/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymohamed <ymohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 10:16:36 by ymohamed          #+#    #+#             */
/*   Updated: 2023/07/24 00:07:01 by ymohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytrace.h"

typedef struct cylinder
{
	t_tuple	oc_v;
	float	bard;
	float	baoc;
	float	k2;
	float	k1;
	float	k0;
	float	h;
	float	y;
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

// int	find_tow_lines_intersection(const t_tuple *l1o,
// 	const t_tuple *v1, const t_ray *r, float *ty)
// {
// 	t_tuple	l1v;
// 	t_tuple	l2v;
// 	t_tuple	l2_to_l1o;
// 	float	denominator;

// 	l1v = *v1;
// 	l2v = r->direction;
// 	*ty = 10;
// 	if (l2v.y == 0)
// 		denominator = l1v.x * l2v.z - l1v.z * l2v.x;
// 	else if (l2v.x == 0)
// 		denominator = l1v.y * l2v.z - l1v.z * l2v.y;
// 	else
// 		denominator = l1v.x * l2v.y - l1v.y * l2v.x;
// 	if (denominator == 0)
// 		return (0);
// 	if (l2v.y == 0)
// 	{
// 		l2_to_l1o.w = 0;
// 		l2_to_l1o.x = l1o->x - r->origin->x;
// 		l2_to_l1o.y = l1o->y - r->origin->y;
// 		l2_to_l1o.z = l1o->z - r->origin->z;		
// 		*ty = (l2_to_l1o.z * l2v.x - l2_to_l1o.x * l2v.z) / denominator;
// 	}
// 	else if (l2v.x == 0)
// 	{
// 		l2_to_l1o.w = 0;
// 		l2_to_l1o.x = l1o->x - r->origin->x;
// 		l2_to_l1o.y = l1o->y - r->origin->y;
// 		l2_to_l1o.z = l1o->z - r->origin->z;
// 		*ty = (l2_to_l1o.y * l2v.z - l2_to_l1o.z * l2v.y) / denominator;
// 	}
// 	else
// 	{
// 		l2_to_l1o.w = 0;
// 		l2_to_l1o.x = l1o->x - r->origin->x;
// 		l2_to_l1o.y = l1o->y - r->origin->y;
// 		l2_to_l1o.z = l1o->z - r->origin->z;	
// 		*ty = (l2_to_l1o.y * l2v.x - l2_to_l1o.x * l2v.y) / denominator;
// 	}
// 	return (1);
// }

// t_hit_info	ray_cylinder_intersect(const t_ray *r, const t_cylndr *c)
// {
// 	t_hit_info		inf;
// 	t_tuple			cx_v;
// 	t_tuple			cy_p;
// 	t_tuple			cc_ro_v;
// 	float			cx_dist;
// 	float			cy_dist;
// 	// t_sphere		s_tmp;

// 	inf.hit_or_not = 0;
// 	cx_v = cros_multiplication(&r->direction, &c->vec);
// 	if (vec_mag(&cx_v) < 0.0001)
// 	{
// 		//facing caps 
// 		// printf("got into cap directly\n");
// 		// exit(0);
// 		cc_ro_v = get_vec_a_to_b(&c->cnt, r->origin);
// 		inf.t = vec_mag(&cc_ro_v) - (c->height / 2);
// 		if (inf.t > 0)
// 			inf.hit_or_not = 1;
// 		return (inf);
// 	}
// 	cx_v = vec_norm(&cx_v);
// 	cc_ro_v = get_vec_a_to_b(&c->cnt, r->origin);
// 	cx_dist = dot_multiplication(&cc_ro_v, &cx_v);
// 	if (fabs(cx_dist) > c->rad)
// 		return (inf);
// 	p0_plus_t_mul_v(&cy_p, &c->cnt, &cx_v, cx_dist);
// 	if (!find_tow_lines_intersection(&cy_p, &c->vec, r, &cy_dist))
// 		return (inf);
// 	if (fabs(cy_dist) > c->height / 2)
// 		return (inf);
// 	// printf("----cx_v: %f\n", cy_dist);///
// 	// cx_v = rescale_vecotr(&c->vec, cy_dist);
// 	// s_tmp = fill_sphere(point_from_point_vector(&c->cnt, &cx_v),
		// c->rad, (t_color){255, 255, 255});
// 	// inf = ray_sphare_intrsection(r, &s_tmp);
// 	inf.hit_or_not = 1;
// 	inf.t = 30;
// 	return (inf);
// }
