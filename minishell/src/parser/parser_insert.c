/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_insert.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gulee <gulee@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 20:38:45 by gulee             #+#    #+#             */
/*   Updated: 2022/08/30 00:48:56 by gulee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	in_pipe_hdoc(t_tree *tree, t_node *node)
{
	t_node	*curr;
	t_node	*tmp;

	curr = tree->root;
	tmp = curr;
	while (curr && curr->type == HDOC_E)
	{
		tmp = curr;
		curr = curr->left;
	}
	if (!tmp || tmp == curr)
		tree->root = node;
	else
		tmp->left = node;
	node->left = curr;
}

void	in_redir(t_tree *tree, t_node *node)
{
	t_node	*curr;
	t_node	*tmp;

	curr = tree->root;
	tmp = curr;
	while (curr)
	{
		if (curr->type == TOKEN_E || curr->type == SQUOTE_E \
			|| curr->type == DQUOTE_E)
			break ;
		tmp = curr;
		if (curr->type == PIPE_E)
			curr = curr->right;
		else
			curr = curr->left;
	}
	if (!tmp || tmp == curr)
		tree->root = node;
	else if (tmp->type == PIPE_E)
		tmp->right = node;
	else
		tmp->left = node;
	node->left = curr;
}

void	in_hdoc_redir(void)
{
	t_token	*new_token;
	t_node	*new_node;
	char	*num;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		null_error("Token allocation failure error in insert heredoc");
	new_token->type = REDIR_E;
	new_token->data = ft_strdup("<");
	new_token->next = NULL;
	new_node = init_node(new_token);
	in_redir(table_get()->tree, new_node);
	new_token->type = TOKEN_E;
	free(new_token->data);
	num = ft_itoa(table_get()->hdoc_count++);
	new_token->data = ft_strjoin(".heredoc_", num);
	free(num);
	num = NULL;
	in_filename(table_get()->tree, init_node(new_token));
	free(new_token->data);
	new_token->data = NULL;
	free(new_token);
	new_token = NULL;
}

void	in_path(t_tree *tree, t_node *node)
{
	t_node	*curr;
	t_node	*tmp;

	curr = tree->root;
	tmp = curr;
	while (curr)
	{
		tmp = curr;
		if (curr->type == PIPE_E)
			curr = curr->right;
		else
			curr = curr->left;
	}
	if (!tmp)
		tree->root = node;
	else if (tmp->type == PIPE_E)
		tmp->right = node;
	else
		tmp->left = node;
}

void	in_filename(t_tree *tree, t_node *node)
{
	t_node	*curr;
	t_node	*tmp;

	curr = tree->root;
	tmp = curr;
	while (curr)
	{
		tmp = curr;
		if (curr->type == PIPE_E)
			curr = curr->right;
		else if (curr->type == REDIR_E || curr->type == HDOC_E)
		{
			if (curr->right)
				curr = curr->left;
			else
				curr = curr->right;
		}
		else
			curr = curr->left;
	}
	if (tmp->type == PIPE_E || !tmp->right)
		tmp->right = node;
	else
		tmp->left = node;
}
