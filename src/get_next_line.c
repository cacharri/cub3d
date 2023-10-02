/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialvarez <ialvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 11:18:50 by dabel-co          #+#    #+#             */
/*   Updated: 2023/10/02 18:32:05 by ialvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	get_next_line(int fd, char **line)
{
	static char	aux[BUFFER_SIZE + 1];
	int			i;

	if (fd == -1 || BUFFER_SIZE < 1 || read(fd, aux, 0))
		return (-1);
	*line = malloc(1);
	*line[0] = '\0';
	aux[BUFFER_SIZE] = '\0';
	i = BUFFER_SIZE;
	while (1)
	{
		if (ft_analize(aux) == 1)
			return (ft_finishing(aux, line, 0, 0));
		if (i > 0)
			*line = ft_strjoin(*line, aux);
		if (i < BUFFER_SIZE)
			i = read(fd, aux, i);
		else
			i = read(fd, aux, BUFFER_SIZE);
		aux[i] = '\0';
		if (i == 0)
			break ;
	}
	return (0);
}
