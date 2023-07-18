/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_4_4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymohamed <ymohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 16:37:10 by ymohamed          #+#    #+#             */
/*   Updated: 2023/07/18 21:03:38 by ymohamed         ###   ########.fr       */
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
			m->matrix[i][j] = 0.0;
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
				m->matrix[i][j] = 1.0;
			else
				m->matrix[i][j] = 0.0;
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
