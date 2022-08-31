/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tokenize.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gulee <gulee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 18:43:17 by gulee             #+#    #+#             */
/*   Updated: 2022/08/31 21:28:42 by gulee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_type	what_is_type(char *str, int len)
{
	char	c;

	c = *str;
	if (c == PIPE_E)
		return (PIPE_E);
	else if (c == LESS_E && len > 1)
		return (HDOC_E);
	else if (c == LESS_E || c == GREAT_E)
		return (REDIR_E);
	else if (c == SQUOTE_E)
		return (SQUOTE_E);
	else if (c == DQUOTE_E)
		return (DQUOTE_E);
	else
		return (TOKEN_E);
}

static void	init_token(t_token_table **list, char *str, int len)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		null_error("Token Allocation failure error in init token");
	ft_memset(new_token, 0, sizeof(t_token));
	new_token->data = str;
	new_token->type = what_is_type(str, len);
	token_add(*list, new_token);
}

void	cmd_tokenize(t_token_table **list, char *str)
{
	char	*tmp;

	while (*str)
	{
		while (is_blank_cc(*str))
			str++;
		tmp = str;
		while (*tmp && !ft_strchr(" |<>", *tmp))
		{
			if (ft_strchr("\'\"", *tmp))
				tmp = ft_strchr(tmp + 1, *tmp);
			if (ft_strchr(" |<>", *(tmp + 1)))
				break ;
			++tmp;
		}
		if (*tmp && *tmp == *(tmp + 1) && ft_strchr("<>", *(tmp + 1)))
			++tmp;
		if (*str)
		{
			init_token(list, ft_substr(str, 0, tmp - str + 1), tmp - str + 1);
			if (!*tmp)
				break ;
			str = tmp + 1;
		}
	}
}
