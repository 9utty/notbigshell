/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gulee <gulee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 01:57:52 by gulee             #+#    #+#             */
/*   Updated: 2022/08/31 17:22:10 by gulee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_bool	close_redir(void)
{
	t_table	*table;

	table = table_get();
	if (table->file->open_stdin > 0)
	{
		close(table->file->open_stdin);
		if (dup2(table->file->open_stdin, STDIN_E) < 0)
			return (FALSE_E);
	}
	if (table->file->open_stdout > 0)
	{
		close(table->file->open_stdout);
		if (dup2(table->file->open_stdout, STDOUT_E) < 0)
			return (FALSE_E);
	}
	return (TRUE_E);
}

t_bool	get_redir(void)
{
	t_table	*table;

	table = table_get();
	if (table->file->open_stdin > 0)
	{
		if (dup2(table->file->open_stdin, STDIN_E) < 0)
			return (FALSE_E);
	}
	if (table->file->open_stdout > 0)
	{
		if (dup2(table->file->open_stdout, STDOUT_E) < 0)
			return (FALSE_E);
	}
	return (TRUE_E);
}

static	void	redir_init(int flag)
{
	t_table	*table;

	table = table_get();
	if (flag == FALSE_E && table->file->open_stdout > 0)
	{
		close(table->file->open_stdout);
		table->file->open_stdout = 0;
	}
	if (flag == TRUE_E && table->file->open_stdin < 0)
	{
		close(table->file->open_stdin);
		table->file->open_stdin = 0;
	}
}

void	ex_redir(t_node *node)
{
	t_file	*file;
	t_bool	flag;
	char	*path;

	file = table_get()->file;
	path = node->right->data;
	flag = TRUE_E;
	if (node->data[0] == '>')
		flag = FALSE_E;
	redir_init(flag);
	if (!ft_strcmp(">", node->data))
		file->open_stdout = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (!ft_strcmp(">>", node->data))
		file->open_stdout = open(path, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (!ft_strcmp("<", node->data))
		file->open_stdin = open(path, O_RDONLY, 0644);
	if (file->open_stdout < 0 || file->open_stdin < 0)
	{
		ft_putstr_fd("minishell: ", STDERR_E);
		ft_putstr_fd(path, STDERR_E);
		ft_putstr_fd(": ", STDERR_E);
		ft_putendl_fd(strerror(errno), STDERR_E);
		return ;
	}
	execute(node->left);
}
