/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gzafer <gzafer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 15:01:38 by gzafer            #+#    #+#             */
/*   Updated: 2024/12/02 13:40:02 by gzafer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*p;
	char	*k;
	size_t	i;

	i = 0;
	p = (char *)dst;
	k = (char *)src;
	if (!dst || !src)
	{
		return (NULL);
	}
	while (i < n)
	{
		p[i] = k[i];
		i++;
	}
	return (dst);
}

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	cr;

	cr = (char)c;
	if (cr == '\0')
	{
		return ((char *)&s[ft_strlen(s)]);
	}
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == cr)
		{
			return ((char *)&s[i]);
		}
		i++;
	}
	return (NULL);
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	len1;
	size_t	len2;
	char	*result;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	result = malloc(len1 + len2 + 1);
	if (!result)
		return (NULL);
	ft_memcpy(result, s1, len1);
	ft_memcpy(result + len1, s2, len2 + 1);
	return (result);
}
