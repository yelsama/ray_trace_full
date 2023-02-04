/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymohamed <ymohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 14:58:59 by ymohamed          #+#    #+#             */
/*   Updated: 2023/02/04 04:20:41 by ymohamed         ###   ########.fr       */
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
// 	t_batch			can;
// 	t_color			clr;
// 	t_point_vector	p_current;
// 	t_point_vector	v_vlocity;
// 	t_point_vector 	v_final_act;
// 	t_point_vector	v_env_wind;
// 	t_point_vector	v_env_gravity;
// 	t_point_vector	v_wind_gravity_act;

// 	alive->frame.frame_ptr = mlx_init();
// 	alive->frame.window = mlx_new_window(alive->frame.frame_ptr,
// 			XBLOCK_DIM, YBLOCK_DIM, "mini_rt");
// 	if (!alive->frame.frame_ptr || !alive->frame.window)
// 		return (0);
// 	fill_color(&clr, 255, 0, 255);
// 	if (!fill_point(&p_current, 0, 1, 0))
// 		return (0);
// 	if (!fill_vector(&v_vlocity, 1, 1.8, 0)
// 		|| !fill_vector(&v_env_wind, -0.01, 0, 0)
// 		|| !fill_vector(&v_env_gravity, 0, -0.1, 0))
// 		return (0);
// 	v_wind_gravity_act = add_vectors(&v_env_gravity, &v_env_wind);
// 	v_vlocity = vec_norm(&v_vlocity);
// 	v_vlocity = rescale_vecotr(&v_vlocity, 10.0);
// 	print_an_elemnt(&v_wind_gravity_act);
// 	v_final_act = add_vectors(&v_wind_gravity_act, &v_vlocity);
// 	int i = 1;
// 	while (p_current.y > 0)
// 	{
// 		printf("this is tick %d\n", i);
// 		p_current = point_from_point_vector(&p_current, &v_final_act);
// 		v_final_act = add_vectors(&v_final_act, &v_wind_gravity_act);
// 		print_an_elemnt(&p_current);
// 		fill_batch(&can, &clr, p_current.x, YBLOCK_DIM - p_current.y);
// 		paint_batch_at_mlx(&can, alive);
// 		i++;
// 		printf("####################################\n");
// 	}
// 	mlx_hook(alive->frame.window, 17, 0, exit_clear_window, alive);
// 	mlx_loop(alive->frame.frame_ptr);
// 	return (1);
// }

// int	main(void)
// {
// 	t_ranger	alive;

// 	if (!create_amlx_window(&alive))
// 		return (write(2, "Error making main frame window\n", 31), 1);
// 	return (0);
// }

void	print_matrix(const t_matrix *m)
{
	int	i;
	int	j;

	i = -1;
	printf("matrix is:\n");
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
			printf("%.5f  ", m->matrix[i][j]);
		printf("\n");
	}
}

int	main(void)
{
	t_matrix	a;
	t_matrix	b;
	t_matrix	inv_a;
	// t_matrix	inv_b;
	t_matrix	c;
	t_matrix	d;

	a.matrix[0][0] = 3;
	a.matrix[0][1] = -9;
	a.matrix[0][2] = 7;
	a.matrix[0][3] = 3;
	a.matrix[1][0] = 3;
	a.matrix[1][1] = -8;
	a.matrix[1][2] = 2;
	a.matrix[1][3] = -9;
	a.matrix[2][0] = -4;
	a.matrix[2][1] = 4;
	a.matrix[2][2] = 4;
	a.matrix[2][3] = 1;
	a.matrix[3][0] = -6;
	a.matrix[3][1] = -2;
	a.matrix[3][2] = 0;
	a.matrix[3][3] = -5;
	printf("this is A ");
	print_matrix(&a);
	b.matrix[0][0] = 8;
	b.matrix[0][1] = 2;
	b.matrix[0][2] = 2;
	b.matrix[0][3] = 2;
	b.matrix[1][0] = 3;
	b.matrix[1][1] = -1;
	b.matrix[1][2] = 7;
	b.matrix[1][3] = 0;
	b.matrix[2][0] = 7;
	b.matrix[2][1] = 0;
	b.matrix[2][2] = 5;
	b.matrix[2][3] = 4;
	b.matrix[3][0] = 6;
	b.matrix[3][1] = -2;
	b.matrix[3][2] = 0;
	b.matrix[3][3] = 5;
	printf("this is B ");
	print_matrix(&b);
	c = matrices_multiplication(&a, &b);
	printf("this is C ");
	print_matrix(&c);
	inv_a = matrix_inverse(&a);
	printf("this is inv a");
	print_matrix(&inv_a);
	d = matrices_multiplication(&inv_a, &c);
	printf("this is D ");
	print_matrix(&d);
	return (0);
}
