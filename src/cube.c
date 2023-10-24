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
	//mlx_loop(init->ptr);
	load_img(init, data);
}
