/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialvarez <ialvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 13:36:15 by ialvarez          #+#    #+#             */
/*   Updated: 2023/09/28 13:22:27 by dabel-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"
int main(int argc, char **argv)
{
	t_info	map_data;
	map_data = parse_map(get_map_info(argv)); //add .cub check,add argc == 2,  try break it
	
		
	return (0);
}
