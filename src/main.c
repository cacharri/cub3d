/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialvarez <ialvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 13:36:15 by ialvarez          #+#    #+#             */
/*   Updated: 2023/10/04 22:28:42 by ialvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void free_map(char **map, int size)
{
	int	i;

	i = -1;
    while (++i < size)
	{
        free(map[i]);
    }
    free(map);
}

void	check_one(char **map, int ini, int end, int i)  //// este es para las filas de arriba y abajo
{
	int check;
	int bits;
	
	bits = end - ini;
	check = 0;
	while (map && map[i])
	{
		while (map[i][ini] && ini <= end) 
		{
			if (map[i][ini] == '0')
			{
				perror("BAD NEIGHBORHOOD");
				exit(1);
			}
			ini++;
		}
		
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

void	check_map(char **map)
{
	int i = 0;
	int j= 0;
	int bef = 0;
	int ini = 0;
	int end = 0;
	int flag = 0;
	int	cord = 0;

	while(map && map[i])
	{
		bef = i;
		j = 0;
		while(map[i][j] != '\0')
		{
			if (ft_strchr("NSEW", map[i][j]))
			{
				cord++;
			}
			if (!ft_strchr("01NSEW ", map[i][j]))
			{
				perror("CHARACTERS OF THE MAP NOT VALIDS");
				exit(1);
			}
			else if (i == 0 && ft_strchr("0NSWE", map[i][j]))
			{
				perror("MAP NOT CLOSED IN THE SUPERIOR BORDDER");
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
				flag = 0;
			}
			j++;
		}
		i++;
	}
	if (cord != 1)
	{
		perror("MAP NOT CLOSED IN THE SUPERIOR BORDDER");
		exit(1);
	}
		
}

int main(int argc, char **argv)
{
	t_info	map_data;
	
	if (argc != 2)
	{
    	printf("Usage: %s <map_file.cub>\n", argv[0]);
   		return (1);
	}
	ft_bzero(&map_data, sizeof(t_info));
	map_data = parse_map(get_map_info(argv)); //add .cub check,add argc == 2,  try break it
	check_map(map_data.map);
	
	return (0);
}
