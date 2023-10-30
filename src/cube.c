/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialvarez <ialvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 17:12:17 by ialvarez          #+#    #+#             */
/*   Updated: 2023/10/24 17:34:28 by ialvarez         ###   ########.fr       */
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

int	game(t_game *game)
{
	mlx_clear_window(game->ptr, game->win);
	//check_movement(g);
	draw_background(game->bg, game->ceiling, game->floor);
	//raycast(g);
	mlx_put_image_to_window(game->ptr, game->win, game->bg.img, 0, 0);
	return(0);	
}
static void	load_img(t_game *x, t_info *data)
{
	x->tex.n.img = mlx_xpm_file_to_image(x->ptr, data->s,
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
void	init_cub(t_game *init, t_info *data)
{	
	init->ptr = mlx_init();
	init->win = mlx_new_window(init->ptr, WIDTH, HEIGHT, "cub3d");
	load_img(init, data);
	init->map = copy_matrix(data->map);
	init->floor = data->floor;
	init->ceiling = data->ceiling;
	free_info(data);
	mlx_loop_hook(init->ptr, game, init);
	mlx_loop(init->ptr);
}
