/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabel-co <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 12:10:05 by dabel-co          #+#    #+#             */
/*   Updated: 2023/12/04 12:10:07 by dabel-co         ###   ########.fr       */
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
				*y = (float)j; //? why float?
			}
			j++;
		}
		i++;
	}
}

long blendColors(long color1, long color2, int weight)
{
    int r1 = (color1 >> 16) & 0xFF;
    int g1 = (color1 >> 8) & 0xFF;
    int b1 = color1 & 0xFF;

    int r2 = (color2 >> 16) & 0xFF;
    int g2 = (color2 >> 8) & 0xFF;
    int b2 = color2 & 0xFF;

    int blendedR = (r1 * (255 - weight) + r2 * weight) / 255;
    int blendedG = (g1 * (255 - weight) + g2 * weight) / 255;
    int blendedB = (b1 * (255 - weight) + b2 * weight) / 255;

    return (blendedR << 16) | (blendedG << 8) | blendedB;
}

void drawMiniMap(t_game *game)
{
	int		x;
	int		y;
	int		borderWidth;
	int		miniMapWidth;
	int		miniMapHeight;
	int		miniMapX;
	int		miniMapY;
	int		cellX;
	int		cellY;
	long	bgColor;
	int		gameX;
	int		gameY;
	float	scaleX;
	float	scaleY;

	x = 0;
	y = -1;
	borderWidth = 2;
	miniMapWidth = (WIDTH * MINIMAP_WIDTH_PERCENTAGE) / 100;
	miniMapHeight = (HEIGHT * MINIMAP_HEIGHT_PERCENTAGE) / 100;
	scaleX = (float)game->x_size / miniMapWidth;
    scaleY = (float)game->y_size / miniMapHeight;
	// Posición del minimapa en la ventana principal
	miniMapX = 10;
	miniMapY = HEIGHT - miniMapHeight - 10;
	// Limpia la imagen del minimapa
	while (++y < miniMapHeight)
	{
		x = -1;
		while (++x < miniMapWidth) {
			cellX = miniMapX + x;
			cellY = miniMapY + y;
			bgColor = 0xFFFFFF;		//Fondo blanco
			// Convierte las coordenadas del minimapa a coordenadas del juego
			gameX = (int)(x * scaleX);
			gameY = (int)(y * scaleY);
			/*if (game->map[gameY][gameX] == '1')
				bgColor = 0x0000FF;  // Pared: Azul*/
			if (game->map[gameY][gameX] == '1')
            {
                // Calcula el sombreado basado en la posición vertical en la pared
                int wallShade = (y * 255) / miniMapHeight;
                // Mezcla el color original de la pared con el sombreado
                bgColor = blendColors(0x0000FF, wallShade << 16, wallShade);
            }
			else if (game->map[gameY][gameX] == '0')
				bgColor = 0xFFFF00;  // Zona 0: Amarillo
			// Agrega un borde alrededor del minimapa
			if (x < borderWidth || x >= miniMapWidth - borderWidth || y < borderWidth || y >= miniMapHeight - borderWidth)
				bgColor = 0x000000;  // Color del borde: negro
			my_mlx_pixel_put(&game->bg, cellX, cellY, bgColor);
			// Jugador
			if (game->player.x == gameX && game->player.y == gameY)
			{
				// Punto rojo más grande
				my_mlx_pixel_put(&game->bg, cellX, cellY, 0xFF0000);
			//	my_mlx_pixel_put(&game->bg, cellX + 1, cellY, 0xFF0000);
			//	my_mlx_pixel_put(&game->bg, cellX, cellY + 1, 0xFF0000);
			//	my_mlx_pixel_put(&game->bg, cellX + 1, cellY + 1, 0xFF0000);
			}
		}
	}
}