/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_shade.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymohamed <ymohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 10:47:56 by ymohamed          #+#    #+#             */
/*   Updated: 2023/06/28 03:53:23 by ymohamed         ###   ########.fr       */
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

t_point_vector	normal_vec_on_sphere(const t_sphere *s, t_point_vector p)
{
	t_point_vector	result_vec;

	result_vec = (t_point_vector){0, 0, 0, 0};
	if (!s || p.w == 0)
		return (write(2, "Erro findin sphere normal vector\n", 33), result_vec);
	result_vec.x = p.x - s->cent.x;
	result_vec.y = p.y - s->cent.y;
	result_vec.z = p.z - s->cent.z;
	result_vec = vec_norm(&result_vec);
	return (result_vec);
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
	normal_v = normal_vec_on_sphere(s, hit_p);
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
