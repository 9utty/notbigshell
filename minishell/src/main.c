/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gulee <gulee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 23:29:01 by gulee             #+#    #+#             */
/*   Updated: 2022/08/31 20:35:35 by gulee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	ctrl_d(void)
{
	ft_putendl_fd("exit", STDOUT_E);
	set_org_term();
	exit(table_get()->exit_num);
}

int	main(int argc, char **argv, char **env)
{
	char	*line;

	init_start(env, argc, argv);
	while (1)
	{
		echoctl_off();
		update_shlvl();
		line = readline("\033[32mminishell$ ");
		if (line)
		{
			if (line[0] == '\0' || parser(line) == FALSE_E)
				continue ;
			replace(table_get()->tree->root);
			execute(table_get()->tree->root);
			ft_remove();
			free(line);
			line = NULL;
			set_org_term();
		}
		else
			ctrl_d();
	}
	return (0);
}
