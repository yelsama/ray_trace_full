/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_shade.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymohamed <ymohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 10:47:56 by ymohamed          #+#    #+#             */
/*   Updated: 2023/07/16 16:17:07 by ymohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytrace.h"

int	under_shadow(t_ranger *alive, t_point_vector p, t_point_vector v, int ob_id)
{
	int			i;
	t_hit_info	hit_inf;
	t_ray		r;
	
	r = fill_ray(&p , v);
	i = -1;
	hit_inf.hit_or_not = 0;
	while (++i < alive->no_of_object)
	{
		if (i == ob_id)
			continue;
		if (alive->objcs[i].obj_type == sphere)
			hit_inf = ray_sphare_intrsection(&r, (t_sphere *)alive->objcs[i].the_obj);
		else if (alive->objcs[i].obj_type == plane)
			hit_inf = ray_plane_intersection(&r, (t_plane *)alive->objcs[i].the_obj);
		else if (alive->objcs[i].obj_type == cylinder)
			hit_inf = ray_cylinder_intersect(&r, (t_cylndr *)alive->objcs[i].the_obj);
		else
			continue;
			// printf("got uknown object at light_shade.c\n");/////
		if (hit_inf.hit_or_not == 1)
			return (1);
	}
	return (0);
}

int	ligth_effect_on_sphere_pxl_color(t_ranger *alive, t_point_vector hit_p,
int obj_id)
{
	t_sphere		*s;
	t_color			amb_clr;
	t_color			full_clr;
	t_point_vector	pxl_to_light_v;
	t_point_vector	normal_v;

	s = (t_sphere *)alive->objcs[obj_id].the_obj;
	pxl_to_light_v = get_vec_a_to_b(&hit_p, &alive->main_light.position);
	pxl_to_light_v = vec_norm(&pxl_to_light_v);
	normal_v = get_vec_a_to_b(&s->cent, &hit_p);
	normal_v = vec_norm(&normal_v);
	amb_clr = blend_two_colors(&alive->amb_appear_clr, &s->color);
	if (under_shadow(alive, hit_p, pxl_to_light_v, obj_id))
		return (rgb_to_int(&amb_clr));
	full_clr = color_multi_scalar(&alive->light_appear_clr,
		dot_multiplication(&normal_v, &pxl_to_light_v));
	full_clr = blend_two_colors(&full_clr, &s->color);
	full_clr = add_colors(&full_clr, &amb_clr);
	return (rgb_to_int(&full_clr));
}

int	light_effect_on_plane_pxl_color(t_ranger *alive, t_point_vector hit_p,
int obj_id)
{
	t_plane			*p;
	t_color			amb_clr;
	t_color			full_clr;
	t_point_vector	pxl_to_light_v;
	t_point_vector	normal_v;

	p = (t_plane *)alive->objcs[obj_id].the_obj;
	pxl_to_light_v = get_vec_a_to_b(&hit_p, &alive->main_light.position);
	pxl_to_light_v = vec_norm(&pxl_to_light_v);
	normal_v = vec_norm(&p->normal_v);
	amb_clr = blend_two_colors(&alive->amb_appear_clr, &p->color);
	if (under_shadow(alive, hit_p, pxl_to_light_v, obj_id))
		return (rgb_to_int(&amb_clr));
	full_clr = color_multi_scalar(&alive->light_appear_clr,
				dot_multiplication(&normal_v, &pxl_to_light_v));
	full_clr = blend_two_colors(&full_clr, &p->color);
	full_clr = add_colors(&full_clr, &amb_clr);
	return (rgb_to_int(&full_clr));
}

t_point_vector  get_cylinder_normal_v(t_cylndr *c, t_point_vector *hit_p)
{
    t_point_vector	ch_v;
	t_point_vector	n_cnt;
	t_point_vector	tmp;
	t_point_vector	normal_v;
	float			sab;

	tmp = get_vec_a_to_b(&c->a, hit_p);
	sab = fabs(vec_mag(&tmp));
    if (sab < c->rad)
		return (rescale_vecotr(&c->vec, -1.0));
        // return (c->vec);
	tmp = get_vec_a_to_b(&c->b, hit_p);
	sab = fabs(vec_mag(&tmp));
    if (sab < c->rad)
        return (c->vec);
    ch_v = get_vec_a_to_b(&c->cnt, hit_p);
	p0_plus_t_mul_v(&n_cnt, &c->cnt, &c->vec,
            dot_multiplication(&ch_v, &c->vec));
	normal_v = get_vec_a_to_b(&n_cnt, hit_p);
	normal_v = vec_norm(&normal_v);
    return (normal_v);
}

int	light_effect_on_cylndr_pxl_color(t_ranger *alive, t_point_vector hit_p,
int obj_id)
{
	t_cylndr        *c;
	t_color			amb_clr;
	t_color			full_clr;
	t_point_vector	pxl_to_light_v;
	t_point_vector	normal_v;

	c = (t_cylndr *)alive->objcs[obj_id].the_obj;
	pxl_to_light_v = get_vec_a_to_b(&hit_p, &alive->main_light.position);
	pxl_to_light_v = vec_norm(&pxl_to_light_v);
    normal_v = get_cylinder_normal_v(c, &hit_p);
	amb_clr = blend_two_colors(&alive->amb_appear_clr, &c->color);
	if (under_shadow(alive, hit_p, pxl_to_light_v, obj_id))
		return (rgb_to_int(&amb_clr));
	full_clr = color_multi_scalar(&alive->light_appear_clr,
		dot_multiplication(&normal_v, &pxl_to_light_v));
	full_clr = blend_two_colors(&full_clr, &c->color);
	full_clr = add_colors(&full_clr, &amb_clr);
	return (rgb_to_int(&full_clr));
}
