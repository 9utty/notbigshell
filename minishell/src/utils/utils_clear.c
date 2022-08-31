/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_clear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gulee <gulee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 17:15:50 by gulee             #+#    #+#             */
/*   Updated: 2022/08/31 17:19:32 by gulee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	clear_token_table(t_token_table *table)
{
	t_token	*remove;
	t_token	*tmp;

	remove = table->head;
	tmp = NULL;
	while (tmp)
	{
		tmp = remove->next;
		free(remove->data);
		remove->data = NULL;
		free(remove);
		remove = NULL;
		remove = tmp;
	}
	ft_memset(table, 0, sizeof(t_token_table));
}

static void	node_remove(t_node *node)
{
	if (!node)
		return ;
	node_remove(node->left);
	node_remove(node->right);
	free(node->data);
	node->data = NULL;
	free(node);
	node = NULL;
}

static void	clear_tree(t_tree *tree)
{
	if (!tree)
		return ;
	node_remove(tree->root);
	ft_memset(tree, 0, sizeof(t_tree));
}

static void	clear_hdoc_list(t_hdoc *hdoc)
{
	t_hdoc	*tmp;
	t_hdoc	*remove;

	if (!hdoc)
		return ;
	remove = hdoc;
	while (remove)
	{
		tmp = remove->next;
		free(remove->hdoc_name);
		remove->hdoc_name = NULL;
		free(remove->eof);
		remove->eof = NULL;
		free(remove);
		remove = tmp;
	}
	ft_memset(hdoc, 0, sizeof(t_hdoc));
}

void	ft_remove(void)
{
	t_table	*table;

	table = table_get();
	clear_token_table(table->token_table);
	clear_tree(table->tree);
	table->hdoc_count = 0;
	clear_hdoc_list(table->hdoc_list);
	ft_memset(table->file, 0, sizeof(t_file));
	table->hdoc_index = 0;
	table->is_hdoc = 0;
	table->has_pipe = FALSE_E;
	table->is_run = FALSE_E;
}
