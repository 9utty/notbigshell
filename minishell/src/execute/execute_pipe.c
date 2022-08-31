/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gulee <gulee@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 01:46:26 by gulee             #+#    #+#             */
/*   Updated: 2022/08/30 16:12:58 by gulee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static pid_t	input(int *fd, t_node *node)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		error_print("Pipe input fork() error in Execute");
	else if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_E);
		close(fd[1]);
		execute(node);
		exit(0);
	}
	return (pid);
}

static pid_t	output(int *fd, t_node *node)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		error_print("Pipe output fork() error in Execute");
	else if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_E);
		close(fd[1]);
		execute(node);
		exit(0);
	}
	return (pid);
}

void	ex_pipe(t_node *node)
{
	int		pipe_fd[2];
	int		node_left;
	int		node_right;
	t_table	*table;

	table = table_get();
	table->has_pipe = TRUE_E;
	table->is_run = TRUE_E;
	if (pipe(pipe_fd) == -1)
		error_print("Pipe func error in Execute");
	node_left = input(pipe_fd, node->left);
	node_right = output(pipe_fd, node->right);
	waitpid(node_left, &table->exit_num, 0);
	close(pipe_fd[1]);
	waitpid(node_right, &table->exit_num, 0);
	close(pipe_fd[0]);
	if (table->exit_num > 0)
		table->exit_num /= 256;
}
