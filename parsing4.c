/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohouhou <mohouhou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 18:18:08 by mohouhou          #+#    #+#             */
/*   Updated: 2023/08/19 18:53:23 by mohouhou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytrace.h"

void	wrong_inputs(char ***argsex)
{
	ft_printf("Wrong Inputs \n");
	free_3d_char(argsex);
	exit(0);
}

void	fill_cylinder22(t_ranger *alive)
{
	t_tuple			tmp2;

	tmp2 = rescale_vecotr(&alive->c[alive->cy].vec,
			alive->c[alive->cy].height / 2.0);
	alive->c[alive->cy].a = point_from_point_vector(&alive->c[alive->cy].cnt,
			&tmp2);
	tmp2 = rescale_vecotr(&tmp2, -1.0);
	alive->c[alive->cy].b = point_from_point_vector(&alive->c[alive->cy].cnt,
			&tmp2);
	alive->c[alive->cy].ba_v = get_vec_a_to_b(&alive->c[alive->cy].a,
			&alive->c[alive->cy].b);
	alive->c[alive->cy].baba = dot_multiplication(&alive->c[alive->cy].ba_v,
			&alive->c[alive->cy].ba_v);
	alive->objcs[alive->obj_index].obj_id = alive->obj_index;
	alive->objcs[alive->obj_index].obj_type = cylinder;
	alive->objcs[alive->obj_index].the_obj = &alive->c[alive->cy];
	alive->cy++;
	alive->obj_index++;
}

void	free_objects(t_ranger *alive)
{
	free(alive->s);
	free(alive->p);
	free(alive->c);
	free(alive->objcs);
}
