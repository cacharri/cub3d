/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialvarez <ialvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 13:36:15 by ialvarez          #+#    #+#             */
/*   Updated: 2023/10/26 17:54:27 by ialvarez         ###   ########.fr       */
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
		printf("Error %s extension\n", ext);
		free(aux);
		return (1);
	}
	free(aux);
	return (0);
}

int	main(int argc, char **argv)
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
	map_data = parse_map(get_map_info(argv, 0));
	check_map(map_data.map, 0, 0);
	init_cub(&init, &map_data);
	return (0);
}
