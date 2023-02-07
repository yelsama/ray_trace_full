/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymohamed <ymohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 14:58:59 by ymohamed          #+#    #+#             */
/*   Updated: 2023/02/07 19:37:42 by ymohamed         ###   ########.fr       */
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

void	drawer(t_point_vector *p_current, t_color *clr, t_batch	*can, t_ranger *alive)
{
	fill_batch(can, clr, p_current->x, YBLOCK_DIM - p_current->y);
	paint_batch_at_mlx(can, alive);
}

int	create_amlx_window(t_ranger *alive)
{
	t_batch			can;
	t_color			clr;
	t_point_vector origin;
	t_point_vector	p_current;
	t_point_vector move_from_origin;
	int				i;

	alive->frame.frame_ptr = mlx_init();
	alive->frame.window = mlx_new_window(alive->frame.frame_ptr,
			XBLOCK_DIM, YBLOCK_DIM, "mini_rt");
	if (!alive->frame.frame_ptr || !alive->frame.window)
		return (0);
	fill_color(&clr, 255, 0, 255);
	if (!fill_point(&origin, 450, 300, 300) || !fill_vector(&move_from_origin, 0, 100, 0))
		return (0);
	// drawer(&origin, &clr, &can, alive);
	p_current = point_from_point_vector(&origin, &move_from_origin);
	// rotate_tuple(&move_from_origin, x_axis, 45);
	drawer(&p_current, &clr, &can, alive);
	i = -1;
	while (++i < 12)
	{
		// rotate_tuple(&move_from_origin, y_axis, 30);
		// rotate_tuple(&move_from_origin, x_axis, 30);
		rotate_tuple(&move_from_origin, z_axis, 30);
		p_current = point_from_point_vector(&origin, &move_from_origin);
		drawer(&p_current, &clr, &can, alive);
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
