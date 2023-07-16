/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymohamed <ymohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 16:43:12 by mohouhou          #+#    #+#             */
/*   Updated: 2023/07/16 14:16:27 by ymohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytrace.h"

int	read_width(char *strt)
{
	int		fd;
	char	*str;
	int		i;

	i = 0;
	str = NULL;
	fd = open(strt, O_RDONLY);
	while (1)
	{
		str = get_next_line(fd);
		if (str == NULL)
			break ;
		free(str);
		i++;
	}
	close(fd);
	return (i);
}

void	free_2d_array_char(char **str)
{
	int i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	fill_ambient(t_ranger *alive, char **str)
{
	char **tmp;
	printf("%s\n",str[1]);
	alive->ambient.brightness = ft_atof(str[1]);
	printf("test\n");
	tmp = ft_split(str[2],',');
	alive->ambient.color.red = ft_atof(tmp[0]);
	alive->ambient.color.green = ft_atof(tmp[1]);
	alive->ambient.color.blue = ft_atof(tmp[2]);
	free_2d_array_char(str);
	
}

void	fill_camera(t_ranger *alive, char **str)
{
	char **tmp;
	
	alive->cam.field_of_view = ft_atof(str[3]);
	tmp = ft_split(str[1],',');
	alive->cam.location.w = 1;
	alive->cam.location.x = ft_atof(tmp[0]);
	alive->cam.location.y = ft_atof(tmp[1]);
	alive->cam.location.z = ft_atof(tmp[2]);
	ft_printf("%.6f \n %.6f\n %.6f\n",ft_atof(tmp[0]),ft_atof(tmp[1]),ft_atof(tmp[2]) );
	free_2d_array_char(tmp);
	tmp = ft_split(str[2],',');
	alive->cam.look_forward.w = 0;
	alive->cam.look_forward.x = ft_atof(tmp[0]);
	alive->cam.look_forward.y = ft_atof(tmp[1]);
	alive->cam.look_forward.z = ft_atof(tmp[2]);
	free_2d_array_char(tmp);
}

void	fill_light(t_ranger *alive, char **str)
{
	char **tmp;
	
	alive->main_light.brightness = ft_atof(str[2]);
	tmp = ft_split(str[1],',');
	alive->main_light.position.w = 1;
	alive->main_light.position.x = ft_atof(tmp[0]);
	alive->main_light.position.y = ft_atof(tmp[1]);
	alive->main_light.position.z = ft_atof(tmp[2]);
	free_2d_array_char(tmp);
	tmp = ft_split(str[3],',');
	alive->main_light.color.red = ft_atof(tmp[0]);
	alive->main_light.color.green = ft_atof(tmp[1]);
	alive->main_light.color.blue = ft_atof(tmp[2]);
	free_2d_array_char(tmp);
}

void	fill_plane2(t_ranger *alive, char **str)
{
	char **tmp;

	tmp = ft_split(str[1],',');
	alive->p[alive->pl].c_point.w = 1;
	alive->p[alive->pl].c_point.x = ft_atof(tmp[0]);
	alive->p[alive->pl].c_point.y = ft_atof(tmp[1]);
	alive->p[alive->pl].c_point.z = ft_atof(tmp[2]);
	free_2d_array_char(tmp);
	tmp = ft_split(str[2],',');
	alive->p[alive->pl].normal_v.w = 0;
	alive->p[alive->pl].normal_v.x = ft_atof(tmp[0]);
	alive->p[alive->pl].normal_v.y = ft_atof(tmp[1]);
	alive->p[alive->pl].normal_v.z = ft_atof(tmp[2]);
	free_2d_array_char(tmp);
	tmp = ft_split(str[3],',');
	alive->p[alive->pl].color.red = ft_atof(tmp[0]);
	alive->p[alive->pl].color.green = ft_atof(tmp[1]);
	alive->p[alive->pl].color.blue = ft_atof(tmp[2]);
	free_2d_array_char(tmp);
	alive->objcs[alive->obj_index].obj_id = alive->obj_index;
	alive->objcs[alive->obj_index].obj_type = plane;
	alive->objcs[alive->obj_index].the_obj = &alive->p[alive->pl];
	alive->pl++;
	alive->obj_index++;
}
void	fill_sphere2(t_ranger *alive, char **str)
{
	char **tmp;

	tmp = ft_split(str[1],',');
	alive->s[alive->sp].cent.w = 1;
	alive->s[alive->sp].cent.x = ft_atof(tmp[0]);
	alive->s[alive->sp].cent.y = ft_atof(tmp[1]);
	alive->s[alive->sp].cent.z = ft_atof(tmp[2]);
	free_2d_array_char(tmp);
	tmp = ft_split(str[3],',');
	alive->s[alive->sp].color.red = ft_atof(tmp[0]);
	alive->s[alive->sp].color.green = ft_atof(tmp[1]);
	alive->s[alive->sp].color.blue = ft_atof(tmp[2]);
	alive->s[alive->sp].rad = ft_atof(str[2]) / 2;
	free_2d_array_char(tmp);
	alive->objcs[alive->obj_index].obj_id = alive->obj_index;
	alive->objcs[alive->obj_index].obj_type = sphere;
	alive->objcs[alive->obj_index].the_obj = &alive->s[alive->sp];
	alive->sp++;
	alive->obj_index++;
}

void	fill_cylinder2(t_ranger *alive, char **str)
{
	char **tmp;
	t_point_vector	tmp2;

	tmp = ft_split(str[1],',');
	alive->c[alive->cy].cnt.w = 1;
	alive->c[alive->cy].cnt.x = ft_atof(tmp[0]);
	alive->c[alive->cy].cnt.y = ft_atof(tmp[1]);
	alive->c[alive->cy].cnt.z = ft_atof(tmp[2]);
	free_2d_array_char(tmp);
	tmp = ft_split(str[2],',');
	alive->c[alive->cy].vec.w = 0;
	alive->c[alive->cy].vec.x = ft_atof(tmp[0]);
	alive->c[alive->cy].vec.y = ft_atof(tmp[1]);
	alive->c[alive->cy].vec.z = ft_atof(tmp[2]);
	free_2d_array_char(tmp);
	alive->c[alive->cy].rad = (ft_atof(str[3])/2.0);
	alive->c[alive->cy].height = ft_atof(str[4]);
	tmp = ft_split(str[5],',');
	alive->c[alive->cy].color.red = ft_atoi(tmp[0]);
	alive->c[alive->cy].color.green = ft_atoi(tmp[1]);
	alive->c[alive->cy].color.blue = ft_atoi(tmp[2]);
	free_2d_array_char(tmp);
	tmp2 = rescale_vecotr(&alive->c->vec, alive->c->height / 2);
	alive->c[alive->cy].a = point_from_point_vector(&alive->c[alive->cy].cnt, &tmp2);
	tmp2 = rescale_vecotr(&tmp2, -1.0);
	alive->c[alive->cy].b = point_from_point_vector(&alive->c[alive->cy].cnt, &tmp2);
	alive->c[alive->cy].ba_v = get_vec_a_to_b(&alive->c[alive->cy].a, &alive->c[alive->cy].b);
	alive->c[alive->cy].baba = dot_multiplication(&alive->c[alive->cy].ba_v, &alive->c[alive->cy].ba_v);
	alive->objcs[alive->obj_index].obj_id = alive->obj_index;
	alive->objcs[alive->obj_index].obj_type = cylinder;
	alive->objcs[alive->obj_index].the_obj = &alive->c[alive->cy];
	alive->cy++;
	alive->obj_index++;
}

void	initiate_params(t_ranger *alive)
{
	alive->A = 0;
	alive->C = 0;
	alive->L = 0;
	alive->pl = 0;
	alive->sp = 0;
	alive->cy = 0;
}

void check_numbers(char ***argsex, t_ranger *alive, int l)
{
	int	i;

	i = 0;
	initiate_params(alive);
	while (i < l)
	{
		if ( ft_strncmp(argsex[i][0],"A",1) == 0)
			alive->A++;
		else if ( ft_strncmp(argsex[i][0],"C",1) == 0)
			alive->C++;
		else if ( ft_strncmp(argsex[i][0],"L",1) == 0)
			alive->L++;
		else if ( ft_strncmp(argsex[i][0],"pl",2) == 0)
			alive->pl++;
		else if ( ft_strncmp(argsex[i][0],"sp",2) == 0)
			alive->sp++;
		else if ( ft_strncmp(argsex[i][0],"cy",2) == 0)
			alive->cy++;
		i++;
	}
}

void check_for_errors(t_ranger *alive)
{
	if (alive->A > 1 || alive->A == 0 || alive->C > 1 || alive->C == 0 || alive->L > 1 || alive->L == 0)
	{
		ft_printf("check inputs\n");
		exit(0);
	}
	if (alive->sp > 0)
		alive->s = malloc(sizeof(t_sphere) * (alive->sp));
	if (alive->pl > 0)
		alive->p = malloc(sizeof(t_plane) * alive->pl);
	if (alive->cy > 0)
		alive->c = malloc(sizeof(t_cylndr) * (alive->cy));
	alive->no_of_object = alive->pl + alive->sp + alive->cy;
	if (alive->no_of_object > 0)
		alive->objcs = malloc(sizeof(t_objcs_list) * alive->no_of_object);
}

void	fill(char ***argsex, t_ranger *alive, int l)
{
	int	i;

	i = 0;
	check_numbers(argsex, alive, l);
	ft_printf("test\n");
	check_for_errors(alive);
	initiate_params(alive);
	alive->obj_index = 0;
	while (i < l)
	{
		printf("%d\n",i);
		if ( ft_strncmp(argsex[i][0],"A",1) == 0)
			fill_ambient(alive,argsex[i]);
		else if ( ft_strncmp(argsex[i][0],"C",1) == 0)
			fill_camera(alive, argsex[i]);
		else if ( ft_strncmp(argsex[i][0],"L",1) == 0)
			fill_light(alive, argsex[i]);
		else if ( ft_strncmp(argsex[i][0],"pl",2) == 0)
			fill_plane2(alive, argsex[i]);
		else if ( ft_strncmp(argsex[i][0],"sp",2) == 0)
			fill_sphere2(alive, argsex[i]);
		else if ( ft_strncmp(argsex[i][0],"cy",2) == 0)
			fill_cylinder2(alive, argsex[i]);
		i++; 
	}
}

int	parsing(t_ranger *alive, char **av)
{
	int	l;
	char	**args;
	int	i;
	int	fd;
	char	***argsex;

	i = 0;
	l = read_width(av[1]);
	args = (char**)malloc(sizeof(char*)*(l + 1));
	fd = open(av[1], O_RDONLY);
	while (i < l)
	{
		args[i] = get_next_line(fd);
		i++;
	}
	args[i] = 0;
	close(fd);
	argsex = (char***)malloc(sizeof(char**) * (i + 1));
	i = 0;
	while(args[i])
	{
		argsex[i] = ft_split(args[i],' ');
		i++;
	}
	fill(argsex, alive, l);


	return (0);
}