/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_shade.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymohamed <ymohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 10:47:56 by ymohamed          #+#    #+#             */
/*   Updated: 2023/07/23 02:22:05 by ymohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytrace.h"

typedef struct shadow_vars
{
	int			i;
	t_hit_info	hit_inf;
	t_ray		r;
	float		light_t;
}	t_shadow_var;

int	under_shadow(t_ranger *alive, t_tuple p, t_tuple v, int ob_id)
{
	t_shadow_var	set;

	set.i = -1;
	set.light_t = vec_mag(&v);
	v = vec_norm(&v);
	set.r = fill_ray(&p, v);
	while (++set.i < alive->no_of_object)
	{
		set.hit_inf.hit_or_not = 0;
		if (set.i == ob_id)
			continue ;
		if (alive->objcs[set.i].obj_type == sphere)
			set.hit_inf = ray_sphare_intrsection(&set.r,
					(t_sphere *)alive->objcs[set.i].the_obj);
		else if (alive->objcs[set.i].obj_type == plane)
			set.hit_inf = ray_plane_intersection(&set.r,
					(t_plane *)alive->objcs[set.i].the_obj);
		else if (alive->objcs[set.i].obj_type == cylinder)
			set.hit_inf = ray_cylinder_intersect(&set.r,
					(t_cylndr *)alive->objcs[set.i].the_obj);
		if (set.hit_inf.hit_or_not == 1 && set.hit_inf.t < set.light_t)
			return (1);
	}
	return (0);
}

int	ligth_effect_on_sphere_pxl_color(t_ranger *alive, t_tuple hit_p,
int obj_id)
{
	t_sphere		*s;
	t_color			amb_clr;
	t_color			full_clr;
	t_tuple	pxl_to_light_v;
	t_tuple	normal_v;

	s = (t_sphere *)alive->objcs[obj_id].the_obj;
	pxl_to_light_v = get_vec_a_to_b(&hit_p, &alive->main_light.position);
	normal_v = get_vec_a_to_b(&s->cent, &hit_p);
	normal_v = vec_norm(&normal_v);
	amb_clr = blend_two_colors(&alive->amb_appear_clr, &s->color);
	if (under_shadow(alive, hit_p, pxl_to_light_v, obj_id))
		return (rgb_to_int(&amb_clr));
	pxl_to_light_v = vec_norm(&pxl_to_light_v);
	full_clr = color_multi_scalar(&alive->light_appear_clr,
			dot_multiplication(&normal_v, &pxl_to_light_v));
	full_clr = blend_two_colors(&full_clr, &s->color);
	full_clr = add_colors(&full_clr, &amb_clr);
	return (rgb_to_int(&full_clr));
}

int	light_effect_on_plane_pxl_color(t_ranger *alive, t_tuple hit_p,
int obj_id)
{
	t_plane			*p;
	t_color			amb_clr;
	t_color			full_clr;
	t_tuple			pxl_to_light_v;
	t_tuple			normal_v;

	p = (t_plane *)alive->objcs[obj_id].the_obj;
	pxl_to_light_v = get_vec_a_to_b(&hit_p, &alive->main_light.position);
	normal_v = vec_norm(&p->normal_v);
	amb_clr = blend_two_colors(&alive->amb_appear_clr, &p->color);
	if (under_shadow(alive, hit_p, pxl_to_light_v, obj_id))
		return (rgb_to_int(&amb_clr));
	pxl_to_light_v = vec_norm(&pxl_to_light_v);
	full_clr = color_multi_scalar(&alive->light_appear_clr,
			dot_multiplication(&normal_v, &pxl_to_light_v));
	full_clr = blend_two_colors(&full_clr, &p->color);
	full_clr = add_colors(&full_clr, &amb_clr);
	return (rgb_to_int(&full_clr));
}

t_tuple	get_cylinder_normal_v(t_cylndr *c, t_tuple *hit_p)
{
	t_tuple	ch_v;
	t_tuple	n_cnt;
	t_tuple	tmp[2];
	t_tuple	normal_v;
	float	sab[2];

	tmp[0] = get_vec_a_to_b(&c->a, hit_p);
	sab[0] = fabs(vec_mag(&tmp[0]));
	tmp[1] = get_vec_a_to_b(&c->b, hit_p);
	sab[1] = fabs(vec_mag(&tmp[1]));
	if (sab[0] < c->rad && sab[0] < sab[1])
		return (c->vec);
	if (sab[1] < c->rad)
		return (rescale_vecotr(&c->vec, -1.0));
	ch_v = get_vec_a_to_b(&c->cnt, hit_p);
	p0_plus_t_mul_v(&n_cnt, &c->cnt, &c->vec,
		dot_multiplication(&ch_v, &c->vec));
	normal_v = get_vec_a_to_b(&n_cnt, hit_p);
	normal_v = vec_norm(&normal_v);
	return (normal_v);
}

int	light_effect_on_cylndr_pxl_color(t_ranger *alive, t_tuple hit_p,
int obj_id)
{
	t_cylndr		*c;
	t_color			amb_clr;
	t_color			full_clr;
	t_tuple			pxl_to_light_v;
	t_tuple			normal_v;

	c = (t_cylndr *)alive->objcs[obj_id].the_obj;
	pxl_to_light_v = get_vec_a_to_b(&hit_p, &alive->main_light.position);
	normal_v = get_cylinder_normal_v(c, &hit_p);
	amb_clr = blend_two_colors(&alive->amb_appear_clr, &c->color);
	if (under_shadow(alive, hit_p, pxl_to_light_v, obj_id))
		return (rgb_to_int(&amb_clr));
	pxl_to_light_v = vec_norm(&pxl_to_light_v);
	full_clr = color_multi_scalar(&alive->light_appear_clr,
			dot_multiplication(&normal_v, &pxl_to_light_v));
	full_clr = blend_two_colors(&full_clr, &c->color);
	full_clr = add_colors(&full_clr, &amb_clr);
	return (rgb_to_int(&full_clr));
}
