/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymohamed <ymohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 12:42:11 by ymohamed          #+#    #+#             */
/*   Updated: 2023/06/17 22:00:31 by ymohamed         ###   ########.fr       */
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
	// t_ray			result_ray;
	// t_point_vector	wall_point;
	// t_point_vector	new_vec;

	// wall_point.w = 1;
	// wall_point.x = (x * alive->cam.pixel_size) - alive->cam.half_width;
	// wall_point.y = alive->cam.half_height - (y * alive->cam.pixel_size);
	// new_vec = (t_point_vector){wall_point.x, wall_point.y, 1.0, 0};
	// wall_point.z = 1.0;
	// reform_tupl_by_matrix(&alive->cam.transform, &wall_point);
	// result_ray.direction = get_vec_a_to_b(&alive->cam.location, &wall_point);
	// result_ray.direction = vec_norm(&result_ray.direction);
	// result_ray.origin = &alive->cam.location;
	// return (result_ray);
	float			h;
	float			w;
	t_point_vector	vec_up;
	t_point_vector	vec_right;
	t_ray			result_ray;

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

// t_matrix	get_orientation_matrix(t_ranger *alive)
// {
// 	t_matrix			new;
// 	t_point_vector		look_up;

// 	look_up = (t_point_vector){0.0, 1.0, 0.0, 0};
// 	alive->cam.look_forward = vec_norm(&alive->cam.look_forward);
// 	alive->rend.look_right = cros_multiplication(&look_up, &alive->cam.look_forward);
// 	if (alive->cam.look_forward.y == 1.0)
// 		alive->rend.look_right.x = 1.0;
// 	alive->rend.look_right = vec_norm(&alive->rend.look_right);
// 	look_up = cros_multiplication(&alive->cam.look_forward, &alive->rend.look_right);
// 	alive->rend.look_up = vec_norm(&look_up);
// 	fill_identity_matrix(&new);
// 	new.matrix[0][0] = alive->rend.look_right.x;
// 	new.matrix[0][1] = alive->rend.look_right.y;
// 	new.matrix[0][2] = alive->rend.look_right.z;
// 	new.matrix[1][0] = alive->rend.look_up.x;
// 	new.matrix[1][1] = alive->rend.look_up.y;
// 	new.matrix[1][2] = alive->rend.look_up.z;
// 	new.matrix[2][0] = alive->cam.look_forward.x;
// 	new.matrix[2][1] = alive->cam.look_forward.y;
// 	new.matrix[2][2] = alive->cam.look_forward.z;
// 	return (new);
// }

void	get_camera_transform_matrix(t_ranger *alive)
{
	t_point_vector		look_up;

	look_up = (t_point_vector){0.0, 1.0, 0.0, 0};
	alive->cam.look_forward = vec_norm(&alive->cam.look_forward);
	alive->rend.look_right = cros_multiplication(&look_up, &alive->cam.look_forward);
	if (alive->cam.look_forward.y == 1.0)
		alive->rend.look_right.x = 1.0;
	alive->rend.look_right = vec_norm(&alive->rend.look_right);
	look_up = cros_multiplication(&alive->cam.look_forward, &alive->rend.look_right);
	alive->rend.look_up = vec_norm(&look_up);
	// t_matrix	orient_m;
	// t_matrix	transl_m;
	// t_matrix	transform;

	// orient_m = get_orientation_matrix(alive);
	// transl_m = get_translation_matrix(-1.0 * alive->cam.location.x,
	// 		-1.0 * alive->cam.location.y, -1.0 * alive->cam.location.z);
	// transform = matrices_multiplication(&orient_m, &transl_m);
	// alive->cam.transform = matrix_inverse(&transform);
}

t_hit_info	get_hit_object(t_ranger *alive, const t_ray *r)
{
	t_hit_info		inf;
	t_hit_info		tmp_inf;
	int				i;
	int				past_first;

	inf.hit_or_not = 0;
	inf.t = 0.0;
	inf.obj_id = -1;
	past_first = 0;
	i = -1;
	while (++i < alive->no_of_object)
	{
		if (alive->objcs[i].obj_type == sphere)
			tmp_inf = ray_sphare_intrsection(r, (t_sphere *)alive->objcs[i].the_obj);
		else if (alive->objcs[i].obj_type == plane)
			tmp_inf = ray_plane_intersection(r, (t_plane *)alive->objcs[i].the_obj);
		// else if (alive->objcs[i].obj_type == cylinder)
		// 	tmp_inf = ray_cylinder_intersect(r, (t_plane *)alive->objcs[i].the_obj);
		else
			printf("got uknown object\n");/////
		if (!past_first && tmp_inf.hit_or_not > 0)
		{
			inf.hit_or_not = 1;
			inf.t = tmp_inf.t;
			inf.obj_id = i;
			past_first++;
		}
		if (tmp_inf.hit_or_not > 0 && tmp_inf.t < inf.t)
		{
			inf.hit_or_not = 1;
			inf.t = tmp_inf.t;
			inf.obj_id = i;
		}
	}
	return (inf);
}
