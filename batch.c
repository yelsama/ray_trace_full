/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canvas.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymohamed <ymohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 12:13:58 by ymohamed          #+#    #+#             */
/*   Updated: 2023/02/01 22:09:14 by ymohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytrace.h"

int	rgb_to_int(const t_color *c)
{
	int	color;

	color = 0;
	if (!c)
		return (write(2, "Error, no color to convert\n", 27), 0);
	color |= (int)(c->red) << 16;
	color |= (int)(c->green) << 8;
	color |= (int)(c->blue);
	return (color);
}

int	fill_batch(t_batch *can, const t_color *c, int width, int height)
{
	if (!can)
		return (write(2, "Error filling canavs\n", 22), 0);
	can->height = height;
	can->width = width;
	if (c)
		can->color = rgb_to_int(c);
	else
		can->color = 0;
	return (1);
}

int	paint_batch_at_mlx(const t_batch *can, t_ranger *alive)
{
	int	y;
	int	x;

	y = -1;
	while (++y <= BATCH_HEIGHT)
	{
		x = -1;
		while (++x <= BATCH_WIDTH)
			mlx_pixel_put(alive->frame.frame_ptr, alive->frame.window,
				x + can->width, y + can->height, can->color);
	}
	return (1);
}
