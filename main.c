/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymohamed <ymohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 14:58:59 by ymohamed          #+#    #+#             */
/*   Updated: 2023/03/05 22:32:47 by ymohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytrace.h"

// int	exit_clear_window(t_ranger *alive)
// {
// 	mlx_clear_window(alive->frame.frame_ptr, alive->frame.window);
// 	mlx_destroy_window(alive->frame.frame_ptr, alive->frame.window);
// 	exit(0);
// 	return (0);
// }

// int	create_amlx_window(t_ranger *alive)
// {
// 	t_sphere		s;
// 	t_point_vector	hit_p;
// 	t_point_vector	proj_window;
// 	t_ray			g_ray;
// 	t_ray			current_r;
// 	float			inf[5];
// 	int				x,y,clr;


// 	alive->frame.frame_ptr = mlx_init();
// 	alive->frame.window = mlx_new_window(alive->frame.frame_ptr,
// 			XBLOCK_DIM, YBLOCK_DIM, "mini_rt");
// 	if (!alive->frame.frame_ptr || !alive->frame.window)
// 		return (0);
// 	hit_p = (t_point_vector){0.0, 0.0, 0.0, 1};
// 	s = fill_sphere((t_point_vector){0.0, 0.0, 20.0, 1}, 1.0, (t_color){200, 0, 200}, 7);
// 	g_ray =  fill_ray(&alive->cam.location, alive->cam.orint_vec);
// 	current_r = fill_ray(&alive->cam.location, alive->cam.orint_vec);
// 	proj_window.w = 0;
// 	proj_window.z = alive->cam.orint_vec.z;

// 	y = -1;
// 	while (++y < YBLOCK_DIM)
// 	{
// 		x = -1;
// 		while (++x < XBLOCK_DIM)
// 		{
// 			proj_window.y = alive->rend.half_heigh - (alive->rend.pixel_size * y);
// 			// proj_window.y = half - (pixl_size * y);
// 			proj_window.x = alive->rend.pixel_size * x - alive->rend.half_width;
// 			// proj_window.x = pixl_size * x - half;
// 			g_ray.direction.x =	proj_window.x - alive->cam.location.x;
// 			g_ray.direction.y =	proj_window.y - alive->cam.location.y;
// 			g_ray.direction.z =	proj_window.z - alive->cam.location.z;
// 			current_r.direction = vec_norm(&g_ray.direction);
// 			ray_sphare_intrsection(&current_r, &s, inf);
// 			// exit (0);
// 			if (inf[1] > 0)
// 			{
// 				hit_p.x = alive->cam.location.x + (inf[2] * current_r.direction.x);
// 				hit_p.y = alive->cam.location.y + (inf[2] * current_r.direction.y);
// 				hit_p.z = alive->cam.location.z + (inf[2] * current_r.direction.z);
// 				clr = ligth_effect_on_sphere_pxl_color(hit_p, &s, &alive->main_light, &alive->ambient);
// 				mlx_pixel_put(alive->frame.frame_ptr, alive->frame.window, x, y, clr);
// 			}
// 		}
// 	}
// 	mlx_hook(alive->frame.window, 17, 0, exit_clear_window, alive);
// 	mlx_loop(alive->frame.frame_ptr);
// 	return (1);
// }

// void	test_cam(t_ranger *alive)
// {
// 	print_an_elemnt(alive->cam.)
// }
//##########################################################

void	fill_initial_values(t_ranger *alive)
{
	// t_matrix	orinetation_transform;
	// t_matrix	translation;

	alive->cam.field_of_view = 60;
	alive->cam.location = (t_point_vector){0.0, 0.0, 0.0, 1};
	alive->cam.look_forward = (t_point_vector){0.0, 1.0, 0.0, 0};
	get_camera_transform_matrix(alive);
}

int	main(void)
{
	t_ranger	alive;
	// t_ray		test;

	alive.error = 0;
	fill_initial_values(&alive);
	set_camera(&alive);
	ray_for_pixel(&alive, 600, 400);
	// print_an_elemnt(&test.direction);
	// print_an_elemnt(test.origin);
	// if (0 && !create_amlx_window(&alive))
	// 	return (write(2, "Error making main frame window\n", 31), 1);
	return (0);
}
//	we need to find hit points, and for each ray find the nearist in front
// intersection which I am going to call it hit.