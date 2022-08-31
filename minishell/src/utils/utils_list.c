/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gulee <gulee@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 01:05:11 by gulee             #+#    #+#             */
/*   Updated: 2022/08/30 02:48:05 by gulee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	list_len(t_env *env)
{
	int	len;

	len = 0;
	while (env)
	{
		++len;
		env = env->next;
	}
	return (len);
}

char	**list_convert(t_env *env)
{
	t_env	*curr;
	char	**buff;
	char	*tmp;
	int		index;

	index = 0;
	buff = (char **)malloc(sizeof(char *) * (list_len(env) + 1));
	if (!buff)
		error_print("List convert error in Execute");
	curr = env;
	while (curr)
	{
		tmp = ft_strjoin(curr->key, "=");
		buff[index] = ft_strjoin(tmp, curr->value);
		free(tmp);
		++index;
		curr = curr->next;
	}
	buff[index] = NULL;
	return (buff);
}

t_hdoc	*list_tail(t_hdoc *list)
{
	while (list)
	{
		if (list->next == NULL)
			break ;
		list = list->next;
	}
	return (list);
}

void	list_add_back(t_hdoc **list, t_hdoc *new)
{
	t_hdoc	*tail;

	if (!list || !new)
		return ;
	if (!*list)
		*list = new;
	else
	{
		tail = list_tail(*list);
		tail->next = new;
	}
}
