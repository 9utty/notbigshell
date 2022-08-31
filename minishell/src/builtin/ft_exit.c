/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gulee <gulee@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 19:36:27 by jinkim2           #+#    #+#             */
/*   Updated: 2022/08/30 16:05:16 by gulee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_ac(t_node *head);
int	digit_check(char *str);
int	get_exit_status(int ac, char *str);
int	ft_exit(t_node *head);

int	get_ac(t_node *head)
{
	int	i;

	i = 0;
	if (!head)
		return (-1);
	while (head)
	{
		i++;
		head = head->right;
	}
	return (i);
}

int	digit_check(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] > '9' || '0' > str[i])
			return (FALSE_E);
		i++;
	}
	return (TRUE_E);
}

int	get_exit_status(int ac, char *str)
{
	printf ("exit\n");
	if (ac == 1)
		return (0);
	else if (!digit_check(str))
	{
		printf("minishell: exit: %s: numeric argument reqiured\n", str);
		return (255);
	}
	else if (ac > 2)
	{
		printf("minishell exit: too many arguments\n");
		return (1);
	}
	else if (ac == -1)
	{
		printf ("error\n");
		return (1);
	}
	else
		return ((unsigned char)ft_atoi(str) % 256);
}

int	ft_exit(t_node *head)
{
	t_table	*table;
	int		ac;

	table = table_get();
	ac = get_ac(head);
	table->exit_num = get_exit_status(ac, head->data);
	exit (table->exit_num);
}
