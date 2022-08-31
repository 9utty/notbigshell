/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinkim2 <jinkim2@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 19:37:38 by jinkim2           #+#    #+#             */
/*   Updated: 2022/08/30 18:33:56 by jinkim2          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	option_check(char **str, int *op_check);
void	print_echo(int op_check, int i, int ac, char **av);
int		ft_echo(t_node *head);

void	option_check(char **str, int *op_check)
{
	int	i;
	int	j;

	i = 1;
	while (str[i])
	{
		j = 0;
		if (str[i][j] == '-')
		{
			j++;
			while (str[i][j])
			{
				if (str[i][j] != 'n')
					break ;
				j++;
			}
		}
		if (j == (int)ft_strlen(str[i]) && str[i][j - 1] == 'n')
			*op_check += 1;
		else
			return ;
		i++;
	}
}

void	print_echo(int op_check, int i, int ac, char **av)
{
	while (op_check + 1 < ac - 1)
	{
		write (1, av[op_check + i], ft_strlen(av[op_check + i]));
		write(1, " ", 1);
		i++;
	}
	if (op_check)
		write (1, av[op_check + i], ft_strlen(av[op_check + i]));
	else
	{
		write (1, av[op_check + i], ft_strlen(av[op_check + i]));
		write (1, "\n", 1);
	}
}

int	ft_echo(t_node *head)
{
	int		i;
	// char	*str;
	char	**av;
	int		ac;
	int		op_check;

	i = 1;
	// str = echo_replace(head->data);
	av = get_av(head->data, &ac);
	op_check = FALSE_E;
	if (ac == 1)
		write (STDOUT_FILENO, "\n", 1);
	if (av[1][0] == '-')
		option_check(av, &op_check);
	print_echo(op_check, i, ac, av);
	return (0);
}
