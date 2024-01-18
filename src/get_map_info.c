/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_info.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialvarez <ialvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 15:07:23 by dabel-co          #+#    #+#             */
/*   Updated: 2024/01/17 20:24:12 by ialvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	aux_check(t_check *c, int i, char **map, int *j)
{
	if (!ft_strchr("1 ", map[i][0]))
		return (4);
	if (map[i][*j] == '0' && i != 0)
	{
		c->ini = *j;
		while (map[i][*j] == '0' || (ft_strchr("NSEW", map[i][*j])
			&& map[i][*j + 1] == '0'))
			(*j)++;
		c->end = *j - 1;
		if (check_sides(map[i], c->ini, c->end) == 3
			|| check_one(map[i - 1], c->ini, c->end) == 3
			|| check_one(map[i + 1], c->ini, c->end) == 3)
			return (3);
	}
	if (ft_strchr("NSEW", map[i][*j]))
	{
		if (check_one(map[i - 1], *j, *j) == 3
			|| check_one(map[i + 1], *j, *j) == 3)
			return (3);
	}
	return (0);
}

int	check_map(char **map, int i, int j)
{
	t_check	c;
	int		err;

	err = 0;
	ft_bzero(&c, sizeof(t_check));
	c.fin = find_end_map(map) - 1;
	err = check_coord(map, &c, c.fin);
	if (c.cord != 1)
		return (1);
	if (err != 0)
		return (err);
	while (map && map[i] != NULL)
	{
		j = 0;
		while (map[i][j] != '\0')
		{
			err = aux_check(&c, i, map, &j);
			if (err != 0)
				return (err);
			j++;
		}
		i++;
	}
	return (0);
}

static void	aux_input(char **map, int *i, int fd, char **line)
{
	if (!map)
	{
		close(fd);
		perror("Memory allocation error");
		return ;
	}
	while (get_next_line(fd, &(*line)))
	{
		map[(*i)] = ft_strdup(*line);
		free(*line);
		(*i)++;
		*line = NULL;
	}
}

char	**extract_input(char **info, int size, int i, char *line)
{
	int		fd;
	char	**map;
	char	*line_copy;

	line_copy = NULL;
	fd = 0;
	map = NULL;
	fd = open(info[1], O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening file");
		return (NULL);
	}
	map = malloc(sizeof(char *) * (size + 2));
	aux_input(map, &i, fd, &line);
	map[i] = ft_strdup(line);
	free(line);
	map[i + 1] = NULL;
	close(fd);
	return (map);
}

char	**get_map_info(char **info, int size)
{
	int		fd;
	char	*line;
	char	**map;

	map = NULL;
	fd = open(info[1], O_RDONLY);
	if (fd < 0)
		return (NULL);
	while (get_next_line(fd, &line))
	{
		size++;
		free(line);
	}
	close(fd);
	map = extract_input(info, size, 0, line);
	free(line);
	return (map);
}
