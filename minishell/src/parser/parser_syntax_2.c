/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_syntax_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gulee <gulee@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 20:42:07 by gulee             #+#    #+#             */
/*   Updated: 2022/08/30 00:49:15 by gulee            ###   ########.fr       */
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
			word
<filename> =
			word
*/

void	arg(int *index)
{
	t_token	*token;
	t_node	*node;
	t_table	*table;

	table = table_get();
	token = token_get(table->token_table, *index);
	if (!token)
		return ;
	if (token->type == REDIR_E || token->type == PIPE_E \
		|| token->type == HDOC_E)
		return ;
	node = init_node(token);
	in_path(table->tree, node);
	*index += 1;
	if (token->next)
		arg(index);
}

void	path(int *index)
{
	t_token	*token;
	t_node	*node;
	t_table	*table;

	table = table_get();
	token = token_get(table->token_table, *index);
	if (!token)
		return ;
	node = init_node(token);
	in_path(table->tree, node);
	*index += 1;
}

void	filename(int *index)
{
	t_token	*token;
	t_node	*node;
	t_table	*table;

	table = table_get();
	token = token_get(table->token_table, *index);
	if (!token || token->type == PIPE_E)
		return ;
	node = init_node(token);
	in_filename(table->tree, node);
	*index += 1;
}
