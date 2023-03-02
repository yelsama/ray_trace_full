/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple_rotation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymohamed <ymohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 21:18:46 by ymohamed          #+#    #+#             */
/*   Updated: 2023/02/24 22:40:12 by ymohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytrace.h"

static void	rotate_around_x(t_point_vector *tpl, float cos_d, float sin_d)
{
	float	tmp[2];

	tmp[0] = tpl->y;
	tmp[1] = tpl->z;
	tpl->y = cos_d * tmp[0] + tmp[1] * -1 * sin_d;
	tpl->z = sin_d * tmp[0] + tmp[1] * cos_d;
}

static void	rotate_around_y(t_point_vector *tpl, float cos_d, float sin_d)
{
	float	tmp[2];

	tmp[0] = tpl->x;
	tmp[1] = tpl->z;
	tpl->x = cos_d * tmp[0] + tmp[1] * sin_d;
	tpl->z = -1 * sin_d * tmp[0] + tmp[1] * cos_d;
}

static void	rotate_around_z(t_point_vector *tpl, float cos_d, float sin_d)
{
	float	tmp[2];

	tmp[0] = tpl->x;
	tmp[1] = tpl->y;
	tpl->x = cos_d * tmp[0] + tmp[1] * -1 * sin_d;
	tpl->y = sin_d * tmp[0] + tmp[1] * cos_d;
}

void	rotate_tuple(t_point_vector *tpl, int axis, int degree)
{
	double	rad;
	float	cos_d;
	float	sin_d;
	int		final_degree;

	final_degree = degree % 360;
	rad = final_degree * DEGTORAD;
	cos_d = (float)cos(rad);
	sin_d = (float)sin(rad);
	if (axis == x_axis)
		rotate_around_x(tpl, cos_d, sin_d);
	if (axis == y_axis)
		rotate_around_y(tpl, cos_d, sin_d);
	if (axis == z_axis)
		rotate_around_z(tpl, cos_d, sin_d);
}

void	shearing_trans(t_point_vector *tpl, float xy_xz_yx_yz_zx_zy[6])
{
	float	tmp[3];

	if (!tpl || !xy_xz_yx_yz_zx_zy)
	{
		write(2, "Errro perform shearing transformation\n", 38);
		return ;
	}
	tmp[0] = tpl->x;
	tmp[1] = tpl->y;
	tmp[2] = tpl->z;
	tpl->x = tmp[0] + tmp[1] * xy_xz_yx_yz_zx_zy[0]
		+ tmp[2] * xy_xz_yx_yz_zx_zy[1];
	tpl->y = tmp[0] * xy_xz_yx_yz_zx_zy[2] + tmp[1]
		+ tmp[2] * xy_xz_yx_yz_zx_zy[3];
	tpl->z = tmp[0] * xy_xz_yx_yz_zx_zy[4]
		+ tmp[1] * xy_xz_yx_yz_zx_zy[5] + tmp[2];
}
