/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialvarez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 17:43:52 by ialvarez          #+#    #+#             */
/*   Updated: 2023/09/27 17:24:28 by dabel-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*dst;
	int		i;

	i = ft_strlen(s1);
	dst = malloc(sizeof (char) * (i + 1));
	if (!dst)
		return (NULL);
	ft_memcpy(dst, s1, i);
	dst[i] = '\0';
	return (dst);
}
