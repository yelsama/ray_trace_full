/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymohamed <ymohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 22:19:03 by ymohamed          #+#    #+#             */
/*   Updated: 2023/08/20 22:36:33 by ymohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytrace.h"

void	exam_the_map_file(char *file, char *extention)
{
	char	*name_ext;

	if (!file || file[0] == 0)
	{
		ft_printf("Error\nIvalid Dirctory");
		exit (0);
	}
	name_ext = ft_strrchr(file, '.');
	if (!name_ext)
	{
		ft_printf("Error\nIvalid Dirctory");
		exit (0);
	}
	if (ft_strlen(name_ext) != 3 || ft_strlen(file) < 4)
	{
		ft_printf("Error\nIvalid extention\n");
		exit (0);
	}
	if (ft_strncmp(extention, name_ext, 3))
	{
		ft_printf("Error\nIvalid extention\n");
		exit (0);
	}
}
