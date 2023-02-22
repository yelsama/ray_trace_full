/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymohamed <ymohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 14:58:59 by ymohamed          #+#    #+#             */
/*   Updated: 2023/02/23 03:27:25 by ymohamed         ###   ########.fr       */
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
	t_color			clr;
	int				c;
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

	alive->frame.frame_ptr = mlx_init();
	alive->frame.window = mlx_new_window(alive->frame.frame_ptr,
			400, 400, "mini_rt");
	if (!alive->frame.frame_ptr || !alive->frame.window)
		return (0);
	clr = (t_color){255, 0, 255};
	c = rgb_to_int(&clr);
	fill_point(&camera, 0.0, 0.0, -5.0);
	on_screen = (t_point_vector){0, 0, 0, 1};
	s = fill_sphare((t_point_vector){0.0, 0.0, 0.0, 1.0}, 1, 39);
	g_ray =  fill_ray(&camera, (t_point_vector){0.0, 0.0, 15.0, 0});
	current_r =  fill_ray(&camera, (t_point_vector){0.0, 0.0, 15.0, 0.0});
	scale_m = get_scaling_matrix(0.5, 1.0, 1.0);
	proj_wall = (t_point_vector){0.0, 0.0, 10.0, 1.0};
	half = 7.0 / 2.0;
	pixl_size = 7.0 / 400.0;
	y = -1;
	while (++y < 400)
	{
		proj_wall.y = half - (pixl_size * y);
		on_screen.y = y;
		g_ray.direction.y = proj_wall.y - camera.y;
		x = -1;
		while (++x < 400)
		{
			proj_wall.x = pixl_size * x - half;
			on_screen.x = x;
			g_ray.direction.x = proj_wall.x - camera.x;
			current_r.direction = vec_norm(&g_ray.direction);
			ray_sphare_intrsection(&current_r, &s, inf);
			if (inf[1] > 0)
			{
				// on_screen.z = 1; // get z projection
				// rotate_tuple(&on_screen, z_axis, 45);
				// reform_tupl_by_matrix(&scale_m, &on_screen);
				mlx_pixel_put(alive->frame.frame_ptr, alive->frame.window, on_screen.x, on_screen.y, c);
			}
		}
	}
	mlx_hook(alive->frame.window, 17, 0, exit_clear_window, alive);
	mlx_loop(alive->frame.frame_ptr);
	return (1);
}

int	main(void)
{
	t_ranger	alive;

	if (!create_amlx_window(&alive))
		return (write(2, "Error making main frame window\n", 31), 1);
	return (0);
}
//	we need to find hit points, and for each ray find the nearist in front
// intersection which I am going to call it hit.