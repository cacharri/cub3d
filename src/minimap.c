/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialvarez <ialvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 12:10:05 by dabel-co          #+#    #+#             */
/*   Updated: 2023/12/04 18:46:41 by ialvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	find_pos(float *x, float *y, char **map)
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
			}
			j++;
		}
		i++;
	}
}

long	blend_colors(long color1, long color2, int weight)
{
	t_blend		c;

	ft_bzero(&c, sizeof(t_blend));
	c.r1 = (color1 >> 16) & 0xFF;
	c.g1 = (color1 >> 8) & 0xFF;
	c.b1 = color1 & 0xFF;
	c.r2 = (color2 >> 16) & 0xFF;
	c.g2 = (color2 >> 8) & 0xFF;
	c.b2 = color2 & 0xFF;
	c.blended_r = (c.r1 * (255 - weight) + c.r2 * weight) / 255;
	c.blended_g = (c.g1 * (255 - weight) + c.g2 * weight) / 255;
	c.blended_b = (c.b1 * (255 - weight) + c.b2 * weight) / 255;
	return ((c.blended_r << 16) | (c.blended_g << 8) | c.blended_b);
}

void	color_minimap(t_minap *c, t_game *game)
{
	while (++c->x < c->mini_map_width)
	{
		c->cell_x = c->mini_map_x + c->x;
		c->cell_y = c->mini_map_y + c->y;
		c->bg_color = 0xFFFFFF;
		c->game_x = (int)(c->x * c->scale_x);
		c->game_y = (int)(c->y * c->scale_y);
		if (game->map[c->game_y][c->game_x] == '1')
			c->bg_color = 0x0000FF;
		else if (game->map[c->game_y][c->game_x] == '0')
			c->bg_color = 0xFFFF00;
		if (c->x < c->border_width
			|| c->x >= c->mini_map_width - c->border_width
			|| c->y < c->border_width
			|| c->y >= c->mini_map_height - c->border_width)
			c->bg_color = 0x000000;
		my_mlx_pixel_put(&game->bg, c->cell_x, c->cell_y, c->bg_color);
		if (game->player.x == c->game_x && game->player.y == c->game_y)
			my_mlx_pixel_put(&game->bg, c->cell_x, c->cell_y, 0xFF0000);
	}
}

void	draw_mini_map(t_game *game)
{
	t_minap		c;

	ft_bzero(&c, sizeof(t_minap));
	c.x = 0;
	c.y = -1;
	c.border_width = 2;
	c.mini_map_width = (WIDTH * MINIMAP_WIDTH_PERCENTAGE) / 100;
	c.mini_map_height = (HEIGHT * MINIMAP_HEIGHT_PERCENTAGE) / 100;
	c.scale_x = (float)game->x_size / c.mini_map_width;
	c.scale_y = (float)game->y_size / c.mini_map_height;
	c.mini_map_x = 10;
	c.mini_map_y = HEIGHT - c.mini_map_height - 10;
	while (++c.y < c.mini_map_height)
	{
		c.x = -1;
		color_minimap(&c, game);
	}
}
