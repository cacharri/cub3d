/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_info.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialvarez <ialvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 15:07:23 by dabel-co          #+#    #+#             */
/*   Updated: 2023/10/17 16:27:17 by ialvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	**extract_input(char **info, int size, int i, char *line)
{
	int fd;
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
	if (!map)
	{
		close(fd);
		perror("Memory allocation error");
		return (NULL);
	}
	while (get_next_line(fd, &line))
	{
		map[i] = ft_strdup(line);
		free(line);
		i++;
		line = NULL;
	}
	map[i] = ft_strdup(line);
	free(line);
	map[i + 1] = NULL;
	close(fd);
	return (map);
}
char	**get_map_info(char **info)
{
	int fd;
	char *line;
	int size;
	int	i;
	char **map;
	
	size = 0;
	i = 0;
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
	return(map);
}
