/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialvarez <ialvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 17:47:13 by ialvarez          #+#    #+#             */
/*   Updated: 2023/10/30 15:48:46 by ialvarez         ###   ########.fr       */
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
		if (map[ini - 2] && map[ini - 2] != '1')
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
	else if ((map[ini - 1] && map[ini - 1] != '1')
		|| (map[end + 1] && map[end + 1] != '1'))
	{
		perror("BAD NEIGHBORHOOD");
		exit(1);
	}
}

void	aux_check_map(char map, int *cord, int i, int fin)
{
	if (ft_strchr("NSEW", map))
		(*cord)++;
	if (!ft_strchr("01NSEW ", map))
	{
		perror("CHARACTERS OF THE MAP NOT VALIDS");
		exit(1);
	}
	else if (((i == 0 || i == fin) && ft_strchr("0NSWE", map)))
	{
		perror("MAP IS NOT CLOSED");
		exit(1);
	}
}

 int	is_valid_rgb(const char *str)
{
	int	commas;
	int	i;

	i = 0;
	commas = 0;
	while (str[++i] != '\0')
	{
		if (str[i] == ',')
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
