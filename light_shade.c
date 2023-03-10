/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_shade.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymohamed <ymohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 10:47:56 by ymohamed          #+#    #+#             */
/*   Updated: 2023/03/03 16:51:40 by ymohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytrace.h"

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

// t_point_vector	reflect_around_normal(const t_point_vector *in,
// const t_point_vector *norm)
// {
// 	t_point_vector	result_vec;
// 	float			tmp;

// 	result_vec = (t_point_vector){0, 0, 0, 0};
// 	if (!in || !norm || in->w != 0 || norm->w != 0)
// 		return (write(2, "Error finiding refleced vector\n", 31), result_vec);
// 	tmp = dot_multiplication(in, norm) * 2;
// 	result_vec.x = in->x - (tmp * norm->x);
// 	result_vec.y = in->y - (tmp * norm->y);
// 	result_vec.z = in->z - (tmp * norm->z);
// 	return (result_vec);
// }

int	ligth_effect_on_sphere_pxl_color(t_point_vector hit_p, const t_sphere *s,
const t_light *l, const t_light *amb)
{
	t_color			amb_clr;
	t_color			result_color;
	t_point_vector	pxl_to_light_v;
	t_point_vector	normal_v;
	float			effect;

	result_color = (t_color){0, 0, 0};
	if (!l || !s || hit_p.w != 1)
		return (write(2, "Error Shading pixel\n", 20), 0);
	pxl_to_light_v = get_vec_a_to_b(&hit_p, &l->position);
	pxl_to_light_v = vec_norm(&pxl_to_light_v);
	normal_v = normal_vec_on_sphere(s, hit_p);
	normal_v = vec_norm(&normal_v);
	amb_clr = color_multi_scalar(&amb->color, amb->brightness);
	amb_clr = blend_two_colors(&amb_clr, &s->color);
	result_color = color_multi_scalar(&l->color, l->brightness);
	effect = dot_multiplication(&normal_v, &pxl_to_light_v);
	result_color = color_multi_scalar(&l->color, effect);
	result_color = blend_two_colors(&result_color, &s->color);
	result_color = add_colors(&result_color, &amb_clr);
	return (rgb_to_int(&result_color));
}
