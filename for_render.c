/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymohamed <ymohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 12:42:11 by ymohamed          #+#    #+#             */
/*   Updated: 2023/07/18 21:44:32 by ymohamed         ###   ########.fr       */
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

void	get_camera_transform_matrix(t_ranger *alive)
{
	t_point_vector		look_up;

	print_an_elemnt(&alive->cam.look_forward);
	look_up = (t_point_vector){0.0, 1.0, 0.0, 0};
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
		else if (alive->objcs[i].obj_type == cylinder)
			tmp_inf = ray_cylinder_intersect(r, (t_cylndr *)alive->objcs[i].the_obj);
		else
			printf("got uknown object at for_render\n");/////
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
