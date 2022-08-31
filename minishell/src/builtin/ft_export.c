/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinkim2 <jinkim2@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 15:58:17 by jinkim2           #+#    #+#             */
/*   Updated: 2022/08/30 18:39:56 by jinkim2          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

/*
	key = value 형식 말고 key 만 들어오는 경우에 value = 0 해뒀어여
	접근하면 문제 생길 것 같은데 env나 export 빼고는 접근하는 경우 없어서 ㄱㅊ을듯??
	env는 value 없으면 출력 안 해서 조건을 value 있을 때만 출력하게 걸어뒀어염
*/

#include "../../includes/minishell.h"

int		ft_isalpha(int c);
void	print_export(t_env *env);
int		valid_argu(char *str);
t_env	*check_exist(char *key, t_env *env);

int	ft_isalpha(int c)
{
	if ((c >= 65 && 90 >= c) || (c >= 97 && 122 >= c) || c == '=' || c == '_')
		return (1);
	return (0);
}

void	print_export(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, "_"))
			;
		else if (!tmp->value)
			printf("declare -x %s\n", tmp->key);
		else
			printf("declare -x %s=\"%s\"\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
}

int	valid_argu(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '_')
	{
		i = 1;
		while (str[i])
		{
			if (!ft_isalpha(str[i]) && !ft_isdigit(str[i]))
				return (0);
			i++;
		}
	}
	else
	{
		while (str[i])
		{
			if (!ft_isalpha(str[i]))
				return (0);
			i++;
		}
	}
	return (1);
}

t_env	*check_exist(char *key, t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!ft_strcmp(key, tmp->key))
			return (tmp);
		tmp = tmp->next;
	}
	return (0);
}
