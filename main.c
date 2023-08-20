/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymohamed <ymohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 14:58:59 by ymohamed          #+#    #+#             */
/*   Updated: 2023/08/20 23:02:28 by ymohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytrace.h"

int	exit_clear_window(t_ranger *alive)
{
	free_objects(alive);
	mlx_clear_window(alive->frame.frame_ptr, alive->frame.window);
	mlx_destroy_window(alive->frame.frame_ptr, alive->frame.window);
	exit(0);
	return (0);
}

int	key_check(int key, t_ranger *alive)
{
	if (key == 53)
		exit_clear_window(alive);
	return (0);
}

static void	loop_in_x_and_plot(t_ranger *alive, t_ray *current_r,
t_tuple *hit_p, int *x)
{
	t_hit_info	hit_info;

	x[0] = -1;
	while (++x[0] < XBLOCK_DIM)
	{
		*current_r = ray_for_pixel(alive, x[0], x[1]);
		hit_info = get_hit_object(alive, current_r);
		if (!hit_info.hit_or_not)
			continue ;
		p0_plus_t_mul_v(hit_p, &alive->cam.location,
			&current_r->direction, hit_info.t);
		if (alive->objcs[hit_info.obj_id].obj_type == sphere)
			x[2] = ligth_effect_on_sphere_pxl_color(alive, *hit_p,
					hit_info.obj_id);
		else if (alive->objcs[hit_info.obj_id].obj_type == plane)
			x[2] = light_effect_on_plane_pxl_color(alive,
					*hit_p, hit_info.obj_id);
		else if (alive->objcs[hit_info.obj_id].obj_type == cylinder)
			x[2] = light_effect_on_cylndr_pxl_color(alive, *hit_p,
					hit_info.obj_id);
		else
			continue ;
		mlx_pixel_put(alive->frame.frame_ptr,
			alive->frame.window, x[0], x[1], x[2]);
	}
}

int	create_amlx_window(t_ranger *alive)
{
	t_tuple			hit_p;
	t_ray			current_r;
	int				x[3];

	alive->frame.frame_ptr = mlx_init();
	if (!alive->frame.frame_ptr)
		return (0);
	alive->frame.window = mlx_new_window(alive->frame.frame_ptr,
			XBLOCK_DIM, YBLOCK_DIM, "mini_rt");
	if (!alive->frame.window)
		return (0);
	current_r = fill_ray(&alive->cam.location, (t_tuple){0.0, 0.0, 0.0, 0});
	hit_p = (t_tuple){0.0, 0.0, 0.0, 1};
	x[1] = -1;
	while (++x[1] < YBLOCK_DIM && !alive->cam_in_obj)
		loop_in_x_and_plot(alive, &current_r, &hit_p, x);
	mlx_hook(alive->frame.window, 17, 0, exit_clear_window, alive);
	mlx_hook(alive->frame.window, 2, 0, key_check, alive);
	mlx_loop(alive->frame.frame_ptr);
	return (1);
}

int	main(int ac, char **av)
{
	t_ranger	alive;

	alive.error = 0;
	alive.cam_in_obj = 0;
	if (ac != 2)
		return (write(2, "Error: Wrong number of arguments\n", 34), 1);
	exam_the_map_file(av[1], ".rt");
	parsing(&alive, av);
	check_vectors(&alive);
	alive.cam_in_obj = verify_camera_inside(&alive);
	alive.light_appear_clr = color_multi_scalar(&alive.main_light.color,
			alive.main_light.brightness);
	alive.amb_appear_clr = color_multi_scalar(&alive.ambient.color,
			alive.ambient.brightness);
	get_camera_transform_matrix(&alive);
	set_camera(&alive);
	if (!create_amlx_window(&alive))
		return (write(2, "Error making main frame window\n", 31), 1);
	return (0);
}
