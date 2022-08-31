/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_action.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gulee <gulee@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 00:28:00 by gulee             #+#    #+#             */
/*   Updated: 2022/08/30 00:49:43 by gulee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	sig_action(int sig_num)
{
	if (sig_num == SIGINT)
	{
		table_get()->exit_num = 1;
		if (table_get()->is_hdoc == TRUE_E)
		{
			ioctl(STDIN_FILENO, TIOCSTI, "\n");
			rl_replace_line("", 0);
			rl_on_new_line();
		}
		else if (table_get()->is_run == FALSE_E)
		{
			printf("\n");
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
		else
		{
			printf("\n");
			rl_on_new_line();
			rl_replace_line("", 0);
		}
		table_get()->is_hdoc = FALSE_E;
	}
}
