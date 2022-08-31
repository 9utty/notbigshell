/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gulee <gulee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 02:10:03 by gulee             #+#    #+#             */
/*   Updated: 2022/08/31 17:22:02 by gulee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ex_command(t_node *node)
{
	get_redir();
	if (!ft_strcmp(node->data, "echo"))
		ft_echo(node);
	else if (!ft_strcmp(node->data, "cd"))
		ft_cd(node);
	else if (!ft_strcmp(node->data, "pwd"))
		ft_pwd(node);
	else if (!ft_strcmp(node->data, "export"))
		ft_export(node);
	else if (!ft_strcmp(node->data, "unset"))
		ft_unset(node);
	else if (!ft_strcmp(node->data, "env"))
		ft_env(node);
	else if (!ft_strcmp(node->data, "exit"))
		ft_exit(node);
	else
		not_minishell(node, 0);
	close_redir();
}
