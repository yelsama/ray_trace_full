/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymohamed <ymohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 14:58:59 by ymohamed          #+#    #+#             */
/*   Updated: 2023/02/22 16:35:17 by ymohamed         ###   ########.fr       */
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
	t_ray			current_r;

	alive->frame.frame_ptr = mlx_init();
	alive->frame.window = mlx_new_window(alive->frame.frame_ptr,
			XBLOCK_DIM, YBLOCK_DIM, "mini_rt");
	if (!alive->frame.frame_ptr || !alive->frame.window)
		return (0);
	fill_color(&clr, 255, 0, 255);
	c = rgb_to_int(&clr);
	fill_point(&camera, 600, 400, 1500);
	s = fill_sphare((t_point_vector){600, 400, 0, 1}, 100, 39);
	y = -1;
	current_r =  fill_ray(&camera, (t_point_vector){0, 0, -1 * camera.z , 0});
	while (++y < YBLOCK_DIM)
	{
		current_r.direction.y = y - camera.y;
		x = -1;
		while (++x < XBLOCK_DIM)
		{
			current_r.direction.x = x - camera.x;
			ray_sphare_intrsection(&current_r, &s, inf);
			if (inf[1] > 0)
				mlx_pixel_put(alive->frame.frame_ptr, alive->frame.window, x, y, c);
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