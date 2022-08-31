/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_syntax_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gulee <gulee@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 19:10:38 by gulee             #+#    #+#             */
/*   Updated: 2022/08/30 00:49:11 by gulee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
<pipeline> =
			<cmd>
			<cmd> '|' <pipeline>
<cmd> =
			<simple_cmd>
			<simple_cmd> <redirs>
<simple_cmd> =
			<path>
			<path> <args>
<redirs> =
			<redir>
			<redir> <redirs>
<redir> =
			'<' <filename>
			'>' <filename>
			'>>' <filename>
			'<<' <filename>
<args> =
			word
			word <args>
<path> =
			word`
<filename> =
			word
*/

void	pipeline(int *index)
{
	t_token	*token;
	t_node	*node;
	t_table	*table;

	table = table_get();
	cmd(index);
	token = token_get(table->token_table, *index);
	if (token && token->type == PIPE_E && ++(*index))
	{
		node = init_node(token);
		in_pipe_hdoc(table->tree, node);
		pipeline(index);
	}
	else if (token)
		pipeline(index);
}

void	cmd(int *index)
{
	t_token	*token;
	t_table	*table;

	table = table_get();
	cmd_simple(index);
	token = token_get(table->token_table, *index);
	if (token && (token->type == REDIR_E || token->type == HDOC_E))
		redirs(index);
}

void	cmd_simple(int *index)
{
	t_token	*token;
	t_table	*table;

	table = table_get();
	token = token_get(table->token_table, *index);
	if (!token || token->type == REDIR_E || token->type == PIPE_E \
		|| token->type == HDOC_E)
		return ;
	path(index);
	token = token_get(table->token_table, *index);
	if (token)
		arg(index);
}

void	redirs(int *index)
{
	t_token	*token;
	t_table	*table;

	table = table_get();
	token = token_get(table->token_table, *index);
	if (token && token->type == PIPE_E)
		return ;
	if (token && (token->type == REDIR_E || token->type == HDOC_E))
	{
		redir(index);
		redirs(index);
	}
}

void	redir(int *index)
{
	t_token	*token;
	t_node	*node;
	t_table	*table;

	table = table_get();
	token = token_get(table->token_table, *index);
	if (!token)
		return ;
	node = init_node(token);
	if (token->type == REDIR_E)
		in_redir(table->tree, node);
	++(*index);
	filename(index);
	if (token->type == HDOC_E)
		in_hdoc_redir();
}
