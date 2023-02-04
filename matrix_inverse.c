/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_inverse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymohamed <ymohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 19:44:13 by ymohamed          #+#    #+#             */
/*   Updated: 2023/02/04 03:30:16 by ymohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytrace.h"

#define N 4

// calculates the determinants of a 3x3 matrix
float	det3(const t_matrix *mat)
{
	float	det;

	det = mat->matrix[0][0] * (mat->matrix[1][1]
			* mat->matrix[2][2] - mat->matrix[1][2] * mat->matrix[2][1])
		- mat->matrix[0][1] * (mat->matrix[1][0]
			* mat->matrix[2][2] - mat->matrix[1][2] * mat->matrix[2][0])
		+ mat->matrix[0][2] * (mat->matrix[1][0]
			* mat->matrix[2][1] - mat->matrix[1][1] * mat->matrix[2][0]);
	return (det);
}

// calculates the final determinant for 4x4 matrix
float	detr(const t_matrix *cof, const t_matrix *mat)
{
	float	det;

	det = cof->matrix[0][0] * mat->matrix[0][0]
		+ cof->matrix[1][0] * mat->matrix[0][1]
		+ cof->matrix[2][0] * mat->matrix[0][2]
		+ cof->matrix[3][0] * mat->matrix[0][3];
	return (det);
}

void	get_submatrix(const t_matrix *mat, int u_i, int u_j, t_matrix *sub)
{
	int	n[4];

	n[0] = 0;
	n[1] = -1;
	while (++n[1] < N)
	{
		if (n[1] == u_j)
			continue ;
		n[2] = 0;
		n[3] = -1;
		while (++n[3] < N)
		{
			if (n[3] == u_i)
				continue ;
			sub->matrix[n[0]][n[2]] = mat->matrix[n[1]][n[3]];
			n[2]++;
		}
		n[0]++;
	}
}

void	cofactor(const t_matrix *mat, t_matrix *cof)
{
	t_matrix	sub;
	int			i;
	int			j;

	j = -1;
	while (++j < N)
	{
		i = -1;
		while (++i < N)
		{
			get_submatrix(mat, i, j, &sub);
			cof->matrix[i][j] = pow(-1, i + j) * det3(&sub);
		}
	}
}

t_matrix	matrix_inverse(const t_matrix *m)
{
	t_matrix	inverse;
	t_matrix	cof;
	float		det;
	int			i;
	int			j;

	fill_zero_matrix(&inverse);
	fill_zero_matrix(&cof);
	if (!m)
		return (write(2, "Error inversing matrix\n", 23), inverse);
	i = -1;
	cofactor(m, &cof);
	det = detr(&cof, m);
	while (++i < N && det != 0)
	{
		j = -1;
		while (++j < N)
			inverse.matrix[i][j] = cof.matrix[i][j] / det;
	}
	if (det == 0)
		printf("zero determenat \n");
	return (inverse);
}
