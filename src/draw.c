/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialvarez <ialvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 12:29:07 by dabel-co          #+#    #+#             */
/*   Updated: 2023/12/04 19:12:14 by ialvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, long color)
{
	char	*dst;

	dst = img->addr + (y * img->len + x
			* (img->bpp / 8));
	*(unsigned int *)dst = color;
}

void	draw_background(t_img bg, int ceiling, int floor)
{
	int	x;
	int	y;
	int	tex;

	y = 0;
	tex = ceiling;
	while (y < HEIGHT)
	{
		if (y == HEIGHT / 2)
			tex = floor;
		x = 0;
		while (x < WIDTH)
		{
		//	my_mlx_pixel_put(&bg, x, y, tex);
			my_mlx_pixel_put(&bg, x, y, blend_colors(tex,
					(((y * 255) / HEIGHT) << 16), ((y * 255) / HEIGHT)));
			x++;
		}
		y++;
	}
}
