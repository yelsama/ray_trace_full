/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymohamed <ymohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 09:44:20 by ymohamed          #+#    #+#             */
/*   Updated: 2023/02/01 21:55:07 by ymohamed         ###   ########.fr       */
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
# define XBLOCK_DIM 900
# define YBLOCK_DIM 550
# define BATCH_WIDTH 2
# define BATCH_HEIGHT 2

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

#endif