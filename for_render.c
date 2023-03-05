/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymohamed <ymohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 12:42:11 by ymohamed          #+#    #+#             */
/*   Updated: 2023/03/05 22:32:20 by ymohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytrace.h"

void	set_camera(t_ranger *alive)
{
	float	half_szie;

	half_szie = tanf((alive->cam.field_of_view / 2) * DEGTORAD);
	alive->cam.aspect_ratio = (XBLOCK_DIM * 1.0) / (YBLOCK_DIM * 1.0);
	if (alive->cam.aspect_ratio >= 1.0)
	{
		alive->cam.half_width = half_szie;
		alive->cam.half_height = half_szie / alive->cam.aspect_ratio;
	}
	else
	{
		alive->cam.half_height = half_szie;
		alive->cam.half_width = half_szie * alive->cam.aspect_ratio;
	}
	alive->cam.pixel_size = (alive->cam.half_width * 2.0) / XBLOCK_DIM;
}

t_ray	ray_for_pixel(t_ranger *alive, int x, int y)
{
	t_ray			result_ray;
	t_point_vector	wall_point;
	// t_point_vector	on_world_v;
	// t_matrix		translation;
	// t_matrix		transform;
	// t_matrix		transform_inv;

	wall_point.w = 1;
	wall_point.x = (x * alive->cam.pixel_size) - alive->cam.half_width;
	wall_point.y = alive->cam.half_height - (y * alive->cam.pixel_size);
	wall_point.z = 1.0;
	
	// // translation = get_translation_matrix(-wall_point.x, -wall_point.y, -wall_point.z);
	// transform = matrices_multiplication(&alive->cam.orientation, &translation);
	// transform_inv = matrix_inverse(&transform);

	// on_world_v.w = 1;
	// on_world_v.x = -1.0 * wall_point.x;
	// on_world_v.y = -1.0 * wall_point.y;
	// on_world_v.z = -1.0 * wall_point.z;


	print_an_elemnt(&wall_point);
	reform_tupl_by_matrix(&alive->cam.transform, &wall_point);
	print_an_elemnt(&wall_point);
	exit(0);
	
	// reform_tupl_by_matrix(&transform_inv, &on_world_v);
	// print_an_elemnt(&on_world_v);

	// reform_tupl_by_matrix(&transform_inv, &wall_point);
	// print_an_elemnt(&wall_point);
	// reform_tupl_by_matrix(&transform_inv, &on_world_v);

	// result_ray.direction = get_vec_a_to_b(result_ray.origin, &wall_point);
	// result_ray.direction = vec_norm(&result_ray.direction);
	// 
	// result_ray = fill_ray(&on_world_v, wall_point);
	return (result_ray);
}

t_matrix	get_orientation_matrix(t_ranger *alive)
{
	t_matrix			new;
	t_point_vector		look_up;
	t_point_vector		look_left;

	look_up = (t_point_vector){0.0, 1.0, 0.0, 0};
	alive->cam.look_forward = vec_norm(&alive->cam.look_forward);
	look_left = cros_multiplication(&look_up, &alive->cam.look_forward);
	if (alive->cam.look_forward.y == 1.0)
		look_left.x = 1.0;
	look_left = vec_norm(&look_left);
	look_up = cros_multiplication(&alive->cam.look_forward, &look_left);
	look_up = vec_norm(&look_up);
	fill_identity_matrix(&new);
	new.matrix[0][0] = look_left.x;
	new.matrix[0][1] = look_left.y;
	new.matrix[0][2] = look_left.z;
	new.matrix[1][0] = look_up.x;
	new.matrix[1][1] = look_up.y;
	new.matrix[1][2] = look_up.z;
	new.matrix[2][0] = alive->cam.look_forward.x;
	new.matrix[2][1] = alive->cam.look_forward.y;
	new.matrix[2][2] = alive->cam.look_forward.z;
	return (new);
}

void	get_camera_transform_matrix(t_ranger *alive)
{
	t_matrix	orient_m;
	t_matrix	transl_m;
	t_matrix	transform;

	orient_m = get_orientation_matrix(alive);
	transl_m = get_translation_matrix(1.0 * alive->cam.location.x,
			-1.0 * alive->cam.location.y, -1.0 * alive->cam.location.z);
	transform = matrices_multiplication(&orient_m, &transl_m);
	alive->cam.transform = matrix_inverse(&transform);
}
