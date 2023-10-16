/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialvarez <ialvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 14:53:49 by ialvarez          #+#    #+#             */
/*   Updated: 2023/10/16 17:00:12 by ialvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include <mlx.h>
# include <stdio.h>
# include <sys/types.h>
# include <fcntl.h>
# include <math.h>

# define VALID " 01NSEO"
# define POSITION "NSEO"
# define CLOSE " 1"

# define KEY_UP 126
# define KEY_DOWN 125
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_W 13
# define KEY_S 1
# define KEY_A 0
# define KEY_D 2
# define KEY_ESC 53

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
void	check_map(char **map);

#endif
