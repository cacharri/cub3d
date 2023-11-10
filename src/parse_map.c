/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialvarez <ialvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 12:53:09 by dabel-co          #+#    #+#             */
/*   Updated: 2023/11/09 20:52:11 by ialvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*ft_strtrok(char *str, char delimiter, int *needle)
{
	int		j;
	int		in;
	char	*aux;

	aux = NULL;
	j = 0;
	in = (*needle);
	while (str && str[(*needle)++] != '\0')
	{
		while (str[(*needle)] == ' ')
		{
			(*needle)++;
			in = (*needle);
		}
		if (str[(*needle)] == delimiter)
		{
			j = (*needle);
			break ;
		}	
	}
	aux = ft_substr(str, in, j - in);
	return (aux);
}

void	parse_rgb(char *map, int *x)
{
	int		i;
	int		r;
	int		g;
	int		b;

	i = 0;
	if (!is_valid_rgb(map))
	{
		printf("Error: El formato RGB en la línea no es válido.\n");
		exit(1);
	}
	r = ft_atoi(ft_strtrok(map, ',', &i));
	i++;
	g = ft_atoi(ft_strtrok(map, ',', &i));
	b = ft_atoi(&map[(i + 1)]);
	if (r < 0 || r > 255
		|| g < 0 || g > 255
		|| b < 0 || b > 255)
	{
		printf("Colors of RGB are not valid\n");
		exit(1);
	}
	(*x) = 0 << 24 | r << 16 | g << 8 | b;
}

t_info	add_paths(char **map, t_info *aux, int init, int end)
{
	int	i;
	int	width;

	i = -1;
	width = 0;
	while (map && map[++i] != NULL)
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
			parse_rgb(map[i] + 1, &aux->floor);
		else if (ft_strncmp(map[i], "C", 1) == 0)
			parse_rgb(map[i] + 1, &aux->ceiling);
	}
	init = find_start_map(map);
	end = find_end_map(map);
	width = find_width_map(map, init, end);
	aux->map = fill_map(map, init, end, width);
	return (*aux);
}

void	check_files(t_info aux, int fd)
{
	fd = open(aux.n, O_RDONLY);
	if (fd < 0)
		return ;
	close(fd);
	fd = open(aux.s, O_RDONLY);
	if (fd < 0)
		return ;
	close(fd);
	fd = open(aux.e, O_RDONLY);
	if (fd < 0)
		return ;
	close(fd);
	fd = open(aux.w, O_RDONLY);
	if (fd < 0)
		return ;
	close(fd);
}

t_info	parse_map(char	**map)
{
	t_info	aux;
	int		fd;

	aux.n = NULL;
	aux.s = NULL;
	aux.e = NULL;
	aux.w = NULL;
	aux.map = NULL;
	fd = 0;
	aux = add_paths(map, &aux, 0, 0);
	if ((check_extension(aux.n, ".xpm") || check_extension(aux.e, ".xpm")
			|| check_extension(aux.w, ".xpm")
			|| check_extension(aux.s, ".xpm")) == 1)
	{
		perror("Error .xpm extension\n");
		exit(1);
	}
	check_files(aux, fd);
	print_matrix(aux.map);
	return (aux);
}
