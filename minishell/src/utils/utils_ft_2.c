/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_ft_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gulee <gulee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 22:49:19 by gulee             #+#    #+#             */
/*   Updated: 2022/08/31 21:14:53 by gulee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static size_t	ft_num_lenth(int nb)
{
	size_t	lenth;

	lenth = 0;
	if (nb <= 0)
		lenth++;
	while (nb)
	{
		lenth++;
		nb = (nb / 10);
	}
	return (lenth);
}

char	*ft_itoa(int n)
{
	long long	tmp;
	size_t		lenth;
	char		*str;

	lenth = ft_num_lenth(n);
	tmp = n;
	str = NULL;
	str = malloc(sizeof(char) * lenth + 1);
	if (str == NULL)
		return (NULL);
	if (tmp < 0)
	{
		str[0] = '-';
		tmp = tmp * -1;
	}
	if (tmp == 0)
		str[0] = '0';
	str[lenth--] = '\0';
	while (tmp)
	{
		str[lenth] = (tmp % 10) + '0';
		tmp = tmp / 10;
		lenth--;
	}
	return (str);
}

void	*ft_memset(void *ptr, int value, size_t num)
{
	unsigned char	*arr;
	size_t			count;

	arr = (unsigned char *)ptr;
	count = 0;
	while (count < num)
	{
		arr[count] = value;
		count++;
	}
	ptr = arr;
	return (ptr);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	len;

	len = ft_strlen(s1);
	if (len < ft_strlen(s2))
		len = ft_strlen(s2);
	return (ft_memcmp(s1, s2, len));
}

int	ft_memcmp(const void *ptr1, const void *ptr2, size_t num)
{
	unsigned char	*str1;
	unsigned char	*str2;
	size_t			count;
	size_t			index;

	str1 = (unsigned char *)ptr1;
	str2 = (unsigned char *)ptr2;
	count = num;
	index = 0;
	while (count)
	{
		if (str1[index] != str2[index])
			return (str1[index] - str2[index]);
		index++;
		count--;
	}
	return (0);
}
