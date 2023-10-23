/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_info.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialvarez <ialvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 15:07:23 by dabel-co          #+#    #+#             */
/*   Updated: 2023/10/23 18:00:28 by ialvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_one(char *map, int ini, int end)
{
	while (map[ini] && ini <= end) 
	{
		if (map[ini] == ' ')
		{
			perror("BAD NEIGHBORHOOD");
			exit(1);
		}
		ini++;
	}
}

void	check_sides(char *map, int ini, int end)
{
	if (map[ini - 1] && ft_strchr("NSEW", map[ini -1]))
	{
		if(map[ini - 2] && map[ini - 2] != '1')
		{
			perror("BAD NEIGHBORHOOD");
			exit(1);
		}
	}
	else if (map[end + 1] && ft_strchr("NSEW", map[end + 1]))
	{
		if (map[end + 2] && map[end + 2] != '1')
		{
			perror("BAD NEIGHBORHOOD");
			exit(1);
		}
	}
	else if ((map[ini - 1] && map[ini - 1] != '1') || (map[end + 1] && map[end + 1] != '1'))
	{
		perror("BAD NEIGHBORHOOD");
		exit(1);
	}
}

void	check_map(char **map, int i, int j, int cord)
{
	int ini;
	int end;
	int flag;

	ini = 0;
	end = 0;
	flag = 0;
	while(map && map[i])
	{
		j = 0;
		while(map[i][j] != '\0')
		{
			if (ft_strchr("NSEW", map[i][j]))
				cord++;
			if (!ft_strchr("01NSEW ", map[i][j]))
			{
				perror("CHARACTERS OF THE MAP NOT VALIDS");
				exit(1);
			}
			else if ((i == 0 || i == find_end_map(map) - 1) && ft_strchr("0NSWE", map[i][j]))
			{
				perror("MAP IS NOT CLOSED");
				exit(1);
			}
			else if (map[i][j] == '0' && i != 0)
			{
				ini = j;
				while(map[i][j] == '0' || (ft_strchr("NSEW", map[i][j]) && map[i][j + 1] == '0'))
				{
					if (ft_strchr("NSEW", map[i][j]))
						cord++;
					flag = ini;
					j++;
				}
				end = j - 1;
			}
			else if (flag != 0)
			{
				check_sides(map[i], ini, end);
				check_one(map[i - 1], ini, end);
				flag = 0;
			}
			j++;
		}
		i++;
	}
	if (cord != 1)
	{
		perror("BAD COORDINATES");
		exit(1);
	}
}

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

char	**get_map_info(char **info, int size)
{
	int fd;
	char *line;
	char **map;

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
