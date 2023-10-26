/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialvarez <ialvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 16:37:28 by ialvarez          #+#    #+#             */
/*   Updated: 2023/10/26 15:21:03 by ialvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	find_start_map(char **map)
{
	int		i;

	i = -1;
	while (map && map[++i] != NULL)
	{
		if (!ft_strchr("NSEWFC", map[i][0]) && ft_strchr(map[i], '1'))
			break ;
	}
	return (i);
}

int	find_end_map(char **map)
{
	int	i;

	i = 0;
	if (map)
	{
		while (map && map[i] != NULL)
			i++;
		i--;
	}
	while (map && map[i])
	{
		if (ft_strchr(map[i], '1'))
			break ;
		i--;
	}
	i++;
	return (i);
}

int	find_width_map(char **map, int start, int end)
{
	int	i;
	int	max;

	i = 0;
	max = 0;
	while (map && map[start] && start != end + 1)
	{
		max = ft_strlen(map[start]);
		if (max > i)
			i = max;
		start++;
	}
	return (i);
}

int	fill_aux(char **filled_map, int i, char **map, int width)
{
	int	j;
	int	init;
	int	end;

	init = find_start_map(map);
	end = find_end_map(map);
	if (!filled_map[i - init])
	{
		j = -1;
		while (++j <= end - init)
			free(filled_map[j]);
		free(filled_map);
		exit (0);
	}
	j = -1;
	while (++j <= width)
	{
		if (map && map[i][j])
			filled_map[i - init][j] = map[i][j];
		else
			return (1);
	}
	return (0);
}

char	**fill_map(char **map, int init, int end, int width)
{
	char	**filled_map;
	int		i;

	i = init;
	filled_map = NULL;
	filled_map = (char **)malloc(sizeof(char *) * ((end - init) + 1));
	ft_memset(filled_map, 32, (size_t)(end - init) + 1);
	if (!filled_map)
		return (NULL);
	while (i < end)
	{
		filled_map[i - init] = (char *)malloc(sizeof(char ) * (width + 1));
		ft_memset(filled_map[i - init], 32, (size_t)(width + 1));
		if (fill_aux(filled_map, i, map, width) == 1)
			filled_map[i - init][width] = '\0';
		i++;
	}
	filled_map[(end - init)] = NULL;
	return (filled_map);
}
