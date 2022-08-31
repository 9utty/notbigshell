/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_ft_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinkim2 <jinkim2@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 01:06:08 by gulee             #+#    #+#             */
/*   Updated: 2022/08/30 18:37:04 by jinkim2          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

size_t	ft_strlen(const char *str)
{
	size_t	count;

	count = 0;
	while (str[count])
		count++;
	return (count);
}

char	*ft_strchr(const char *str, int c)
{
	size_t	index;

	index = 0;
	while (str[index])
	{
		if (str[index] == (const char)c)
			return ((char *)str + index);
		index++;
	}
	if (str[index] == (const char)c)
		return ((char *)str + index);
	return (0);
}

char	*ft_strdup(char *str)
{
	char	*dest;
	size_t	size;
	size_t	index;

	index = 0;
	size = ft_strlen(str);
	dest = NULL;
	dest = malloc((sizeof(char) * size) + 1);
	if (!dest)
		return (NULL);
	while (index < size)
	{
		dest[index] = str[index];
		index++;
	}
	dest[index] = '\0';
	return (dest);
}

char	*ft_substr(char *s, int start, int len)
{
	char	*ptr;
	int		index;

	if (!s)
		return (NULL);
	if (*s == '\0' || (size_t)start > ft_strlen(s))
		return (ft_strdup(""));
	if (ft_strlen(s) <= (size_t)len)
		len = ft_strlen(s) - (size_t)start;
	ptr = malloc(sizeof(char) * len + 1);
	if (!ptr)
		return (NULL);
	index = 0;
	while (s[start] && index < len)
		ptr[index++] = s[start++];
	ptr[index] = '\0';
	return (ptr);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*ptr;
	size_t	i;
	size_t	j;

	ptr = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!ptr)
		return (NULL);
	i = 0;
	if (s1)
	{
		while (s1[i])
		{
			ptr[i] = s1[i];
			i++;
		}
	}
	j = 0;
	while (s2[j])
		ptr[i++] = s2[j++];
	ptr[i] = '\0';
	return (ptr);
}
