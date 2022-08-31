/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gulee <gulee@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 15:55:10 by jinkim2           #+#    #+#             */
/*   Updated: 2022/08/30 16:05:12 by gulee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_env(t_node *head);

int	ft_env(t_node *head)
{
	t_env	*env;

	(void)head;
	env = table_get()->env;
	while (env)
	{
		if (env->value)
			printf ("%s=%s\n", env->key, env->value);
		env = env->next;
	}
	return (0);
}
