/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialvarez <ialvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 14:53:49 by ialvarez          #+#    #+#             */
/*   Updated: 2024/01/17 19:18:15 by ialvarez         ###   ########.fr       */
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

# define TRANSPARENT 0x00000000
# define WALL_COLOR 0xFF0000
# define FOV 1.0472
# define HFOV 0.523599
# define DEGREES_0 0
# define DEGREES_90 1.5708
# define DEGREES_180 3.14159
# define DEGREES_270 4.71239
# define DEGREES_360 6.28319
# define PLAYER_SPEED 0.14
# define PLAYER_ROTATE 0.10

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

typedef struct s_vector
{
	float	x;
	float	y;
}	t_vector;

typedef struct s_bres
{
	float	x;
	float	y;
	float	end_x;
	float	end_y;
}	t_bres;

typedef struct s_check
{
	int	ini;
	int	end;
	int	flag;
	int	fin;
	int	cord;
}				t_check;

typedef struct s_keys
{
	int		w;
	int		a;
	int		s;
	int		d;
	int		left;
	int		right;
}	t_keys;

typedef struct s_player
{
	float	x;
	float	y;
	float	angle;
	float	step_x;
	float	step_y;
	int		mouse;
	t_keys	key;
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
	int		err;
}				t_info;

typedef struct s_game
{
	void		*ptr;
	void		*win;
	char		**map;
	int			x_size;
	int			y_size;
	float		wall_h;
	int			floor;
	int			ceiling;
	float		pl_minimap_y;
	float		pl_minimap_x;
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
	int		bor_width;
	int		mi_map_width;
	int		mi_map_height;
	int		mi_map_x;
	int		mi_map_y;
	int		cell_x;
	int		cell_y;
	long	bg_color;
	int		game_x;
	int		game_y;
	float	scale_x;
	float	scale_y;
	int		pl_mi_map_x;
	int		pl_mi_map_y;
	int		i;
	int		j;
}				t_minap;

t_info	parse_map(char **map);
char	**get_map_info(char **info, int size);
int		check_map(char **map, int i, int j);
void	init_cub(t_game *init, t_info *data);
int		check_extension(char *argv, char *ext);
int		find_start_map(char **map);
int		find_end_map(char **map);
int		find_width_map(char **map, int start, int end);
int		fill_aux(char **filled_map, int i, char **map, int width);
char	**fill_map(char **map, int init, int end, int width);
int		check_one(char *map, int ini, int end);
int		check_sides(char *map, int ini, int end);
int		check_coord(char **map, t_check *c, int fin);
void	init_aux(t_info *aux);
int		is_valid_rgb(const char *str);
void	free_info(t_info *info);
void	draw_mini_map(t_game *game);
void	my_mlx_pixel_put(t_img *img, int x, int y, long color);
void	draw_background(t_img bg, int ceiling, int floor);
float	find_pos(float *x, float *y, char **map);
void	raycasting(t_game *g);
void	check_movement(t_game *g);
int		close_game(t_game *game);
int		my_mlx_pixel_get(t_img *img, int x, int y);
void	draw_line(t_img img, t_bres bres, int texture);
int		key_pressed(int key, t_game *g);
int		key_released(int key, t_game *g);
int		mouse_input(int x, int y, t_game *g);
char	*ft_strtrok(char *str, char delimiter, int *needle);
#endif
