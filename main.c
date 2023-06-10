/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymohamed <ymohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 14:58:59 by ymohamed          #+#    #+#             */
/*   Updated: 2023/05/21 17:52:29 by ymohamed         ###   ########.fr       */
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
	t_sphere		s2;
	t_plane			p1;
	t_point_vector	hit_p;
	t_ray			current_r;
	float			s_inf[5];
	float			p_inf[5];
	int				x,y,clr;


	alive->frame.frame_ptr = mlx_init();
	alive->frame.window = mlx_new_window(alive->frame.frame_ptr,
			XBLOCK_DIM, YBLOCK_DIM, "mini_rt");
	if (!alive->frame.frame_ptr || !alive->frame.window)
		return (0);
	p1 = fill_plane((t_point_vector){0.0, 0.0, 100.0, 1}, (t_point_vector){0.0, 1.0, 0.0, 0},  (t_color){0, 200, 0}, 7);
	// s1 = fill_sphere((t_point_vector){13.0, 13.0, 80.0, 1}, 6.0, (t_color){0, 200, 200}, 7);
	s2 = fill_sphere((t_point_vector){0.0, 0.01, -10.0, 1}, 2.0, (t_color){255, 0, 0}, 7);
	// s3 = fill_sphere((t_point_vector){-13.0, 0.0, 80.0, 1}, 6.0, (t_color){50, 200, 0}, 7);
	current_r = fill_ray(&alive->cam.location, (t_point_vector){0.0, 0.0, 0.0, 0});
	hit_p.w = 1;

	y = -1;
	while (++y < YBLOCK_DIM)
	{
		x = -1;
		while (++x < XBLOCK_DIM)
		{
			current_r = ray_for_pixel(alive, x, y);
			// ray_sphare_intrsection(&current_r, &s1, inf);
			// if (inf[1] > 0)
			// {
			// 	hit_p.x = alive->cam.location.x + (inf[2] * current_r.direction.x);
			// 	hit_p.y = alive->cam.location.y + (inf[2] * current_r.direction.y);
			// 	hit_p.z = alive->cam.location.z + (inf[2] * current_r.direction.z);
			// 	clr = ligth_effect_on_sphere_pxl_color(hit_p, &s1, &alive->main_light, &alive->ambient);
			// 	mlx_pixel_put(alive->frame.frame_ptr, alive->frame.window, x, y, clr);
			// }
			// ray_sphare_intrsection(&current_r, &s3, inf);
			// if (inf[1] > 0)
			// {
			// 	hit_p.x = alive->cam.location.x + (inf[2] * current_r.direction.x);
			// 	hit_p.y = alive->cam.location.y + (inf[2] * current_r.direction.y);
			// 	hit_p.z = alive->cam.location.z + (inf[2] * current_r.direction.z);
			// 	clr = ligth_effect_on_sphere_pxl_color(hit_p, &s3, &alive->main_light, &alive->ambient);
			// 	mlx_pixel_put(alive->frame.frame_ptr, alive->frame.window, x, y, clr);
			// }
			ray_sphare_intrsection(&current_r, &s2, s_inf);
			ray_plane_intersection(&current_r, &p1, p_inf);
			if (s_inf[1] > 0 && (s_inf[2] < p_inf[2] || !p_inf[1]))
			{
				hit_p.x = alive->cam.location.x + (s_inf[2] * current_r.direction.x);
				hit_p.y = alive->cam.location.y + (s_inf[2] * current_r.direction.y);
				hit_p.z = alive->cam.location.z + (s_inf[2] * current_r.direction.z);
				clr = ligth_effect_on_sphere_pxl_color(hit_p, &s2, &alive->main_light, &alive->ambient);
				mlx_pixel_put(alive->frame.frame_ptr, alive->frame.window, x, y, clr);
			}
			else if (p_inf[1] > 0)
			{
				hit_p.x = alive->cam.location.x + (p_inf[2] * current_r.direction.x);
				hit_p.y = alive->cam.location.y + (p_inf[2] * current_r.direction.y);
				hit_p.z = alive->cam.location.z + (p_inf[2] * current_r.direction.z);
				clr = light_effect_on_plane_pxl_color(hit_p, &p1, &alive->main_light, &alive->ambient);
				mlx_pixel_put(alive->frame.frame_ptr, alive->frame.window, x, y, clr);
			}
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
	alive->cam.location = (t_point_vector){0.0, 0.0, 9.0, 1};
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