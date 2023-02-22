/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transforms.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymohamed <ymohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 18:47:36 by ymohamed          #+#    #+#             */
/*   Updated: 2023/02/23 02:47:23 by ymohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytrace.h"

t_matrix	get_translation_matrix(float x, float y, float z)
{
	t_matrix	trans;

	fill_identity_matrix(&trans);
	trans.matrix[0][3] = x;
	trans.matrix[1][3] = y;
	trans.matrix[2][3] = z;
	return (trans);
}

t_matrix	get_scaling_matrix(float x, float y, float z)
{
	t_matrix	trans;

	fill_identity_matrix(&trans);
	trans.matrix[0][0] = x;
	trans.matrix[1][1] = y;
	trans.matrix[2][2] = z;
	return (trans);
}

t_point_vector	matrix_by_tuple(const t_matrix *mat, const t_point_vector *tpl)
{
	t_point_vector	result_tuple;

	result_tuple = (t_point_vector){0.0, 0.0, 0.0, 0.0};
	if (!mat || !tpl)
		return (write(2, "Error finiding needed elements\n", 31), result_tuple);
	result_tuple.x = (mat->matrix[0][0] * tpl->x)
		+ (mat->matrix[0][1] * tpl->y) + (mat->matrix[0][2] * tpl->x);
	result_tuple.y = (mat->matrix[1][0] * tpl->x)
		+ (mat->matrix[1][1] * tpl->y) + (mat->matrix[1][2] * tpl->x);
	result_tuple.z = (mat->matrix[2][0] * tpl->x)
		+ (mat->matrix[2][1] * tpl->y) + (mat->matrix[2][2] * tpl->x);
	result_tuple.w = tpl->w * mat->matrix[3][3];
	return (result_tuple);
}

void	reform_tupl_by_matrix(const t_matrix *mat, t_point_vector *tpl)
{
	float	*result_tuple;

	result_tuple = malloc(sizeof(float) * 4);
	if (!mat || !tpl || !result_tuple)
	{
		write(2, "Error finiding needed elements\n", 31);
		return ;
	}
	result_tuple[0] = (mat->matrix[0][0] * tpl->x)
		+ (mat->matrix[0][1] * tpl->y) + (mat->matrix[0][2] * tpl->x);
	result_tuple[1] = (mat->matrix[1][0] * tpl->x)
		+ (mat->matrix[1][1] * tpl->y) + (mat->matrix[1][2] * tpl->x);
	result_tuple[2] = (mat->matrix[2][0] * tpl->x)
		+ (mat->matrix[2][1] * tpl->y) + (mat->matrix[2][2] * tpl->x);
	result_tuple[3] = tpl->w * mat->matrix[3][3];
	tpl->x = result_tuple[0];
	tpl->y = result_tuple[1];
	tpl->z = result_tuple[2];
	tpl->w = result_tuple[3];
	free(result_tuple);
	result_tuple = NULL;
}
