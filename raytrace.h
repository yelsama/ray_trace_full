/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymohamed <ymohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 09:44:20 by ymohamed          #+#    #+#             */
/*   Updated: 2023/08/20 23:23:01 by ymohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYTRACE_H
# define RAYTRACE_H
# include "./resources/mlx/mlx.h"
# include "./resources/ft_libft_printf/ft_libft_printf.h"
# include <math.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <stdint.h>
# include <stdarg.h>
# include <fcntl.h>

# ifndef EPSILON
#  define EPSILON 0.01
# endif
# define DEGTORAD 0.01745327
# define XBLOCK_DIM 1920 
# define YBLOCK_DIM 1080
# define BATCH_WIDTH 2
# define BATCH_HEIGHT 2

typedef enum e_axis
{
	x_axis,
	y_axis,
	z_axis,
	sphere,
	plane,
	cylinder
}	t_axis;

typedef struct s_objects_lis
{
	int					obj_id;
	int					obj_type;
	void				*the_obj;
}	t_objcs_list;

typedef struct s_main_frame
{
	void	*frame_ptr;
	void	*window;
}	t_main_frame;

typedef struct s_colors
{
	float	red;
	float	green;
	float	blue;
}	t_color;

typedef struct s_point_vector_in_3d
{
	float	x;
	float	y;
	float	z;
	int		w;
}	t_tuple;

typedef struct s_canva
{
	int	width;
	int	height;
	int	color;
}	t_batch;

typedef struct s_hit_info
{
	float	hit_or_not;
	float	t;
	int		obj_id;
}	t_hit_info;

typedef struct s_matrix
{
	float	matrix[4][4];
}	t_matrix;

typedef struct s_camera
{
	t_tuple		location;
	t_tuple		look_forward;
	t_matrix	transform;
	float		field_of_view;
	float		half_width;
	float		half_height;
	float		aspect_ratio;
	float		pixel_size;
}	t_camera;

typedef struct s_render_system
{
	float	half_width;
	float	half_heigh;
	float	pixel_size;
	float	half_szie;
	float	aspect_ratio;
	t_tuple	look_up;
	t_tuple	look_right;
}	t_render;

typedef struct s_ray
{
	t_tuple	*origin;
	t_tuple	direction;
}	t_ray;
typedef struct s_light
{
	t_tuple	position;
	float	brightness;
	t_color	color;
}	t_light;

typedef struct s_sphere
{
	t_tuple	cent;
	float	rad;
	t_color	color;
}	t_sphere;

typedef struct s_cylinder
{
	t_tuple	cnt;
	t_tuple	vec;
	t_tuple	a;
	t_tuple	b;
	t_tuple	ba_v;
	float	rad;
	float	height;
	float	baba;
	t_color	color;
}	t_cylndr;

typedef struct s_plane
{
	t_tuple	c_point;
	t_tuple	normal_v;
	t_color	color;
}	t_plane;

typedef struct s_ranger
{
	t_main_frame	frame;
	t_camera		cam;
	t_render		rend;
	t_light			main_light;
	t_light			ambient;
	t_color			light_appear_clr;
	t_color			amb_appear_clr;
	t_objcs_list	*objcs;
	t_sphere		*s;
	t_plane			*p;
	t_cylndr		*c;
	int				no_of_object;
	int				error;
	int				am;
	int				ca;
	int				li;
	int				pl;
	int				sp;
	int				cy;
	int				cam_in_obj;
	int				obj_index;
}	t_ranger;

// Operations to get vectors (ops_on_vectors.c)
int			fill_vector(t_tuple *v, float x, float y, float z);
t_tuple		add_vectors(const t_tuple *v1, const t_tuple *v2);
t_tuple		subtract_vectors(const t_tuple *v1, const t_tuple *v2);
t_tuple		vector_opposite(const t_tuple *v);
t_tuple		get_vec_a_to_b(const t_tuple *a, const t_tuple *b);

// Operations on points (ops_on_point.c)
int			fill_point(t_tuple *p, float x, float y, float z);
int			elemnts_are_identical(const t_tuple *a,
				const t_tuple *b, float epsilon);
t_tuple		point_from_point_vector(const t_tuple *a, const t_tuple *v);
void		print_an_elemnt(t_tuple *e);
void		p0_plus_t_mul_v(t_tuple *p, const t_tuple *p0,
				const t_tuple *v, float t);

// Dot and Cross Multiplication of vectors (mag_norm_dot_cros.c)
float		vec_mag(const t_tuple *v);
t_tuple		vec_norm(const t_tuple *v);
float		dot_multiplication(const t_tuple *v1, const t_tuple *v2);
t_tuple		cros_multiplication(const t_tuple *v1, const t_tuple *v2);
t_tuple		rescale_vecotr(const t_tuple *v, float scl);

// Handle Colors (colors.c)
int			fill_color(t_color *c, float red, float green, float blue);
t_color		add_colors(const t_color *c1, const t_color *c2);
t_color		subt_colors(const t_color *c1, const t_color *c2);
t_color		color_multi_scalar(const t_color *c, float sclr);
t_color		blend_two_colors(const t_color *c1, const t_color *c2);

// Convert the RGB values into one int value and making batch (batch.c)
int			rgb_to_int(const t_color *c);
int			fill_batch(t_batch *can, const t_color *c, int width, int height);
int			paint_batch_at_mlx(const t_batch *can, t_ranger *alive);

// Matrices operations (matrix_4_4.c)
int			fill_zero_matrix(t_matrix *m);
int			fill_identity_matrix(t_matrix *m);
t_matrix	matrices_multiplication(const t_matrix *m1, const t_matrix *m2);
// t_tuple	matrix_by_tuple(const t_matrix *m, const t_tuple *tuple);

// Perform Matrix Inverse (matrix_inverse.c)
t_matrix	matrix_inverse(const t_matrix *m);

// Get transforming matrices to move or rotate (transforms.c)
t_matrix	get_translation_matrix(float x, float y, float z);
t_matrix	get_scaling_matrix(float x, float y, float z);
t_tuple		matrix_by_tuple(const t_matrix *mat, const t_tuple *tpl);
void		reform_tupl_by_matrix(const t_matrix *mat, t_tuple *tpl);

// Get rotation arround x y z axis (tuple_rotation.c)
void		rotate_tuple(t_tuple *tpl, int axis, int degree);
void		shearing_trans(t_tuple *tpl, float xy_xz_yx_yz_zx_zy[6]);

// Create and handle rays (ops_on_ray.c)
t_ray		fill_ray(t_tuple *orgn_p, t_tuple v);
t_tuple		intrsction_point(const t_ray *r, float t);

// Find if the ray intersect with specific shape or not (inspect_intersect.c)
t_hit_info	ray_sphare_intrsection(const t_ray *r, const t_sphere *s);
t_hit_info	ray_plane_intersection(const t_ray *r, const t_plane *p);

// Fill Basic shapes (form_shapes.c)
t_sphere	fill_sphere(t_tuple cntr, float rad, t_color clr);
t_plane		fill_plane(t_tuple cntr, t_tuple normal_v,
				t_color clr);
t_cylndr	fill_cylndr(t_tuple cntr, t_tuple vec,
				t_color clr, float *h_r);

// Find normal and light vectors for light and shade (light_shade.c)
t_tuple		normal_vec_on_sphere(const t_sphere *s, t_tuple p);
int			ligth_effect_on_sphere_pxl_color(t_ranger *alive,
				t_tuple hit_p, int obj_id);
int			light_effect_on_plane_pxl_color(t_ranger *alive,
				t_tuple hit_p, int obj_id);
int			light_effect_on_cylndr_pxl_color(t_ranger *alive,
				t_tuple hit_p, int obj_id);

// Prepare rendering values from camera and canvas info and get
// rays when rendering image (for_render.c)
void		set_camera(t_ranger *alive);
t_ray		ray_for_pixel(t_ranger *alive, int x, int y);
void		get_camera_transform_matrix(t_ranger *alive);
t_hit_info	get_hit_object(t_ranger *alive, const t_ray *r);
// t_matrix	get_orientation_matrix(t_ranger *alive);

// Special function to operate cylinder (cylinder.c)
t_hit_info	ray_cylinder_intersect(const t_ray *r, const t_cylndr *c);

// Find if camera is inside an object or not (cam_inside.c)
int			verify_camera_inside(t_ranger *alive);

// preparse check the the path and the file extention (preparse.c)
void		exam_the_map_file(char *file, char *extention);

// Check if all given vectors are normalized or not (check_vectors.c)
void		check_vectors(t_ranger *alive);

//Parsing
int			parsing(t_ranger *alive, char **av);
int			read_width(char *strt);
void		fill(char ***argsex, t_ranger *alive, int l);
void		fill_ambient(t_ranger *alive, char **str);
void		fill_camera(t_ranger *alive, char **str);
void		fill_light(t_ranger *alive, char **str);
void		fill_plane2(t_ranger *alive, char **str);
void		fill_sphere2(t_ranger *alive, char **str);
void		fill_cylinder2(t_ranger *alive, char **str);

//get_next_line
char		*ft_strchr(const char *s, int c);
char		*gl_substr(char *s, int start, int len);
char		*gl_strjoin(char *s1, char *s2);
int			gl_strlen2(char *str);
int			gl_strlen(char *str);
char		*gl_strchr(const char *s, int c);
// int		ft_strlen(char *str);
// char	*ft_strjoin(char *s1, char *s2);
// char	*ft_substr(char *s, int start, int len);
char		*get_next_line(int fd);
void		free_3d_char(char ***array);
int			check_values(char ***argsex, int l);
void		free_2d_array_char(char **str);
int			check_float(char *array);
int			check_coordinates_float(char *array);
int			check_ambient_error(char **array);
int			check_light_error(char **array);
void		norm_a_vector(t_tuple *vec);
void		free_3d_char(char ***array);
void		wrong_inputs(char ***argsex);
void		fill_cylinder22(t_ranger *alive);
void		free_objects(t_ranger *alive);
char		*change_spaces(char *str);
void		initiate_params2(t_ranger *alive);

#endif