/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialvarez <ialvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 13:36:15 by ialvarez          #+#    #+#             */
/*   Updated: 2023/09/29 21:41:43 by ialvarez         ###   ########.fr       */
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

		
	return (0);
}
