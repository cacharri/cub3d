/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabel-co <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 11:19:05 by dabel-co          #+#    #+#             */
/*   Updated: 2023/09/27 18:26:18 by dabel-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_finishing(char *aux, char **line, int x, int i)
{
	char	split[BUFFER_SIZE + 1];

	while (aux[i] != '\n')
	{
		split[i] = aux[i];
		i++;
	}
	split[i] = '\0';
	*line = ft_strjoin(*line, split);
	i++;
	while (aux[i] != '\0')
	{
		aux[x] = aux[i];
		x++;
		i++;
	}
	aux[x] = '\0';
	return (1);
}

int	ft_analize(char *aux)
{
	int	i;

	i = 0;
	while (i < BUFFER_SIZE)
	{
		if (aux[i] == '\n')
			return (1);
		if (aux[i] == '\0')
			return (0);
		i++;
	}
	return (0);
}
