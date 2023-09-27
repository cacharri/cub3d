/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_info.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabel-co <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 15:07:23 by dabel-co          #+#    #+#             */
/*   Updated: 2023/09/27 19:53:52 by dabel-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
char	**copy_matrix(char **matrix)
{
	char	**dst;
	int		i;
	if (!matrix)
		return (NULL);
	i = 0;
	while (matrix[i] != NULL)
		i++;
	dst = malloc(sizeof(char **) * i + 1);
	i = 0;
	while (matrix[i] != NULL)
	{
		dst[i] = ft_strdup(matrix[i]);
		i++;
	}
	dst[i] = NULL;
	return (dst);
}

void	free_matrix(char **matrix)
{
	int	i;
	i = -1;
	while (matrix[++i] != NULL)
		free(matrix[i]);
	free(matrix);
}

int		map_len(char **map)
{
	int i;

	i = 0;
	while (map && map[i])
		i++;
	return (i);
}
char	**add_line(char **info, char **line)
{
	int i;
	int len;
	char **aux;

	aux = NULL;
	if (!info)
	{
		aux = malloc (sizeof(char *) * 2);
		aux[0] = *line;
		aux[1] = NULL;
		return (aux);
	}
	len = map_len(info);
	aux = malloc(sizeof(char *) * (len + 2));
	while (i < len)
	{
		aux[i] = ft_strdup(info[i]);
		i++;
	}
	aux[len] = *line;
	aux[len + 1] = NULL;
	return (aux);
}

char	**get_map_info_aux(int ret, char **line, int fd)
{
	char **info;
	char **aux;

	info = NULL;
	aux = NULL;
	while (ret > 0)
	{
		aux = add_line(info, line);
		free_matrix(info);
		info = copy_matrix(aux);
		free_matrix(aux);
		ret = get_next_line(fd, line);
	}
	return (info);
}

char	**get_map_info(char **info)
{
	int fd;
	char *line;
	int ret;

	line = NULL;
	fd = open(info[1], O_RDONLY);
	if (fd < 0)
		printf("error\n");
	ret = get_next_line(fd, &line);
	if (!ret)
		printf("empty map\n");
	info = get_map_info_aux(ret, &line, fd);
}
