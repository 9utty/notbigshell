/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_term.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gulee <gulee@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 01:24:38 by gulee             #+#    #+#             */
/*   Updated: 2022/08/30 00:51:07 by gulee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	get_org_term(void)
{
	t_table	*table;

	table = table_get();
	tcgetattr(STDIN_E, &(table->org_term));
}

void	set_org_term(void)
{
	t_table	*table;

	table = table_get();
	tcsetattr(STDIN_E, TCSANOW, &(table->new_term));
}

void	echoctl_off(void)
{
	t_table	*table;

	table = table_get();
	tcgetattr(STDIN_E, &(table->new_term));
	table->new_term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_E, TCSANOW, &(table->new_term));
}

void	echoctl_on(void)
{
	t_table	*table;

	table = table_get();
	tcgetattr(STDIN_E, &(table->new_term));
	table->new_term.c_lflag |= ECHOCTL;
	tcsetattr(STDIN_E, TCSANOW, &(table->new_term));
}
