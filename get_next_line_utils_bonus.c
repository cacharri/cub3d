/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialvarez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 19:03:43 by ialvarez          #+#    #+#             */
/*   Updated: 2021/05/06 19:05:13 by ialvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*a;
	const unsigned char	*b;

	a = dst;
	b = src;
	if (!src && !dst)
		return (NULL);
	while (n > 0)
	{
		*a++ = *b++;
		n--;
	}
	return (dst);
}

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		 i++;
	}
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{	
	char	*dst;

	if (!s1 || !s2)
		return (NULL);
	dst = malloc(sizeof (char) * (ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (dst)
	{
		ft_memcpy(dst, s1, ft_strlen(s1));
		ft_memcpy(dst + ft_strlen(s1), s2, ft_strlen(s2) + 1);
	}
	return (dst);
}

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

char	*ft_strchr(const char *s, int c)
{
	int		a;
	int		len;
	char	x;

	x = c;
	a = 0;
	len = ft_strlen(s);
	while (a < len + 1)
	{
		if (s[a] == x)
			return ((char *)s + a);
		a++;
	}
	return (NULL);
}
