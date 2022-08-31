/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinkim2 <jinkim2@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 20:48:04 by jinkim2           #+#    #+#             */
/*   Updated: 2022/08/30 18:35:53 by jinkim2          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_key(char *str);
char	*get_env(char *str);
char	**get_av(char *str, int *ac);
char	*ft_strndup(char *str, int len);

char	*get_key(char *str) // 못 찾으면 0
{
	char	*tmp;
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			break ;
		i++;
	}
	if ((size_t)i == ft_strlen(str))
		return (0);
	tmp = ft_strndup(str, i);
	if (!tmp)
		exit (12);
	return (tmp);
}

char	*get_env(char *str)
{
	t_env	*env;

	if (!str)
		return (0);
	env = (table_get())->env;
	while (env)
	{
		if (ft_strcmp(env->key, str))
			return (env->value);
		env = env->next;
	}
	return (0);
}

char	**get_av(char *str, int *ac)
{
	int		i;
	char	**tmp;

	if (!str)
		return (0);
	i = 0;
	tmp = ft_split(str, ' ');
	if (!tmp)
		exit (12);
	while (tmp[i])
		i++;
	*ac = i;
	return (tmp);
}

// int	ft_strcmp(char *str1, char *str2) // 같으면 0
// {
// 	int	i;

// 	i = 0;
// 	while (str1[i])
// 	{
// 		if (str1[i] != str2[i])
// 			return ((unsigned char)str1[i] - (unsigned char)str2[i]);
// 		i++;
// 	}
// 	if (str2[i])
// 		return ((unsigned char)str1[i] - (unsigned char)str2[i]);
// 	return (0);
// }

char	*ft_strndup(char *str, int len)
{
	char	*new;
	int		i;

	i = 0;
	new = malloc(sizeof(char) * (len + 1));
	if (!new)
		exit (12);
	while (i < len)
	{
		new[i] = str[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}
