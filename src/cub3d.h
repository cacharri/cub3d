/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialvarez <ialvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 14:53:49 by ialvarez          #+#    #+#             */
/*   Updated: 2023/10/17 19:16:40 by ialvarez         ###   ########.fr       */
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

# define VALID " 01NSEO"
# define POSITION "NSEO"
# define CLOSE " 1"
# define WIDTH 1080
# define HEIGHT 720

# define DEGREES_E 0
# define DEGREES_N 1.5708
# define DEGREES_W 3.14159
# define DEGREES_S 4.71239
# define DEGREES_360 6.28319

typedef struct s_rbg
{
	int		r;
	int		g;
	int		b;
}				t_rgb;

typedef struct s_info
{
	char	*n;
	char	*s;
	char	*w;
	char	*e;
	t_rgb	floor;
	t_rgb	ceiling;
	char	**map;
}				t_info;

typedef struct s_game
{
	void	*ptr;
	void	*win;
	int		x_size;
	int		y_size;
	float	wall_h;
	
}				t_game;


t_info	parse_map(char **map);
char	**get_map_info(char **info);
int		find_end_map(char **map);
void    init_cub(t_game *init);
int	check_extension(char *argv, char *ext);

#endif
