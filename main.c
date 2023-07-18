/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymohamed <ymohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 14:58:59 by ymohamed          #+#    #+#             */
/*   Updated: 2023/07/18 13:34:57 by ymohamed         ###   ########.fr       */
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
	t_hit_info		hit_info;
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
			p0_plus_t_mul_v(&hit_p, &alive->cam.location, &current_r.direction, hit_info.t);
			if (alive->objcs[hit_info.obj_id].obj_type == sphere)
				clr = ligth_effect_on_sphere_pxl_color(alive, hit_p, hit_info.obj_id);
			else if (alive->objcs[hit_info.obj_id].obj_type == plane)
				clr = light_effect_on_plane_pxl_color(alive, hit_p, hit_info.obj_id);
			else if (alive->objcs[hit_info.obj_id].obj_type == cylinder)
				clr = light_effect_on_cylndr_pxl_color(alive, hit_p, hit_info.obj_id);
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
	// alive->cam.field_of_view = 40;
	// alive->cam.location = (t_point_vector){0.0, 0.0, 30.0, 1};
	// alive->cam.look_forward = (t_point_vector){0.0, 0.0, -1.0, 0};
	// alive->main_light.position = (t_point_vector){-4.0, 10.0, 4.0, 1};
	// alive->main_light.brightness = 0.8;
	// alive->main_light.color = (t_color){255, 255, 255};
	// alive->ambient.brightness = 0.2;
	// alive->ambient.color = (t_color){255, 255, 255};
	alive->light_appear_clr = color_multi_scalar(&alive->main_light.color, alive->main_light.brightness);
	alive->amb_appear_clr = color_multi_scalar(&alive->ambient.color, alive->ambient.brightness);
	get_camera_transform_matrix(alive);
}

int	main(int ac, char **av)
{
	t_ranger	alive;

	alive.error = 0;
	(void)ac;
	parsing(&alive, av);
	printf("%d\n", alive.no_of_object);
	fill_initial_values(&alive);
	set_camera(&alive);
	// set_objects(&alive);
	if (1 && !create_amlx_window(&alive))
		return (write(1, "Error making main frame window\n", 31), 1);
	return (0);
}
// we need to find hit points, and for each ray find the nearist in front
// intersection which I am going to call it hit.
	// test = ray_for_pixel(&alive, 0, 0);
	// print_an_elemnt(&test.direction);
//for plane t = (op - plane point) dot n / (v dot n)