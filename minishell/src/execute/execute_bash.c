/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_bash.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gulee <gulee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 02:24:51 by gulee             #+#    #+#             */
/*   Updated: 2022/08/31 17:41:05 by gulee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	double_array_free(char **str)
{
	int	index;

	index = -1;
	while (str[++index])
	{
		free(str[index]);
		str[index] = NULL;
	}
	free(str);
	str = NULL;
}

static char	*cmd_path_get(char *cmd, int fd, int index)
{
	char	*path;
	char	**tmp_path;
	char	*tmp;

	tmp_path = ft_split(env_get("PATH"), ':');
	path = NULL;
	while (tmp_path[index])
	{
		tmp = ft_strjoin(tmp_path[index], "/");
		path = ft_strjoin(tmp, cmd);
		fd = open(path, O_RDONLY, 0644);
		free(tmp);
		if (fd > 0)
		{
			close(fd);
			break ;
		}
		free(path);
		path = NULL;
		++index;
	}
	double_array_free(tmp_path);
	return (path);
}

static void	path_get(t_node *node, char *path)
{
	char	*tmp;

	tmp = node->data;
	if (!ft_memcmp("./", tmp, 2) || !ft_memcmp("/", tmp, 1))
		path = ft_strdup(tmp);
	else
		path = cmd_path_get(tmp, 0, 0);
}

static void	min_execve(t_node *node, char **env)
{
	char	*path;
	char	**option;

	path = NULL;
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	option = get_option(node);
	path_get(node, path);
	echoctl_on();
	if (execve(path, option, env) < 0)
	{
		ft_putstr_fd("minishell: ", STDERR_E);
		ft_putstr_fd(node->data, STDERR_E);
		ft_putstr_fd(": ", STDERR_E);
		ft_putendl_fd(strerror(errno), STDERR_E);
		exit(127);
	}
}

void	not_minishell(t_node *node, int state)
{
	char	*path;
	pid_t	pid;
	char	**env;

	path = NULL;
	path_get(node, path);
	if (!path)
	{
		ft_putstr_fd("minishell: ", STDERR_E);
		ft_putstr_fd(node->data, STDERR_E);
		ft_putendl_fd(": command not found", STDERR_E);
		table_get()->exit_num = 127;
		return ;
	}
	free(path);
	signal(SIGINT, SIG_IGN);
	env = list_convert(table_get()->env);
	pid = fork();
	if (pid < 0)
		error_print("Not minishell fork() error in Execute");
	else if (pid == 0)
		min_execve(node, env);
	waitpid(pid, &(state), 0);
	exec_sig(state);
	double_array_free(env);
}
