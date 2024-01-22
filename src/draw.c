/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialvarez <ialvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 12:29:07 by dabel-co          #+#    #+#             */
/*   Updated: 2024/01/22 17:52:57 by ialvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*ft_strtrok(char *str, char delimiter, int *needle)
{
	int		j;
	int		in;
	char	*aux;

	aux = NULL;
	j = 0;
	in = (*needle);
	while (str && str[(*needle)++] != '\0')
	{
		while (str[(*needle)] == ' ')
		{
			(*needle)++;
			in = (*needle);
		}
		if (str[(*needle)] == delimiter)
		{
			j = (*needle);
			break ;
		}
	}
	aux = ft_substr(str, in, j - in);
	return (aux);
}

int	my_mlx_pixel_get(t_img *img, int x, int y)
{
	char	*dst;

	dst = img->addr + (y * img->len + x * (img->bpp / 8));
	return (*(unsigned int *)dst);
}

void	draw_line(t_img img, t_bres bres, int texture)
{
	float	step_x;
	float	step_y;
	float	dist;
	int		i;

	dist = sqrt(pow(bres.x - bres.end_x, 2)
			+ pow(bres.y - bres.end_y, 2));
	step_x = (bres.end_x - bres.x) / dist;
	step_y = (bres.end_y - bres.y) / dist;
	i = 0;
	while (i < dist)
	{
		my_mlx_pixel_put(&img, (int)(bres.x + step_x * i)
			+ 0, (int)(bres.y + step_y * i)
			+ 0, texture);
		i++;
	}
}

void	my_mlx_pixel_put(t_img *img, int x, int y, long texture)
{
	char	*dst;

	if (x >= 0 && x < img->width && y >= 0 && y < img->height)
	{
		dst = img->addr + (y * img->len
				+ x * (img->bpp / 8));
		*(unsigned int *)dst = texture;
	}
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
			my_mlx_pixel_put(&bg, x, y, tex);
			x++;
		}
		y++;
	}
}
