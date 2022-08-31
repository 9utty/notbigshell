/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gulee <gulee@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 19:35:03 by jinkim2           #+#    #+#             */
/*   Updated: 2022/08/30 16:05:24 by gulee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_pwd(t_node *head);

int	ft_pwd(t_node *head)
{
	char	buf[1024];

	(void)head;
	printf("%s\n", getcwd(buf, 1024));
	return (0);
}
