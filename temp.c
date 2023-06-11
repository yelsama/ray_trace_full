/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymohamed <ymohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 16:47:12 by ymohamed          #+#    #+#             */
/*   Updated: 2023/06/11 19:11:58 by ymohamed         ###   ########.fr       */
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

t_hit_info	get_hit_object(t_ranger *alive, const t_ray *r)
{
	t_sphere		*s;
	t_plane			*p;
	t_hit_info		inf;
	t_hit_info		tmp_inf;
	int				i;
	int				past_first;

	inf.hit_or_not = 0;
	inf.t = 0.0;
	inf.obj_id = -1;
	past_first = 0;
	i = -1;
	while (++i < alive->no_of_object)
	{
		if (alive->objcs[i].obj_type == sphere)
		{
			s = (t_sphere *)alive->objcs[i].the_obj;
			tmp_inf = ray_sphare_intrsection(r, s);
		}
		else if (alive->objcs[i].obj_type == plane)
		{
			p = (t_plane *)alive->objcs[i].the_obj;
			tmp_inf = ray_plane_intersection(r, p);
		}
		else
			printf("got uknown object\n");
		if (!past_first && tmp_inf.hit_or_not > 0)
		{
			inf.hit_or_not = 1;
			inf.t = tmp_inf.t;
			inf.obj_id = i;
			past_first++;
		}
		if (tmp_inf.hit_or_not > 0 && tmp_inf.t < inf.t)
		{
			inf.hit_or_not = 1;
			inf.t = tmp_inf.t;
			inf.obj_id = i;
		}
	}
	return (inf);
}
