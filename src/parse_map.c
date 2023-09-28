/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialvarez <ialvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 12:53:09 by dabel-co          #+#    #+#             */
/*   Updated: 2023/09/28 20:28:35 by ialvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
			aux->s = map[i];
		}
		else if (ft_strncmp(map[i], "EA", 2) == 0)
		{
			aux->e = map[i];
		}
		else if (ft_strncmp(map[i], "WE", 2) == 0)
		{
			aux->w = map[i];
		}
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
	return (aux);
}
