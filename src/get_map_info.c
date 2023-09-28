/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_info.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabel-co <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 15:07:23 by dabel-co          #+#    #+#             */
/*   Updated: 2023/09/28 12:52:59 by dabel-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
char	*copy_line(char *line)
{
	int i;
	char *aux;

	i = 0;
	aux = malloc(sizeof(char) * ft_strlen(line) + 1);
	while (line[i] != '\0')
	{
		aux[i] = line[i];
		i++;
	}
	aux[i] = '\0';
	return (aux);
	
}
char	**extract_input(char **info, int size, int i, char *line)
{
	int fd;
	char	**map;
	fd = open(info[1], O_RDONLY);
	map = malloc(sizeof(char *) * size + 8); //what the fuck es esto
	while (i < size)
	{
		get_next_line(fd, &line);
		//printf("size of the line is%d\n", ft_strlen(line));
		//printf("%s\n", line); //debug
		map[i] = copy_line(line);
		i++;
	}
	map[i] = NULL;
	//start debug
	return (map);
}
char	**get_map_info(char **info)
{
	int fd;
	char *line;
	int size;
	char **map;
	size = 0;
	fd = open(info[1], O_RDONLY);
	if (fd < 0)
		printf("error\n");
	while (get_next_line(fd, &line))
		size++;
	printf("size is %d\n", size); //debug
	if (size == 0)
		printf("empty map\n"); //add exit thingy
	close(fd);
	map = extract_input(info, size, 0, line); 
	//debug
	int i = 0;
	while (map[i])
	{
		printf("%s\n", map[i]);
		i++;
	}
}
