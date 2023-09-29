/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialvarez <ialvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 12:53:09 by dabel-co          #+#    #+#             */
/*   Updated: 2023/09/29 22:44:29 by ialvarez         ###   ########.fr       */
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
	ft_memset(color, '0', sizeof(t_rgb));
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

int		find_start_map(char **map)
{
	int		i;

	i = -1;
	while(map && map[++i] != NULL)
	{
		if (!ft_strchr("NSEWFC", map[i][0]) && ft_strchr(map[i], '1'))
			break ;
	}
	return (i);
}

int		find_end_map(char **map)
{
	int	i;

	i = -1;
	while(map && map[i] != NULL)
		i++;
	i--;
	while(map && map[i])
	{
		if (ft_strchr(map[i], '1'))
			break ;
		i--;
	}
	i++;
	return (i);
}

int		find_width_map(char **map, int start, int end)
{
	int	i;
	int	max;

	i = 0;
	max = 0;
	while (map && map[start] && start != end)
	{
		max = ft_strlen(map[start]);
		if (max > i)
			i = max;
		start++;
	}
	return (i);
}
char **fill_map(char **map, int init, int end, int width)
{
    char **filled_map;
	int		j;
	int		i;
	
	i = init;
	filled_map = NULL;
	filled_map = (char **)malloc(sizeof(char *) * (end - init + 1));
	ft_memset(filled_map, '0', ((end - init) + 1) * sizeof(char *));
    if (!filled_map)
        return (NULL);
    while (i < end)
	{
        filled_map[i - init] = (char *)malloc(sizeof(char ) *(width + 1));
		ft_memset(filled_map[i - init], '0', (width + 1) * sizeof(char));
        if (!filled_map[i - init]) 
		{
            j = -1;
            while (++j < i - init)
                free(filled_map[j]);
            free(filled_map);
            return (NULL);
        }
		j = -1;
	//	printf("wid->%d\n", width);
		while (++j < width)
		{
			printf("i->%d j->%d init->%d\n", i, j, init);
            if (map[i][j] != '\0')
				filled_map[i - init][j] = map[i][j];
			else
			    filled_map[i - init][j] = 32;
		//	printf("linea->%c  | ", filled_map[i - init][j]);
        }
        filled_map[i - init][j] = '\0';
		//printf("fila->%s  | ", filled_map[i - init]);
		i++;
    }
    filled_map[end - init] = NULL;
    return (filled_map);
}

t_info	add_paths(char **map, t_info *aux)
{
	int i;
	int init;
	int	end;
	int	width;

	i = -1;
	init = 0;
	end = 0;
	width = 0;
	
	while(map && map[++i] != NULL)
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
//	printf("esto es el inicio del mapa->%d\n", init);
//	printf("esto es el final del mapa->%d\n", end);
//	printf("esto es el width del mapa->%d\n", width);
	print_matrix(aux->map);
	return (*aux);
}
t_info	parse_map(char	**map)
{
	t_info	aux;
	
	aux.n = NULL;
    aux.s = NULL;
    aux.e = NULL;
    aux.w = NULL;
    aux.map = NULL;
    ft_memset(&aux.floor, 0, sizeof(t_rgb));
    ft_memset(&aux.ceiling, 0, sizeof(t_rgb));
	aux = add_paths(map, &aux);
//	printf("norte %s\n", aux.n);
//	printf("sur %s\n", aux.s);
//	printf("este %s\n", aux.e);
//	printf("oeste %s\n", aux.w);
//	printf("floor r%d\n", aux.floor.r);
//	printf("floor g%d\n", aux.floor.g);
//	printf("floor b%d\n", aux.floor.b);
//	printf("cei r%d\n", aux.ceiling.r);
//	printf("cei g%d\n", aux.ceiling.g);
//	printf("cei b%d\n", aux.ceiling.b);
	return (aux);
}
