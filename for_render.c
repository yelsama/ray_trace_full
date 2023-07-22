/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymohamed <ymohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 12:42:11 by ymohamed          #+#    #+#             */
/*   Updated: 2023/07/23 02:01:33 by ymohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytrace.h"

void	set_camera(t_ranger *alive)
{
	float	half_size;

	half_size = tanf((alive->cam.field_of_view * DEGTORAD) / 2.0);
	alive->cam.aspect_ratio = (XBLOCK_DIM * 1.0) / (YBLOCK_DIM * 1.0);
	if (alive->cam.aspect_ratio >= 1.0)
	{
		alive->cam.half_width = half_size;
		alive->cam.half_height = half_size / alive->cam.aspect_ratio;
	}
	else
	{
		alive->cam.half_height = half_size;
		alive->cam.half_width = half_size * alive->cam.aspect_ratio;
	}
	alive->cam.pixel_size = (alive->cam.half_width * 2.0) / XBLOCK_DIM;
}

t_ray	ray_for_pixel(t_ranger *alive, int x, int y)
{
	float	h;
	float	w;
	t_tuple	vec_up;
	t_tuple	vec_right;
	t_ray	result_ray;

	h = alive->cam.half_height - (y * alive->cam.pixel_size);
	w = (x * alive->cam.pixel_size) - alive->cam.half_width;
	vec_up = rescale_vecotr(&alive->rend.look_up, h);
	vec_right = rescale_vecotr(&alive->rend.look_right, w);
	result_ray.direction = add_vectors(&alive->cam.look_forward, &vec_right);
	result_ray.direction = add_vectors(&result_ray.direction, &vec_up);
	result_ray.direction = vec_norm(&result_ray.direction);
	result_ray.origin = &alive->cam.location;
	return (result_ray);
}

void	get_camera_transform_matrix(t_ranger *alive)
{
	t_tuple		look_up;

	print_an_elemnt(&alive->cam.look_forward);
	look_up = (t_tuple){0.0, 1.0, 0.0, 0};
	alive->cam.look_forward = vec_norm(&alive->cam.look_forward);
	alive->rend.look_right = cros_multiplication(&look_up,
			&alive->cam.look_forward);
	if (alive->cam.look_forward.y == 1.0)
		alive->rend.look_right.x = 1.0;
	alive->rend.look_right = vec_norm(&alive->rend.look_right);
	look_up = cros_multiplication(&alive->cam.look_forward,
			&alive->rend.look_right);
	alive->rend.look_up = vec_norm(&look_up);
}

static void	update_hit(t_hit_info *inf, t_hit_info *tmp_inf, int i)
{
			inf->hit_or_not = 1;
			inf->t = tmp_inf->t;
			inf->obj_id = i;
}

typedef struct hit_set
{
	t_hit_info		inf;
	t_hit_info		tmp_inf;
	int				i;
	int				past_first;
}	t_hit_set;

t_hit_info	get_hit_object(t_ranger *alive, const t_ray *r)
{
	t_hit_set	set;

	set.inf.hit_or_not = 0;
	set.inf.t = 0.0;
	set.inf.obj_id = -1;
	set.past_first = 0;
	set.i = -1;
	while (++set.i < alive->no_of_object)
	{
		if (alive->objcs[set.i].obj_type == sphere)
			set.tmp_inf = ray_sphare_intrsection(r,
					(t_sphere *)alive->objcs[set.i].the_obj);
		else if (alive->objcs[set.i].obj_type == plane)
			set.tmp_inf = ray_plane_intersection(r,
					(t_plane *)alive->objcs[set.i].the_obj);
		else if (alive->objcs[set.i].obj_type == cylinder)
			set.tmp_inf = ray_cylinder_intersect(r,
					(t_cylndr *)alive->objcs[set.i].the_obj);
		if (!set.past_first && set.tmp_inf.hit_or_not > 0 && !set.past_first++)
			update_hit(&set.inf, &set.tmp_inf, set.i);
		if (set.tmp_inf.hit_or_not > 0 && set.tmp_inf.t < set.inf.t)
			update_hit(&set.inf, &set.tmp_inf, set.i);
	}
	return (set.inf);
}
