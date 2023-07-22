/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymohamed <ymohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 20:52:50 by ymohamed          #+#    #+#             */
/*   Updated: 2023/07/23 01:58:55 by ymohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytrace.h"

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

// t_matrix	get_orientation_matrix(t_ranger *alive)
// {
// 	t_matrix			new;
// 	t_tuple		look_up;

// 	look_up = (t_tuple){0.0, 1.0, 0.0, 0};
// 	alive->cam.look_forward = vec_norm(&alive->cam.look_forward);
// 	alive->rend.look_right = cros_multiplication(&look_up,
			// &alive->cam.look_forward);
// 	if (alive->cam.look_forward.y == 1.0)
// 		alive->rend.look_right.x = 1.0;
// 	alive->rend.look_right = vec_norm(&alive->rend.look_right);
// 	look_up = cros_multiplication(&alive->cam.look_forward,
			// &alive->rend.look_right);
// 	alive->rend.look_up = vec_norm(&look_up);
// 	fill_identity_matrix(&new);
// 	new.matrix[0][0] = alive->rend.look_right.x;
// 	new.matrix[0][1] = alive->rend.look_right.y;
// 	new.matrix[0][2] = alive->rend.look_right.z;
// 	new.matrix[1][0] = alive->rend.look_up.x;
// 	new.matrix[1][1] = alive->rend.look_up.y;
// 	new.matrix[1][2] = alive->rend.look_up.z;
// 	new.matrix[2][0] = alive->cam.look_forward.x;
// 	new.matrix[2][1] = alive->cam.look_forward.y;
// 	new.matrix[2][2] = alive->cam.look_forward.z;
// 	return (new);
// }

// t_tuple	matrix_by_tuple(const t_matrix *m, 
// const t_tuple *tuple)
// {
// 	t_tuple	result_tuple;
// 	float			tmp[4];
// 	int				i;

// 	result_tuple = (t_tuple){0, 0, 0, 0};
// 	if (!m || !tuple)
// 		return (write(2, "Error multiplication matrix with tuple\n", 39),
// 			result_tuple);
// 	i = -1;
// 	while (++i < 4)
// 		tmp[i] = 0;
// 	i = -1;
// 	while (++i < 4)
// 		tmp[i] = m->matrix[i][0] * tuple->x
// 			+ m->matrix[i][1] * tuple->y
// 			+ m->matrix[i][2] * tuple->z
// 			+ m->matrix[i][3] * tuple->w;
// 	result_tuple.x = tmp[0];
// 	result_tuple.y = tmp[1];
// 	result_tuple.z = tmp[2];
// 	result_tuple.w = tmp[3];
// 	return (result_tuple);
// }
