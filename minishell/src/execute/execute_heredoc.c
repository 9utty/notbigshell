/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gulee <gulee@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 01:02:30 by gulee             #+#    #+#             */
/*   Updated: 2022/08/30 16:12:57 by gulee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	hdoc_start(t_hdoc *arg)
{
	t_hdoc	*hdoc;
	char	*buff;
	t_table	*table;

	table = table_get();
	hdoc = arg;
	while (table->is_hdoc == TRUE_E)
	{
		buff = readline("> ");
		if (!buff)
		{
			ft_putstr_fd("\033[1A", STDOUT_E);
			ft_putstr_fd("\033[2C", STDOUT_E);
			break ;
		}
		if (!ft_strcmp(buff, hdoc->eof))
		{
			free(buff);
			break ;
		}
		ft_putendl_fd(buff, hdoc->fd);
		free(buff);
	}
}

t_hdoc	*hdoc_init(t_node *node)
{
	t_hdoc	*new;
	int		flag;

	new = malloc(sizeof(t_hdoc));
	if (new == NULL)
		error_print("Heredoc init in Execute error");
	ft_memset(&new, 0, sizeof(t_hdoc));
	new->hdoc_name = ft_strjoin(".heredoc_", \
				ft_itoa(table_get()->hdoc_count++));
	flag = O_CREAT | O_TRUNC | O_RDWR;
	new->fd = open(new->hdoc_name, flag, 0644);
	if (new->fd < 0)
	{
		free(new->hdoc_name);
		ft_memset(&new, 0, sizeof(t_hdoc));
		free(new);
		return (0);
	}
	new->eof = ft_strdup(node->data);
	return (new);
}

void	ex_heredoc(t_node *node)
{
	t_node	*tmp;
	t_table	*table;

	table = table_get();
	table->is_hdoc = TRUE_E;
	tmp = node->right;
	list_add_back(&table->hdoc_list, hdoc_init(tmp));
	hdoc_start(list_tail(table->hdoc_list));
	if (table->is_hdoc == FALSE_E)
		return ;
	execute(node->left);
}
