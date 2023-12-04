/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialvarez <ialvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 14:53:49 by ialvarez          #+#    #+#             */
/*   Updated: 2023/12/04 17:55:38 by ialvarez         ###   ########.fr       */
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
# define WIDTH 1080
# define HEIGHT 720
# define TILE_SIZE 20
# define MINIMAP_WIDTH_PERCENTAGE 20
# define MINIMAP_HEIGHT_PERCENTAGE 20

# define DEGREES_E 0
# define DEGREES_N 1.5708
# define DEGREES_W 3.14159
# define DEGREES_S 4.71239
# define DEGREES_360 6.28319

# define KEY_UP 126
# define KEY_DOWN 125
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_W 13
# define KEY_S 1
# define KEY_A 0
# define KEY_D 2
# define KEY_ESC 53

# define TRANSPARENT 0x00000000 //?
# define WALL_COLOR 0xFF0000 //?

typedef struct s_img
{
	void	*img;
	int		width;
	int		height;
	char	*addr;
	int		bpp;
	int		len;
	int		endian;
}				t_img;

typedef struct s_texture
{
	t_img	n;
	t_img	s;
	t_img	e;
	t_img	w;
	int		floor;
	int		ceiling;
}				t_texture;

typedef struct s_bres
{
	float	x;
	float	y;
	float	end_x;
	float	end_y;
}	t_bres;		//Bresenham's line algorithm

typedef struct s_check
{
	int	ini;
	int	end;
	int	flag;
	int	fin;
	int	cord;
}				t_check;

typedef struct s_player
{
	float	x;
	float	y;
	float	angle;
	float	plane_x;
	float	plane_y;
	int		mouse;
}				t_player;

typedef struct s_info
{
	char	*n;
	char	*s;
	char	*w;
	char	*e;
	int		floor;
	int		ceiling;
	char	**map;
}				t_info;

typedef struct s_game
{
	void		*ptr;
	void		*win;
	char		**map;
	int			x_size;
	int			y_size;
	float		wall_h;
	int			floor; //?
	int			ceiling; //?
	t_img		bg;
	t_texture	tex;
	t_player	player;
}				t_game;

typedef struct s_blend
{
	int		r1;
	int		g1;
	int		b1;
	int		r2;
	int		g2;
	int		b2;
	int		blended_r;
	int		blended_g;
	int		blended_b;
}				t_blend;

typedef struct s_minap
{
	int		x;
	int		y;
	int		border_width;
	int		mini_map_width;
	int		mini_map_height;
	int		mini_map_x;
	int		mini_map_y;
	int		cell_x;
	int		cell_y;
	long	bg_color;
	int		game_x;
	int		game_y;
	float	scale_x;
	float	scale_y;
}				t_minap;

t_info	parse_map(char **map);
char	**get_map_info(char **info, int size);
void	check_map(char **map, int i, int j);
void	init_cub(t_game *init, t_info *data);
int		check_extension(char *argv, char *ext);
int		find_start_map(char **map);
int		find_end_map(char **map);
int		find_width_map(char **map, int start, int end);
int		fill_aux(char **filled_map, int i, char **map, int width);
char	**fill_map(char **map, int init, int end, int width);
void	check_one(char *map, int ini, int end);
void	check_sides(char *map, int ini, int end);
void	aux_check_map(char map, int *cord, int i, int fin);
int		is_valid_rgb(const char *str);
void	free_info(t_info *info);
void	draw_mini_map(t_game *game);
void	my_mlx_pixel_put(t_img *img, int x, int y, long color);
void	draw_background(t_img bg, int ceiling, int floor);
void	find_pos(float *x, float *y, char **map);
void	raycasting(t_game *g);
long	blend_colors(long color1, long color2, int weight);
#endif
