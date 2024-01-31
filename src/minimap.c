/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialvarez <ialvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 12:10:05 by dabel-co          #+#    #+#             */
/*   Updated: 2024/01/31 16:02:02 by ialvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	set_angles(char c)
{
	if (c == 'N')
		return (DEGREES_0);
	else if (c == 'E')
		return (DEGREES_90);
	else if (c == 'S')
		return (DEGREES_180);
	else if (c == 'W')
		return (DEGREES_270);
	return (0);
}

float	find_pos(float *x, float *y, char **map)
{
	int		i;
	int		j;

	i = 0;
	while (map && map[i] != NULL)
	{
		j = 0;
		while (map && map[i][j] != 0)
		{
			if (ft_strchr("NSWE", map[i][j]))
			{
				*x = (float)i;
				*y = (float)j;
				return (set_angles(map[i][j]));
			}
			j++;
		}
		i++;
	}
	return (0);
}

void	aux_minimap(t_minap **c)
{
	(*c)->cell_y = (*c)->mi_map_y + (*c)->y;
	(*c)->cell_x = (*c)->mi_map_x + (*c)->x;
	(*c)->bg_color = 0xFFFFFF;
	(*c)->game_x = (int)((*c)->x * (*c)->scale_x);
	(*c)->game_y = (int)((*c)->y * (*c)->scale_y);
}

void	color_minimap(t_minap *c, t_game *game)
{
	c->pl_mi_map_x = game->player.x / c->scale_x;
	c->pl_mi_map_y = (game->player.y / c->scale_y) + 4;
	c->i = -2;
	while (++c->x < c->mi_map_width)
	{
		aux_minimap(&c);
		if (game->map[c->game_y][c->game_x] == '1')
			c->bg_color = 0x0000FF;
		else if (game->map[c->game_y][c->game_x] == '0'
			|| ft_strchr("NSEW", game->map[c->game_y][c->game_x]))
			c->bg_color = 0xFFFF00;
		if (c->x < c->bor_width || c->x >= c->mi_map_width - c->bor_width
			|| c->y < c->bor_width || c->y >= c->mi_map_height - c->bor_width)
			c->bg_color = 0x000000;
		my_mlx_pixel_put(&game->bg, c->cell_x, c->cell_y, c->bg_color);
	}
	while (c->i++ <= 2)
	{
		c->j = -2;
		while (c->j++ <= 2)
			my_mlx_pixel_put(&game->bg, c->mi_map_x + c->pl_mi_map_x
				+ c->i, c->mi_map_y + c->pl_mi_map_y + c->j, 0xFF0000);
	}
}

void	draw_mini_map(t_game *game)
{
	t_minap		c;

	ft_bzero(&c, sizeof(t_minap));
	c.x = 0;
	c.y = -1;
	c.bor_width = 2;
	c.mi_map_width = (WIDTH * MINIMAP_WIDTH_PERCENTAGE) / 100;
	c.mi_map_height = (HEIGHT * MINIMAP_HEIGHT_PERCENTAGE) / 100;
	c.scale_x = (float)game->x_size / c.mi_map_width;
	c.scale_y = (float)game->y_size / c.mi_map_height;
	c.mi_map_x = 10;
	c.mi_map_y = HEIGHT - c.mi_map_height - 10;
	while (++c.y < c.mi_map_height)
	{
		c.x = -1;
		color_minimap(&c, game);
	}
}
