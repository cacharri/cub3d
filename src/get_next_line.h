/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialvarez <ialvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 11:19:34 by dabel-co          #+#    #+#             */
/*   Updated: 2023/09/28 18:42:52 by ialvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define ERROR "Error\n"
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include "../libft/libft.h"


int		get_next_line(int fd, char **line);
int		ft_finishing(char *aux, char **line, int x, int i);
int		ft_analize(char *aux);
#endif
