/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gulee <gulee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 00:46:46 by gulee             #+#    #+#             */
/*   Updated: 2022/08/31 17:21:50 by gulee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	execute_node_check(t_node *node)
{
	if (!node)
		return ;
	if (node->type == HDOC_E)
		ex_heredoc(node);
	else if (node->type == PIPE_E)
		ex_pipe(node);
	else if (node->type == REDIR_E)
		ex_redir(node);
	else if (node->type == TOKEN_E)
		ex_command(node);
	table_get()->is_hdoc = FALSE_E;
}

void	execute(t_node *node)
{
	t_table	*table;

	if (!node)
		return ;
	table = table_get();
	table->file->origin_stdin = dup(STDIN_E);
	table->file->origin_stdout = dup(STDOUT_E);
	if (table->file->origin_stdin < 0 || table->file->origin_stdout < 0)
		error_print("Execute File stdin or stdout error");
	execute_node_check(node);
}
