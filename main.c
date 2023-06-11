/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymohamed <ymohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 14:58:59 by ymohamed          #+#    #+#             */
/*   Updated: 2023/06/11 18:52:46 by ymohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytrace.h"

int	exit_clear_window(t_ranger *alive)
{
	mlx_clear_window(alive->frame.frame_ptr, alive->frame.window);
	mlx_destroy_window(alive->frame.frame_ptr, alive->frame.window);
	exit(0);
	return (0);
}

int	create_amlx_window(t_ranger *alive)
{
	t_point_vector	hit_p;
	t_ray			current_r;
	t_hit_info	hit_info;
	int				x,y,clr;


	alive->frame.frame_ptr = mlx_init();
	alive->frame.window = mlx_new_window(alive->frame.frame_ptr,
			XBLOCK_DIM, YBLOCK_DIM, "mini_rt");
	if (!alive->frame.frame_ptr || !alive->frame.window)
		return (0);
	current_r = fill_ray(&alive->cam.location, (t_point_vector){0.0, 0.0, 0.0, 0});
	hit_p.w = 1;

	(void)clr;
	y = -1;
	while (++y < YBLOCK_DIM)
	{
		x = -1;
		while (++x < XBLOCK_DIM)
		{
			current_r = ray_for_pixel(alive, x, y);
			hit_info = get_hit_object(alive, &current_r);
			if (!hit_info.hit_or_not)
				continue;

			hit_p.x = alive->cam.location.x + (hit_info.t * current_r.direction.x);
			hit_p.y = alive->cam.location.y + (hit_info.t * current_r.direction.y);
			hit_p.z = alive->cam.location.z + (hit_info.t * current_r.direction.z);
			if (alive->objcs[hit_info.obj_id].obj_type == sphere)
				clr = ligth_effect_on_sphere_pxl_color(hit_p, (t_sphere *)alive->objcs[hit_info.obj_id].the_obj, &alive->main_light, &alive->ambient);
			else if (alive->objcs[hit_info.obj_id].obj_type == plane)
				clr = light_effect_on_plane_pxl_color(hit_p, (t_plane *)alive->objcs[hit_info.obj_id].the_obj, &alive->main_light, &alive->ambient);
			else
				continue;	
			mlx_pixel_put(alive->frame.frame_ptr, alive->frame.window, x, y, clr);
		}
	}
	mlx_hook(alive->frame.window, 17, 0, exit_clear_window, alive);
	mlx_loop(alive->frame.frame_ptr);
	return (1);
}

//##########################################################

void	fill_initial_values(t_ranger *alive)
{
	alive->cam.field_of_view = 60;
	alive->cam.location = (t_point_vector){0.0, 1.0, 9.0, 1};
	alive->cam.look_forward = (t_point_vector){0.0, 0.0, -1.0, 0};
	alive->main_light.position = (t_point_vector){10.0, 10.0, 4.0, 1};
	alive->main_light.brightness = 0.8;
	alive->main_light.color = (t_color){255, 255, 255};
	alive->ambient.brightness = 0.2;
	alive->ambient.color = (t_color){255, 255, 255};
	get_camera_transform_matrix(alive);
}

int	main(void)
{
	t_ranger	alive;
	// t_ray		test;

	alive.error = 0;
	fill_initial_values(&alive);
	set_camera(&alive);
	set_objects(&alive);
	// test = ray_for_pixel(&alive, 100, 50);
	// print_an_elemnt(&test.direction);
	if (1 && !create_amlx_window(&alive))
		return (write(1, "Error making main frame window\n", 31), 1);
	return (0);
}
// we need to find hit points, and for each ray find the nearist in front
// intersection which I am going to call it hit.
	// test = ray_for_pixel(&alive, 0, 0);
	// print_an_elemnt(&test.direction);
//for plane t = (op - plane point) dot n / (v dot n)