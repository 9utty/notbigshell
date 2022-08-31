/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gulee <gulee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 18:23:57 by gulee             #+#    #+#             */
/*   Updated: 2022/08/31 21:54:10 by gulee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_env_state(char *env)
{
	char	*buf;

	if (!ft_strcmp(env, "?"))
		buf = ft_itoa(table_get()->exit_num);
	else
		buf = ft_strdup(env_get(env));
	free(env);
	env = NULL;
	return (buf);
}

void	env_join(char **new, char *env, int *start, int *end)
{
	char	*org;

	org = *new;
	*new = ft_strjoin(*new, env);
	free(env);
	env = NULL;
	free(org);
	org = NULL;
	*start = *end;
	*end -= 1;
}

void	update_shlvl(void)
{
	t_node	cmd_node;
	t_node	new_node;
	char	*new_shlvl;
	int		org_exitcode;

	ft_memset(&cmd_node, 0, sizeof(t_node));
	ft_memset(&new_node, 0, sizeof(t_node));
	cmd_node.data = "export";
	cmd_node.type = TOKEN_E;
	new_shlvl = ft_itoa(ft_atoi(getenv("SHLVL")) + 1);
	new_node.data = ft_strjoin("SHLVL=", new_shlvl);
	new_node.type = TOKEN_E;
	cmd_node.left = &new_node;
	org_exitcode = table_get()->exit_num;
	// ft_export(&cmd_node);
	table_get()->exit_num = org_exitcode;
	free(new_shlvl);
	free(new_node.data);
}
