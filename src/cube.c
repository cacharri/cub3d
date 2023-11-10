/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialvarez <ialvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 17:12:17 by ialvarez          #+#    #+#             */
/*   Updated: 2023/11/10 22:32:30 by ialvarez         ###   ########.fr       */
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
			my_mlx_pixel_put(&bg, x, y, tex);
			x++;
		}
		y++;
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
				my_mlx_pixel_put(&game->bg, cellX + 1, cellY, 0xFF0000);
				my_mlx_pixel_put(&game->bg, cellX, cellY + 1, 0xFF0000);
				my_mlx_pixel_put(&game->bg, cellX + 1, cellY + 1, 0xFF0000);
			}
		}
	}
	mlx_put_image_to_window(game->ptr, game->win, game->bg.img, 0, 0);
}

int	game(t_game *game)
{
	mlx_clear_window(game->ptr, game->win);

	draw_background(game->bg, game->ceiling, game->floor);
	drawMiniMap(game);
	//check_movement(g);
	//raycast(g);
	mlx_put_image_to_window(game->ptr, game->win, game->bg.img, 0, 0);
	return(0);	
}

static void	load_img(t_game *x, t_info *data)
{
	x->tex.n.img = mlx_xpm_file_to_image(x->ptr, data->n,
			&x->tex.n.width, &x->tex.n.height);
	x->tex.n.addr = mlx_get_data_addr(x->tex.n.img, &x->tex.n.bpp,
			&x->tex.n.len, &x->tex.n.endian);
	x->tex.s.img = mlx_xpm_file_to_image(x->ptr, data->s,
			&x->tex.s.width, &x->tex.s.height);
	x->tex.s.addr = mlx_get_data_addr(x->tex.s.img, &x->tex.s.bpp,
			&x->tex.s.len, &x->tex.s.endian);
	x->tex.e.img = mlx_xpm_file_to_image(x->ptr, data->e,
			&x->tex.e.width, &x->tex.e.height);
	x->tex.e.addr = mlx_get_data_addr(x->tex.e.img, &x->tex.e.bpp,
			&x->tex.e.len, &x->tex.e.endian);
	x->tex.w.img = mlx_xpm_file_to_image(x->ptr, data->w,
			&x->tex.w.width, &x->tex.w.height);
	x->tex.w.addr = mlx_get_data_addr(x->tex.w.img, &x->tex.w.bpp,
			&x->tex.w.len, &x->tex.w.endian);

	x->bg.width = WIDTH;
	x->bg.height = HEIGHT;
	x->bg.img = mlx_new_image(x->ptr, WIDTH, HEIGHT);
	x->bg.addr = mlx_get_data_addr(x->bg.img, &x->bg.bpp,
			&x->bg.len, &x->bg.endian);
}

int	close_game(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
	{
		mlx_destroy_window(game->ptr, game->win);
		exit(0);
	}
	return (0);
}

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
				printf("i:%d\nj:%d\n", i, j);
				*x = (float)i;		// comprobar estos valores si son correctos
				*y = (float)j;		//
			}
			j++;
		}
		i++;
	}
}

void	init_cub(t_game *init, t_info *data)
{	
	init->y_size = find_end_map(data->map);
	init->x_size = find_width_map(data->map, find_start_map(data->map), find_end_map(data->map));
	find_pos(&init->player.y, &init->player.x, data->map);
	init->ptr = mlx_init();
	init->win = mlx_new_window(init->ptr, WIDTH, HEIGHT, "cub3d");
	load_img(init, data);
	init->map = copy_matrix(data->map);
	init->floor = data->floor;
	init->ceiling = data->ceiling;
	free_info(data);
	mlx_loop_hook(init->ptr, game, init);
	mlx_hook(init->win, 17, 1L << 0, close_game, init);
	mlx_hook(init->win, 2, 1L << 0, close_game, init);
	mlx_loop(init->ptr);
}
