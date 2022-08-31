/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinkim2 <jinkim2@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 15:20:51 by jinkim2           #+#    #+#             */
/*   Updated: 2022/08/30 18:34:48 by jinkim2          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	delete_node(char *key, t_env *env);
int		unset_check_exist(char *av, t_env *env);
int		ft_unset(t_node *head);

void	delete_node(char *key, t_env *env)
{
	t_env	*tmp;

	tmp = env;
	if (!ft_strcmp(key, tmp->key))
	{
		tmp->key = 0;
		tmp->value = 0;
		tmp->next = 0;
		free (tmp);
	}
	else
	{
		while (tmp->next)
		{
			if (!ft_strcmp(tmp->next->key, key))
				break ;
			tmp = tmp->next;
		}
		tmp->next->key = 0;
		tmp->next->value = 0;
		tmp->next = tmp->next->next;
		free (tmp->next);
	}
}

int	unset_check_exist(char *av, t_env *env)
{
	if (get_env(av))
		delete_node(av, env);
	return (1);
}

int	ft_unset(t_node *head)
{
	char	**av;
	int		ac;
	int		i;
	t_env	*env;

	env = table_get()->env;
	av = get_av(head->data, &ac);
	i = 1;
	while (i < ac)
	{
		unset_check_exist(av[i], env);
		i++;
	}
	return (0);
}
