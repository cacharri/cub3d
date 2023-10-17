/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialvarez <ialvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 13:36:15 by ialvarez          #+#    #+#             */
/*   Updated: 2023/10/17 20:38:42 by ialvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_extension(char *argv, char *ext)
{
	int		len;
	char	*aux;

	len = ft_strlen(argv);
	aux = ft_substr(argv, len - 4, len);
	if (ft_strcmp(aux, ext))
	{
		printf("Error %s extension\n", ext);
		free(aux);
		return (1);
	}
	free(aux);
	return (0);
}

int main(int argc, char **argv)
{
	t_info	map_data;
	t_game	init;
	
	if (argc != 2 || check_extension(argv[1], ".cub") == 1)
	{
    	printf("Usage: %s <map_file.cub>\n", argv[0]);
   		return (1);
	}
	ft_bzero(&map_data, sizeof(t_info));
	ft_bzero(&init, sizeof(t_game));
	map_data = parse_map(get_map_info(argv)); //add .cub check,add argc == 2,  try break it
	check_map(map_data.map, 0, 0, 0);
	
	//init_cub(&init);
	return (0);
}
