/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymohamed <ymohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 09:44:20 by ymohamed          #+#    #+#             */
/*   Updated: 2023/01/30 19:38:10 by ymohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYTRACE_H
# define RAYTRACE_H
# include "./resources/mlx/mlx.h"
# include "./resources/ft_libft_printf/ft_libft_printf.h"
# include <math.h>
# include <unistd.h>
#include <stdio.h>

# ifndef EPSILON
#  define EPSILON	0.01
# endif

typedef struct s_point_vector_in_3d
{
	float	x;
	float	y;
	float	z;
	int		w;
}	t_point_vector;

// Operations to get vectors (ops_on_vectors.c)
int				fill_vector(t_point_vector *v, float x, float y, float z);
t_point_vector	add_vectors(const t_point_vector *v1, const t_point_vector *v2);
t_point_vector	subract_vectors(const t_point_vector *v1,
					const t_point_vector *v2);
t_point_vector	vector_opposite(const t_point_vector *v);
t_point_vector	get_vec_a_to_b(const t_point_vector *a,
					const t_point_vector *b);

// Operations on points (ops_on_point.c)
int				fill_point(t_point_vector *p, float x, float y, float z);
int				elemnts_are_identical(const t_point_vector *a,
					const t_point_vector *b, float epsilon);
t_point_vector	point_from_point_vector(const t_point_vector *a,
					const t_point_vector *v);
void			print_an_elemnt(t_point_vector *e);

// Dot and Cross Multiplication of vectors (mag_norm_dot_cros.c)
float			vec_mag(const t_point_vector *v);
t_point_vector	vec_norm(const t_point_vector *v);
float			dot_multiplication(const t_point_vector *v1,
					const t_point_vector *v2);
t_point_vector	cros_multiplication(const t_point_vector *v1,
					const t_point_vector *v2);

#endif