/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymohamed <ymohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 08:17:03 by ymohamed          #+#    #+#             */
/*   Updated: 2023/07/18 20:52:28 by ymohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytrace.h"

int	fill_color(t_color *c, float red, float green, float blue)
{
	if (!c)
		return (write(2, "Error filling color\n", 20), 0);
	if (red > 255)
		red = 255;
	if (red < 0)
		red = 0;
	if (green > 255)
		green = 255;
	if (green < 0)
		green = 0;
	if (blue > 255)
		blue = 255;
	if (blue < 0)
		blue = 0;
	c->red = red;
	c->green = green;
	c->blue = blue;
	return (1);
}

t_color	add_colors(const t_color *c1, const t_color *c2)
{
	t_color	result_color;

	result_color = (t_color){0.0, 0.0, 0.0};
	if (!c1 || !c2)
		return (write(2, "Error adding colors\n", 20), result_color);
	result_color.red = c1->red + c2->red;
	result_color.green = c1->green + c2->green;
	result_color.blue = c1->blue + c2->blue;
	if (result_color.red > 255)
		result_color.red = 255;
	if (result_color.green > 255)
		result_color.green = 255;
	if (result_color.blue > 255)
		result_color.blue = 255;
	return (result_color);
}

t_color	subt_colors(const t_color *c1, const t_color *c2)
{
	t_color	result_color;

	result_color = (t_color){0, 0, 0};
	if (!c1 || !c2)
		return (write(2, "Error subtract colors\n", 22), result_color);
	result_color.red = c1->red - c2->red;
	result_color.green = c1->green - c2->green;
	result_color.blue = c1->blue - c2->blue;
	if (result_color.red < 0)
		result_color.red = 0;
	if (result_color.green < 0)
		result_color.green = 0;
	if (result_color.blue < 0)
		result_color.blue = 0;
	return (result_color);
}

t_color	color_multi_scalar(const t_color *c, float sclr)
{
	t_color	result_color;

	result_color = (t_color){0, 0, 0};
	if (!c)
		return (write(2, "No color to scale\n", 18), result_color);
	result_color.red = c->red * sclr;
	result_color.green = c->green * sclr;
	result_color.blue = c->blue * sclr;
	if (result_color.red > 255)
		result_color.red = 255;
	if (result_color.red < 0)
		result_color.red = 0;
	if (result_color.green > 255)
		result_color.green = 255;
	if (result_color.green < 0)
		result_color.green = 0;
	if (result_color.blue > 255)
		result_color.blue = 255;
	if (result_color.blue < 0)
		result_color.blue = 0;
	return (result_color);
}

t_color	blend_two_colors(const t_color *c1, const t_color *c2)
{
	t_color	result_color;
	float	rgb[3];

	result_color = (t_color){0, 0, 0};
	if (!c1 || !c2)
		return (write(2, "Error mixing colors\n", 20), result_color);
	rgb[0] = (c1->red / 255) * (c2->red / 255);
	rgb[1] = (c1->green / 255) * (c2->green / 255);
	rgb[2] = (c1->blue / 255) * (c2->blue / 255);
	result_color.red = rgb[0] * 255;
	result_color.green = rgb[1] * 255;
	result_color.blue = rgb[2] * 255;
	return (result_color);
}
