/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymohamed <ymohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 16:47:12 by ymohamed          #+#    #+#             */
/*   Updated: 2023/06/11 21:06:56 by ymohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytrace.h"

void	set_objects(t_ranger *alive)
{
	alive->p[0] = fill_plane((t_point_vector){0.0, -2.2, 100.0, 1}, (t_point_vector){0.0, 1.0, 0.0, 0},  (t_color){131, 131, 126});
	alive->s[0] = fill_sphere((t_point_vector){4.0, 3.0, -20.0, 1}, 3.0, (t_color){0, 200, 200});
	alive->s[1] = fill_sphere((t_point_vector){0.0, 0.01, -10.0, 1}, 2.0, (t_color){126, 112, 152});
	alive->s[2] = fill_sphere((t_point_vector){-2.0, 0.0, -8.0, 1}, 2.0, (t_color){240, 151, 41});
	alive->objcs[0].obj_id = 0;
	alive->objcs[0].obj_type = plane;
	alive->objcs[0].the_obj = &alive->p[0];
	alive->objcs[1].obj_id = 1;
	alive->objcs[1].obj_type = sphere;
	alive->objcs[1].the_obj = &alive->s[0];
	alive->objcs[2].obj_id = 2;
	alive->objcs[2].obj_type = sphere;
	alive->objcs[2].the_obj = &alive->s[1];
	alive->objcs[3].obj_id = 3;
	alive->objcs[3].obj_type = sphere;
	alive->objcs[3].the_obj = &alive->s[2];
	alive->no_of_object = 4;
}
