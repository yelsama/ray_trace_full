/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrices.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymohamed <ymohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 16:37:10 by ymohamed          #+#    #+#             */
/*   Updated: 2023/02/02 22:30:35 by ymohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytrace.h"

int	fill_zero_matrix(t_matrix *m)
{
	int	i;
	int	j;

	if (!m)
		return (write(2, "Error filling matrix\n", 21), 0);
	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
			m->matrix[i][j] = 0;
	}
	if (i == 4 && j == 4)
		return (1);
	return (0);
}

int	fill_identity_matrix(t_matrix *m)
{
	int	i;
	int	j;

	if (!m)
		return (write(2, "Error filling matrix\n", 21), 0);
	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
		{
			if (j == i)
				m->matrix[i][j] = 1;
			else
				m->matrix[i][j] = 0;
		}
	}
	if (i == 4 && j == 4)
		return (1);
	return (0);
}

t_matrix	matrices_multiplication(const t_matrix *m1, const t_matrix *m2)
{
	t_matrix	result_mat;
	int			r;
	int			c;

	fill_zero_matrix(&result_mat);
	if (!m1 || !m2)
		return (write(2, "Errot multiplying matrices\n", 27), result_mat);
	r = -1;
	while (++r < 4)
	{
		c = -1;
		while (++c < 4)
			result_mat.matrix[r][c] = m1->matrix[r][0] * m2->matrix[0][c]
				+ m1->matrix[r][1] * m2->matrix[1][c]
				+ m1->matrix[r][2] * m2->matrix[2][c]
				+ m1->matrix[r][3] * m2->matrix[3][c];
	}
	return (result_mat);
}

t_point_vector	matrix_by_tuple(const t_matrix *m, const t_point_vector *tuple)
{
	t_point_vector	result_tuple;
	float			tmp[4];
	int				i;

	result_tuple = (t_point_vector){0, 0, 0, 0};
	if (!m || !tuple)
		return (write(2, "Error multiplication matrix with tuple\n", 39),
			result_tuple);
	i = -1;
	while (++i < 4)
		tmp[i] = 0;
	i = -1;
	while (++i < 4)
		tmp[i] = m->matrix[i][0] * tuple->x
			+ m->matrix[i][1] * tuple->y
			+ m->matrix[i][2] * tuple->z
			+ m->matrix[i][3] * tuple->w;
	result_tuple.x = tmp[0];
	result_tuple.y = tmp[1];
	result_tuple.z = tmp[2];
	result_tuple.w = tmp[3];
	return (result_tuple);
}
