/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialvarez <ialvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 13:36:15 by ialvarez          #+#    #+#             */
/*   Updated: 2024/01/17 20:24:55 by ialvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_info(t_info *info)
{
	if (info->n)
		free(info->n);
	if (info->s)
		free(info->s);
	if (info->e)
		free(info->e);
	if (info->w)
		free(info->w);
	if (info->map)
		free(info->map);
}

int	check_extension(char *argv, char *ext)
{
	int		len;
	char	*aux;

	len = ft_strlen(argv);
	aux = ft_substr(argv, len - 4, len);
	if (ft_strcmp(aux, ext))
	{
		free(aux);
		return (1);
	}
	free(aux);
	return (0);
}

static void	errors(t_info *data, int err)
{
	if (err == 2 || err == 3)
		printf("Error\n MAP NOT VALID\n");
	else if (err == 6)
		printf("Error\n .xpm extension\n");
	else if (err == 7)
		printf("Error\n Files are corrupt\n");
	else if (err == 1)
		printf("Error\n Wrong coordinates\n");
	else if (err == 4)
		printf("Error\n Map is not closed\n");
	else if (err == 5)
		printf("Error\n Characters of the map aren´t valid\n");
	free_info(data);
}

int	main(int argc, char **argv)
{
	t_info	map_data;
	t_game	init;
	int		err;

	if (argc != 2 || check_extension(argv[1], ".cub") == 1)
	{
		printf("Usage: %s <map_file.cub>\n", argv[0]);
		return (1);
	}
	ft_bzero(&map_data, sizeof(t_info));
	ft_bzero(&init, sizeof(t_game));
	map_data = parse_map(get_map_info(argv, 0));
	if (map_data.err == 2 || map_data.err == 6 || map_data.err == 7)
	{
		errors(&map_data, map_data.err);
		exit (1);
	}
	err = check_map(map_data.map, 0, 0);
	if (err != 0)
	{
		errors(&map_data, err);
		exit (1);
	}
	init_cub(&init, &map_data);
	return (0);
}
