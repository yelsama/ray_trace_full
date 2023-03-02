/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymohamed <ymohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 14:58:59 by ymohamed          #+#    #+#             */
/*   Updated: 2023/03/02 09:39:21 by ymohamed         ###   ########.fr       */
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
	int				clr;
	t_point_vector	camera;
	t_sphere		s;
	float			inf[5];
	int				y;
	int				x;
	t_ray			g_ray;
	t_ray			current_r;
	t_matrix		scale_m;
	t_point_vector	proj_wall;
	float			half;
	float			pixl_size;
	t_point_vector	on_screen;
	t_point_vector	hit_p;
	t_light			main_light;
	t_light			amb;

	alive->frame.frame_ptr = mlx_init();
	alive->frame.window = mlx_new_window(alive->frame.frame_ptr,
			400, 400, "mini_rt");
	if (!alive->frame.frame_ptr || !alive->frame.window)
		return (0);
	clr = 50;
	hit_p = (t_point_vector){0, 0, 0, 1};
	fill_point(&camera, 0.0, 0.0, -5.0);
	main_light.brightness = 0.8;
	main_light.color = (t_color){255.0, 255.0, 255.0};
	main_light.position = (t_point_vector){4.0, 5.0, -10.0, 1};
	amb.brightness = 0.2;
	amb.color = (t_color){255.0, 255.0, 255.0};
	on_screen = (t_point_vector){0, 0, 0, 1};
	s = fill_sphere((t_point_vector){0.0, 0.0, 0.0, 1.0}, 1, (t_color){200, 0, 200}, 7);
	g_ray =  fill_ray(&camera, (t_point_vector){0.0, 0.0, 15.0, 0});
	current_r =  fill_ray(&camera, (t_point_vector){0.0, 0.0, 15.0, 0.0});
	scale_m = get_scaling_matrix(1.0, 0.5, 1.0);
	proj_wall = (t_point_vector){0.0, 0.0, 20.0, 1.0};
	half = 14.0 / 2.0;
	pixl_size = 14.0 / 400.0;
	y = -1;
	while (++y < 400)
	{
		x = -1;
		while (++x < 400)
		{
			proj_wall.y = half - (pixl_size * y);
			proj_wall.x = pixl_size * x - half;
			on_screen.x = x;
			on_screen.y = y;
			// rotate_tuple(&proj_wall, y_axis, 20);
			// rotate_tuple(&proj_wall, z_axis, -20);
			g_ray.direction.x = proj_wall.x - camera.x;
			g_ray.direction.y = proj_wall.y - camera.y;
			g_ray.direction.z = proj_wall.z - camera.z;
			current_r.direction = vec_norm(&g_ray.direction);
			ray_sphare_intrsection(&current_r, &s, inf);
			if (inf[1] > 0)
			{
				hit_p.x = camera.x + (inf[2] * current_r.direction.x);
				hit_p.y = camera.y + (inf[2] * current_r.direction.y);
				hit_p.z = camera.z + (inf[2] * current_r.direction.z);
				clr = ligth_effect_on_sphere_pxl_color(hit_p, &s, &main_light, &amb);
				// reform_tupl_by_matrix(&scale_m, &hit_p);
				// mlx_pixel_put(alive->frame.frame_ptr, alive->frame.window, 200 + hit_p.x * (400 / 2) , 200 + hit_p.y * (400 / 2), c);
				mlx_pixel_put(alive->frame.frame_ptr, alive->frame.window, on_screen.x, on_screen.y, clr);
			}
		}
	}
	mlx_hook(alive->frame.window, 17, 0, exit_clear_window, alive);
	mlx_loop(alive->frame.frame_ptr);
	return (1);
}

void	test_ligt_shade_vectors(t_ranger *alive)
{
	// t_sphere		s;
	// t_point_vector	n_v;
	t_point_vector	v;
	t_point_vector	n;

	(void)alive;
	// s = fill_sphere((t_point_vector){0.0, 0, 0, 1}, 1.0, 7);
	// n_v = normal_vec_on_sphere(&s, (t_point_vector){0.0, 0.0, 1.0, 1});
	v = (t_point_vector){0, -1, 0, 0};
	n = (t_point_vector){sqrtf(2.0) / 2, sqrtf(2.0) / 2, 0, 0};
	// n_v = reflect_around_normal(&v, &n);
	// print_an_elemnt(&n_v);
}

int	main(void)
{
	t_ranger	alive;

	test_ligt_shade_vectors(&alive);
	if (1 && !create_amlx_window(&alive))
		return (write(2, "Error making main frame window\n", 31), 1);
	return (0);
}
//	we need to find hit points, and for each ray find the nearist in front
// intersection which I am going to call it hit.