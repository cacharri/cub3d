/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialvarez <ialvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 16:34:06 by dabel-co          #+#    #+#             */
/*   Updated: 2024/01/22 18:00:58 by ialvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_texture_color(t_game *g, t_img *img, t_vector ray, int y)
{
	int	color;
	int	x;

	color = 0;
	x = (int)(img->width * (ray.x + ray.y)) % img->width;
	if (g->map[(int)ray.y][(int)ray.x] == '1')
		color = my_mlx_pixel_get(img, x, y);
	return (color);
}

t_img	get_texture_img(t_game *g, t_vector ray, float ray_angle)
{
	t_img	texture_img;
	float	step_x;
	float	step_y;

	ft_bzero(&texture_img, sizeof(t_img));
	step_x = cos(ray_angle) / 90;
	step_y = sin(ray_angle) / 90;
	if (step_x < 0)
		step_x = -step_x;
	if (step_y < 0)
		step_y = -step_y;
	if (g->map[(int)(ray.y - step_y)][(int)ray.x] != '1')
		texture_img = g->tex.n;
	else if (g->map[(int)(ray.y + step_y)][(int)ray.x] != '1')
		texture_img = g->tex.s;
	else if (g->map[(int)ray.y][(int)(ray.x - step_x)] != '1')
		texture_img = g->tex.w;
	else if (g->map[(int)ray.y][(int)(ray.x + step_x)] != '1')
		texture_img = g->tex.e;
	return (texture_img);
}

void	draw_walls(t_game *g, t_img texture, t_vector ray, int ray_count)
{
	int		i;
	float	step_y;
	int		color;
	t_bres	draw;

	step_y = g->wall_h * 2 / texture.height;
	draw.x = ray_count;
	draw.end_x = ray_count;
	draw.y = (HEIGHT / 2) - g->wall_h;
	i = 0;
	while (i < texture.height && draw.y < HEIGHT)
	{
		color = get_texture_color(g, &texture, ray, i);
		draw.end_y = draw.y + step_y;
		draw_line(g->bg, draw, color);
		draw.y += step_y;
		i++;
	}
}

void	dist_to_wall(float ray_angle, int ray_count, t_game *g, t_vector ray)
{
	float	distance;
	t_img	texture_img;

	distance = sqrt(pow(ray.x - g->player.x - 0.5, 2)
			+ pow(ray.y - g->player.y - 0.5, 2));
	distance = distance * cos(ray_angle - g->player.angle);
	g->wall_h = 475 / distance;
	texture_img = get_texture_img(g, ray, ray_angle);
	draw_walls(g, texture_img, ray, ray_count);
}

void	raycasting(t_game *g)
{
	int			ray_count;
	float		ray_angle;
	float		ray_cos;
	float		ray_sin;
	t_vector	ray;

	ray_count = -1;
	ray_angle = g->player.angle - HFOV;
	ft_bzero(&ray, sizeof(t_vector));
	while (++ray_count < WIDTH)
	{
		ray.x = g->player.x + 0.5;
		ray.y = g->player.y + 0.5;
		ray_cos = cos(ray_angle) / 90;
		ray_sin = sin(ray_angle) / 90;
		while (ray.x < g->x_size && ray.y < g->y_size && ray.x >= 0 && ray.y
			>= 0 && g->map[(int)floor(ray.y)][(int)floor(ray.x)] != '1')
		{
			ray.x += ray_cos;
			ray.y += ray_sin;
		}
		if (ray.x >= 0 && ray.y >= 0 && ray.x < g->x_size && ray.y < g->y_size)
			dist_to_wall(ray_angle, ray_count, g, ray);
		ray_angle += FOV / WIDTH;
	}
}
