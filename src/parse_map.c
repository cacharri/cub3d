/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialvarez <ialvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 12:53:09 by dabel-co          #+#    #+#             */
/*   Updated: 2024/01/22 18:06:18 by ialvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	parse_rgb(char *map, int *x)
{
	int		i;
	int		r;
	int		g;
	int		b;

	i = 0;
	if (!is_valid_rgb(map))
		return (1);
	r = ft_atoi(ft_strtrok(map, ',', &i));
	i++;
	g = ft_atoi(ft_strtrok(map, ',', &i));
	b = ft_atoi(&map[(i + 1)]);
	if (r < 0 || r > 255
		|| g < 0 || g > 255
		|| b < 0 || b > 255)
	{
		printf("Colors of RGB are not valid\n");
		return (1);
	}
	(*x) = 0 << 24 | r << 16 | g << 8 | b;
	return (0);
}

void	add_paths_aux(char **map, t_info *aux, int i)
{
	if (ft_strncmp(map[i], "NO", 2) == 0)
		aux->n = ft_strtrim(map[i] + 2, " \t");
	else if (ft_strncmp(map[i], "SO", 2) == 0)
		aux->s = ft_strtrim(map[i] + 2, " \t");
	else if (ft_strncmp(map[i], "EA", 2) == 0)
		aux->e = ft_strtrim(map[i] + 2, " \t");
	else if (ft_strncmp(map[i], "WE", 2) == 0)
		aux->w = ft_strtrim(map[i] + 2, " \t");
	else if (ft_strncmp(map[i], "F", 1) == 0)
		aux->err = parse_rgb(map[i] + 1, &aux->floor);
	else if (ft_strncmp(map[i], "C", 1) == 0)
		aux->err = parse_rgb(map[i] + 1, &aux->ceiling);
}

t_info	add_paths(char **map, t_info *aux, int init, int end)
{
	int	i;
	int	width;

	i = -1;
	while (map && map[++i] != NULL)
		add_paths_aux(map, aux, i);
	if (aux->err == 1)
		return (*aux);
	init = find_start_map(map);
	end = find_end_map(map);
	if (init + 1 == end || end < init || end == 0)
		return (*aux);
	width = find_width_map(map, init, end);
	aux->map = fill_map(map, init, end, width);
	return (*aux);
}

static int	check_files(t_info aux, int fd)
{
	fd = open(aux.n, O_RDONLY);
	if (fd < 0)
		return (1);
	close(fd);
	fd = open(aux.s, O_RDONLY);
	if (fd < 0)
		return (1);
	close(fd);
	fd = open(aux.e, O_RDONLY);
	if (fd < 0)
		return (1);
	close(fd);
	fd = open(aux.w, O_RDONLY);
	if (fd < 0)
		return (1);
	close(fd);
	return (0);
}

t_info	parse_map(char	**map)
{
	t_info	aux;
	int		fd;

	init_aux(&aux);
	fd = 0;
	aux = add_paths(map, &aux, 0, 0);
	if (!aux.map || aux.ceiling == 257 || aux.floor == 257
		|| map == NULL || aux.err == 1)
	{
		aux.err = 2;
		return (aux);
	}
	if ((check_extension(aux.n, ".xpm") || check_extension(aux.e, ".xpm")
			|| check_extension(aux.w, ".xpm")
			|| check_extension(aux.s, ".xpm")) == 1)
	{
		aux.err = 6;
		return (aux);
	}
	if (check_files(aux, fd) == 1)
		aux.err = 7;
	return (aux);
}
