/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_ft_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinkim2 <jinkim2@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 00:41:16 by gulee             #+#    #+#             */
/*   Updated: 2022/08/30 18:39:14 by jinkim2          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_isspace(char c)
{
	if ((c >= 9 && c <= 13) || c == ' ')
		return (1);
	return (0);
}

t_bool	ft_isdigit(char num)
{
	if (num >= '0' && num <= '9')
		return (TRUE_E);
	return (FALSE_E);
}

int	ft_atoi(const char *str)
{
	size_t	result;
	int		negative;

	result = 0;
	negative = 1;
	while (*str != '\0' && (ft_isspace(*str)))
		str++;
	if (*str != '\0' && (*str == '-' || *str == '+'))
	{
		if (*str == '-')
			negative = -1;
		str++;
	}
	while (*str != '\0' && ft_isdigit(*str))
	{
		result = (result * 10) + (*str - '0');
		str++;
	}
	return (result * negative);
}
