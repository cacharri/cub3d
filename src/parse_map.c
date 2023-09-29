/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialvarez <ialvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 12:53:09 by dabel-co          #+#    #+#             */
/*   Updated: 2023/09/29 15:52:11 by ialvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*ft_strtrok(char *str, char delimiter, int *needle)
{
	int j;
	int in;
	char	*aux;

	aux = NULL;
	j = 0;
	in = (*needle);
	while(str && str[++(*needle)] != '\0')
	{
		while(str[(*needle)++] == ' ')
			in = (*needle);
		if (str[(*needle)] == delimiter)
		{
			j = (*needle);
			break ;
		}	
	}
	aux = ft_substr(str, in, j - 1);
	return (aux);
}

void	parse_rgb(char *map, t_rgb *color)
{
	int		i;

	i = -1;
	color->r = ft_atoi(ft_strtrok(map, ',', &i));
	color->g = ft_atoi(ft_strtrok(map, ',', &i));
	color->b = ft_atoi(&map[(i + 1)]);
	if (color->r < 0 || color->r > 255 ||
    	color->g < 0 || color->g > 255 ||
   		color->b < 0 || color->b > 255)	
	{
		printf("Colors of RGB are not valid\n");
		exit(1);
	}
}

t_info	add_paths(char **map, t_info *aux)
{
	int i;
	int flag;
	char *path;

	
	flag = 0;
	i = -1;
	path = NULL;
	
	while(map && map[++i] != NULL)
	{
		if (ft_strncmp(map[i], "NO", 2) == 0)
		{
			path = ft_strtrim(map[i] + 2, " \t");
    		if (path)
        		aux->n = path;
		}
		else if (ft_strncmp(map[i], "SO", 2) == 0)
		{
			path = ft_strtrim(map[i] + 2, " \t");
    		if (path)
				aux->s = path;
		}
		else if (ft_strncmp(map[i], "EA", 2) == 0)
		{
			path = ft_strtrim(map[i] + 2, " \t");
    		if (path)
				aux->e = path;
		}
		else if (ft_strncmp(map[i], "WE", 2) == 0)
		{
			path = ft_strtrim(map[i] + 2, " \t");
    		if (path)
				aux->w = path;
		}
		else if (ft_strncmp(map[i], "F", 1) == 0)
			parse_rgb(map[i] + 1, &aux->floor);
		else if (ft_strncmp(map[i], "C", 1) == 0)
			parse_rgb(map[i] + 1, &aux->ceiling);
	}
	return (*aux);
}
t_info	parse_map(char	**map)
{
	t_info	aux;
	
	aux = add_paths(map, &aux);
	printf("norte %s\n", aux.n);
	printf("sur %s\n", aux.s);
	printf("este %s\n", aux.e);
	printf("oeste %s\n", aux.w);
	printf("floor r%d\n", aux.floor.r);
	printf("floor g%d\n", aux.floor.g);
	printf("floor b%d\n", aux.floor.b);
	printf("cei r%d\n", aux.ceiling.r);
	printf("cei g%d\n", aux.ceiling.g);
	printf("cei b%d\n", aux.ceiling.b);
	return (aux);
}
