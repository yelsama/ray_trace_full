/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymohamed <ymohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 14:58:59 by ymohamed          #+#    #+#             */
/*   Updated: 2023/01/31 08:12:50 by ymohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytrace.h"

int	main(void)
{
	t_point_vector	p_current;
	t_point_vector	v_vlocity;
	t_point_vector 	v_final_act;
	t_point_vector	v_env_wind;
	t_point_vector	v_env_gravity;
	t_point_vector	v_wind_gravity_act;

	if (!fill_point(&p_current, 0, 1, 0))
		return (0);
	if (!fill_vector(&v_vlocity, 1, 1, 0)
		|| !fill_vector(&v_env_wind, -0.01, 0, 0)
		|| !fill_vector(&v_env_gravity, 0, -0.1, 0))
		return (0);
	v_wind_gravity_act = add_vectors(&v_env_gravity, &v_env_wind);
	print_an_elemnt(&v_wind_gravity_act);
	v_final_act = add_vectors(&v_wind_gravity_act, &v_vlocity);
	int i = 1;
	while (p_current.y > 0)
	{
		printf("this is tick %d\n", i);
		p_current = point_from_point_vector(&p_current, &v_final_act);
		v_final_act = add_vectors(&v_final_act, &v_wind_gravity_act);
		print_an_elemnt(&p_current);
		i++;
		printf("####################################\n");
	}
	printf("got here\n");
	return (0);
}
