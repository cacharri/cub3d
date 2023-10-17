/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialvarez <ialvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 17:12:17 by ialvarez          #+#    #+#             */
/*   Updated: 2023/10/16 18:58:35 by ialvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    init_cub(t_game *init)
{
    init->ptr = mlx_init();
    init->win = mlx_new_window(init->ptr, WIDTH, HEIGHT, "cub3d");
}