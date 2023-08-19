/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohouhou <mohouhou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 14:58:59 by ymohamed          #+#    #+#             */
/*   Updated: 2023/08/19 18:53:53 by mohouhou         ###   ########.fr       */
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
	t_tuple			hit_p;
	t_ray			current_r;
	t_hit_info		hit_info;
	int				x[3];


	alive->frame.frame_ptr = mlx_init();
	alive->frame.window = mlx_new_window(alive->frame.frame_ptr,
			XBLOCK_DIM, YBLOCK_DIM, "mini_rt");
	if (!alive->frame.frame_ptr || !alive->frame.window)
		return (0);
	current_r = fill_ray(&alive->cam.location, (t_tuple){0.0, 0.0, 0.0, 0});
	hit_p.w = 1;

	(void)x[2];
	x[1] = -1;
	while (++x[1] < YBLOCK_DIM)
	{
		x[0] = -1;
		while (++x[0] < XBLOCK_DIM)
		{
			current_r = ray_for_pixel(alive, x[0], x[1]);
			hit_info = get_hit_object(alive, &current_r);
			if (!hit_info.hit_or_not)
				continue ;
			p0_plus_t_mul_v(&hit_p, &alive->cam.location, &current_r.direction, hit_info.t);
			if (alive->objcs[hit_info.obj_id].obj_type == sphere)
				x[2] = ligth_effect_on_sphere_pxl_color(alive, hit_p, hit_info.obj_id);
			else if (alive->objcs[hit_info.obj_id].obj_type == plane)
				x[2] = light_effect_on_plane_pxl_color(alive, hit_p, hit_info.obj_id);
			else if (alive->objcs[hit_info.obj_id].obj_type == cylinder)
				x[2] = light_effect_on_cylndr_pxl_color(alive, hit_p, hit_info.obj_id);
			else
				continue;	
			mlx_pixel_put(alive->frame.frame_ptr, alive->frame.window, x[0], x[1], x[2]);
		}
	}
	mlx_hook(alive->frame.window, 17, 0, exit_clear_window, alive);
	mlx_hook(alive->frame.window, 2, 0, exit_clear_window, alive);
	mlx_loop(alive->frame.frame_ptr);
	free_objects(alive);
	return (1);
}

void	fill_initial_values(t_ranger *alive)
{
	alive->light_appear_clr = color_multi_scalar(&alive->main_light.color,
			alive->main_light.brightness);
	alive->amb_appear_clr = color_multi_scalar(&alive->ambient.color,
			alive->ambient.brightness);
	get_camera_transform_matrix(alive);
}

int	main(int ac, char **av)
{
	t_ranger	alive;

	alive.error = 0;
	(void)ac;
	parsing(&alive, av);
	fill_initial_values(&alive);
	set_camera(&alive);
	if (1 && !create_amlx_window(&alive))
		return (write(1, "Error making main frame window\n", 31), 1);
	return (0);
}
