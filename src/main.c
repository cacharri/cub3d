/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialvarez <ialvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 13:36:15 by ialvarez          #+#    #+#             */
/*   Updated: 2023/10/16 17:05:01 by ialvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"



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
