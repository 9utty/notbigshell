/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gulee <gulee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 01:08:23 by gulee             #+#    #+#             */
/*   Updated: 2022/08/31 21:20:15 by gulee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static	t_env	*env_last(t_env	*env)
{
	t_env	*tmp;

	if (!env)
		return (NULL);
	tmp = env;
	while (tmp->next)
	{
		if (!tmp->next)
			break ;
		tmp = tmp->next;
	}
	return (tmp);
}

void	set_env(char **env)
{
	t_table	*table;
	int		index;
	t_env	*tmp;
	t_env	*last;

	table = table_get();
	table->env = init_env(env[0]);
	index = 0;
	while (env[index])
	{
		tmp = init_env(env[index]);
		last = env_last(table->env);
		last->next = tmp;
		++index;
	}
}

char	*env_get(char *key)
{
	t_env	*cur;
	t_table	*table;

	table = table_get();
	cur = table->env;
	while (cur)
	{
		if (!ft_strcmp(cur->key, key))
			return (cur->value);
		cur = cur->next;
	}
	return ("");
}
