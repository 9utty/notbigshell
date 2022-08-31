/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gulee <gulee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 18:34:18 by gulee             #+#    #+#             */
/*   Updated: 2022/08/31 20:51:06 by gulee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_bool	check_quote(char *str)
{
	int	index;

	index = 0;
	while (str[index])
	{
		if (str[index] == '\'')
		{
			if (ft_strchr(&str[index + 1], '\''))
				str = ft_strchr(&str[index + 1], '\'');
			else
				return (FALSE_E);
		}
		else if (str[index] == '\"')
		{
			if (ft_strchr(&str[index + 1], '\"'))
				str = ft_strchr(&str[index], '\"');
			else
				return (FALSE_E);
		}
		++index;
	}
	return (TRUE_E);
}

static t_bool	check_syntax(t_node	*node)
{
	if (!node)
		return (TRUE_E);
	if (node->type == PIPE_E)
	{
		if (!node->left || !node->right)
			return (FALSE_E);
		else if (node->left->type == REDIR_E && \
			ft_strlen(node->left->data) == 1 && node->left->data[0] == '>')
			return (TRUE_E);
	}
	else if (node->type == REDIR_E || node->type == HDOC_E)
	{
		if (!node->right)
			return (FALSE_E);
	}
	return (check_syntax(node->left) && check_syntax(node->right));
}

t_bool	parser(char *line)
{
	int	index;

	index = 0;
	add_history(line);
	if (check_quote(line) == FALSE_E)
	{
		error_print("Check-quote error");
		return (FALSE_E);
	}
	cmd_tokenize(&(table_get()->token_table), line);
	pipeline(&index);
	if (check_syntax(table_get()->tree->root) == FALSE_E)
	{
		error_print("Check-syntax error");
		return (FALSE_E);
	}
	return (TRUE_E);
}
