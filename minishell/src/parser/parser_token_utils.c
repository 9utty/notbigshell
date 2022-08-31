/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_token_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gulee <gulee@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 19:38:08 by gulee             #+#    #+#             */
/*   Updated: 2022/08/30 00:49:19 by gulee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_token	*last_get(t_token *token)
{
	while (token)
	{
		if (!token->next)
			break ;
		token = token->next;
	}
	return (token);
}

void	token_add(t_token_table *token_table, t_token *new_token)
{
	t_token	*tmp;

	if (!token_table || !new_token)
		return ;
	if (!token_table->head && token_table->token_count == 0)
		token_table->head = new_token;
	else
	{
		tmp = last_get(token_table->head);
		tmp->next = new_token;
	}
	token_table->token_count += 1;
}

t_token	*token_get(t_token_table *list, int end)
{
	t_token	*token;
	int		index;

	index = 0;
	if (!list || end >= list->token_count)
		return (NULL);
	token = list->head;
	while (index < end)
	{
		token = token->next;
		++index;
	}
	return (token);
}
