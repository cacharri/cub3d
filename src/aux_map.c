/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialvarez <ialvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 17:47:13 by ialvarez          #+#    #+#             */
/*   Updated: 2024/01/24 16:49:33 by ialvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_aux(t_info *aux)
{
	(*aux).n = NULL;
	(*aux).s = NULL;
	(*aux).e = NULL;
	(*aux).w = NULL;
	(*aux).map = NULL;
	(*aux).floor = 257;
	(*aux).ceiling = 257;
	(*aux).err = 0;
}

int	check_coord(char **map, t_check *c, int fin)
{
	int	i;
	int	j;

	i = -1;
	while (map && map[++i] != NULL)
	{
		j = 0;
		while (map[i][j] != '\0')
		{
			if (ft_strchr("NSEW", map[i][j]))
				(*c).cord++;
			if (!ft_strchr("01NSEW ", map[i][j]))
				return (5);
			if (((i == 0 || i == fin) && ft_strchr("0NSWE", map[i][j])))
				return (4);
			j++;
		}
	}
	return (0);
}

int	check_one(char *map, int ini, int end)
{
	while (map[ini] && ini <= end)
	{
		if (map[ini] == ' ')
			return (3);
		ini++;
	}
	return (0);
}

int	check_sides(char *map, int ini, int end)
{
	if (map[ini - 1] && ft_strchr("NSEW", map[ini -1]))
	{
		if (map[ini - 2] && map[ini - 2] != '1')
			return (3);
	}
	if (map[end + 1] && ft_strchr("NSEW", map[end + 1]))
	{
		if ((map[end + 2] && map[end + 2] != '1') || !map[end + 2])
			return (3);
	}
	else if (((map[ini - 1] && map[ini - 1] != '1')
			|| (map[end + 1] && map[end + 1] != '1'))
		&& !ft_strchr("NSEW", map[ini - 1]))
		return (3);
	return (0);
}

int	is_valid_rgb(const char *str)
{
	int	commas;
	int	i;

	i = 0;
	commas = 0;
	while (str[++i] != '\0')
	{
		if (str[i] == ',' && str[i - 1] != ',')
		{
			commas++;
			if (commas > 2)
				return (0);
		}
		else if (!ft_isdigit(str[i]) && str[i] != '\t' && str[i] != 32)
			return (0);
	}
	return (commas == 2);
}
