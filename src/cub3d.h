/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialvarez <ialvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 14:53:49 by ialvarez          #+#    #+#             */
/*   Updated: 2023/09/28 18:43:09 by ialvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "get_next_line.h"
# include "../libft/libft.h"
# include "key.h"
# include <mlx.h>
# include <stdio.h>
# include <sys/types.h>
# include <fcntl.h>
# include <math.h>

typedef struct s_rbg
{
	int r;
	int g;
	int b;
}		t_rgb;

typedef struct s_info
{
	char *n;
	char *s;
	char *w;
	char *e;
	t_rgb	floor;
	t_rgb	ceiling;
	char **map;
}		t_info;

t_info	parse_map(char **map);
char	**get_map_info(char **info);
#endif
