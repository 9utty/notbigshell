/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gulee <gulee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 02:55:41 by gulee             #+#    #+#             */
/*   Updated: 2022/08/31 20:03:43 by gulee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	option_quantity(t_node *node)
{
	t_node	*curr;
	int		len;

	len = 1;
	curr = node->left;
	while (curr)
	{
		curr = curr->left;
		++len;
	}
	return (len);
}

char	**get_option(t_node *node)
{
	t_node	*curr;
	char	**option;
	int		index;

	index = 0;
	curr = node;
	option = (char **)malloc(sizeof(char *) * option_quantity(node));
	if (option == NULL)
		error_print("Get option allocate error in Execute");
	while (curr)
	{
		option[index] = ft_strdup(curr->data);
		curr = curr->left;
		++index;
	}
	option[index] = NULL;
	return (option);
}

void	exec_sig(int state)
{
	int	sig;

	echoctl_off();
	if (WIFEXITED(state))
		table_get()->exit_num = state / 256;
	else if (WIFSIGNALED(state))
	{
		sig = WTERMSIG(state);
		if (sig == SIGQUIT)
		{
			ft_putendl_fd("Quit: 3", STDIN_E);
			table_get()->exit_num = 131;
		}
		else if (sig == SIGINT)
		{
			if (table_get()->has_pipe == FALSE_E)
				ft_putchar_fd('\n', STDIN_E);
			else
				ft_putstr_fd("\033[12D", STDIN_E);
			table_get()->exit_num = 130;
		}
	}
	signal(SIGINT, sig_action);
	signal(SIGQUIT, SIG_IGN);
}
