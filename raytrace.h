/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymohamed <ymohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 09:44:20 by ymohamed          #+#    #+#             */
/*   Updated: 2023/02/21 15:12:39 by ymohamed         ###   ########.fr       */
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
#  define EPSILON 0.01
# endif
# define DEGTORAD 0.01745327
# define XBLOCK_DIM 1200
# define YBLOCK_DIM 800
# define BATCH_WIDTH 2
# define BATCH_HEIGHT 2

typedef enum e_axis
{
	x_axis,
	y_axis,
	z_axis
}	t_axis;

typedef struct s_main_frame
{
	void	*frame_ptr;
	void	*window;
}	t_main_frame;

typedef struct s_colors
{
	int	red;
	int	green;
	int	blue;
}	t_color;

typedef struct s_point_vector_in_3d
{
	float	x;
	float	y;
	float	z;
	int		w;
}	t_point_vector;

typedef struct s_canva
{
	int	width;
	int	height;
	int	color;
}	t_batch;

typedef struct s_ranger
{
	t_main_frame	frame;
}	t_ranger;

typedef struct s_matrix
{
	float	matrix[4][4];
}	t_matrix;

typedef struct s_ray
{
	t_point_vector	*origin;
	t_point_vector	direction;
}	t_ray;

typedef struct s_sphere
{
	int				objct_id;
	float			rad;
	t_point_vector	cent;
}	t_sphere;

// Operations to get vectors (ops_on_vectors.c)
int				fill_vector(t_point_vector *v, float x, float y, float z);
t_point_vector	add_vectors(const t_point_vector *v1, const t_point_vector *v2);
t_point_vector	subtract_vectors(const t_point_vector *v1,
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
t_point_vector	rescale_vecotr(const t_point_vector *v, float scl);

// Handle Colors (colors.c)
int				fill_color(t_color *c, int red, int green, int blue);
t_color			add_colors(const t_color *c1, const t_color *c2);
t_color			subt_colors(const t_color *c1, const t_color *c2);
t_color			color_multi_scalar(const t_color *c, int sclr);
t_color			blend_two_colors(const t_color *c1, const t_color *c2);

// Convert the RGB values into one int value and making batch (batch.c)
int				rgb_to_int(const t_color *c);
int				fill_batch(t_batch *can, const t_color *c, int width,
					int height);
int				paint_batch_at_mlx(const t_batch *can, t_ranger *alive);

// Matrices operations (matrix_4_4.c)
int				fill_zero_matrix(t_matrix *m);
int				fill_identity_matrix(t_matrix *m);
t_matrix		matrices_multiplication(const t_matrix *m1, const t_matrix *m2);
// t_point_vector	matrix_by_tuple(const t_matrix *m, const t_point_vector *tuple);

// Perform Matrix Inverse (matrix_inverse.c)
t_matrix		matrix_inverse(const t_matrix *m);

// Get transforming matrices to move or rotate (transforms.c)
t_matrix		get_translation_matrix(float x, float y, float z);
t_matrix		get_scaling_matrix(float x, float y, float z);
t_point_vector	matrix_by_tuple(const t_matrix *mat, const t_point_vector *tpl);
void			reform_tupl_by_matrix(const t_matrix *mat, t_point_vector *tpl);

// Get rotation arround x y z axis (tuple_rotation.c)
void			rotate_tuple(t_point_vector *tpl, int axis, int degree);
void			shearing_trans(t_point_vector *tpl, float xy_xz_yx_yz_zx_zy[6]);

// Create and handle rays (ops_on_ray.c)
t_ray			fill_ray(t_point_vector *orgn_p, t_point_vector v);
t_point_vector	intrsction_point(const t_ray *r, float t);
				//point = origin + vector * time
void			ray_sphare_intrsection(const t_ray *r, const t_sphere *s,
					float *inf);

// Fill Basic shapes (form_shapes.c)
t_sphere		fill_sphare(t_point_vector cntr, float rad, int objct_id);

#endif