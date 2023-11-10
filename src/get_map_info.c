/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_info.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialvarez <ialvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 15:07:23 by dabel-co          #+#    #+#             */
/*   Updated: 2023/11/09 19:38:32 by ialvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	aux_check(t_check *c, int i, char **map, int *j)
{
	if (map[i][0] == '0')
	{
		perror("MAP IS NOT CLOSED");
		exit(1);
	}
	if (map[i][*j] == '0' && i != 0)
	{
		c->ini = *j;
		while (map[i][*j] == '0' || (ft_strchr("NSEW", map[i][*j])
			&& map[i][*j + 1] == '0'))
		{
			if (ft_strchr("NSEW", map[i][*j]))
				c->cord++;
			c->flag = c->ini;
			(*j)++;
		}
		c->end = *j - 1;
	}
	else if (c->flag != 0)
	{
		check_sides(map[i], c->ini, c->end);
		check_one(map[i - 1], c->ini, c->end);
		c->flag = 0;
	}
}

void	check_map(char **map, int i, int j)
{
	t_check	c;

	ft_bzero(&c, sizeof(t_check));
	c.fin = find_end_map(map) - 1;
	while (map && map[i])
	{
		j = 0;
		while (map[i][j] != '\0')
		{
			aux_check_map(map[i][j], &c.cord, i, c.fin);
			aux_check(&c, i, map, &j);
			j++;
		}
		i++;
	}
	if (c.cord != 1)
	{
		perror("BAD COORDINATES");
		exit(1);
	}
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
	{
		perror("Error opening file");
		return (NULL);
	}
	while (get_next_line(fd, &line))
	{
		size++;
		free(line);
	}
	close(fd);
	if (size == 0)
	{
		printf("Empty map\n");
		return (NULL);
	}
	map = extract_input(info, size, 0, line);
	free(line);
	return (map);
}
