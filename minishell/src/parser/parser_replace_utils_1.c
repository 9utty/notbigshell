/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_replace_utils_1.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gulee <gulee@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 23:18:22 by gulee             #+#    #+#             */
/*   Updated: 2022/08/30 00:49:01 by gulee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	join_squote(char *rest, char *data, int *front, int *end)
{
	*front = join_str(rest, data, *front, *end);
	*end = ft_strlen(data) - ft_strlen(ft_strchr(data + *front, SQUOTE_E));
	*front = join_str(rest, data, *front, *end);
}

int	join_str(char *new, char *org, int start, int end)
{
	char	*org_data;
	char	*new_data;

	if (end - start > 0)
	{
		new_data = ft_substr(org, start, end - start);
		org_data = new;
		new = ft_strjoin(new, new_data);
		free(new_data);
		free(org_data);
		new_data = NULL;
		org_data = NULL;
	}
	return (end + 1);
}

void	join_envp(char *new, char *env, int *start, int *end)
{
	char	*org;

	org = new;
	new = ft_strjoin(new, env);
	free(env);
	free(org);
	env = NULL;
	org = NULL;
	*start = *end;
	*end -= 1;
}

void	find_end_position(char *data, int *end, int *flag)
{
	char	c;
	int		tmp;

	tmp = *end;
	c = data[tmp];
	*flag = TRUE_E;
	if ((tmp - 2 >= 0) && (data[tmp - 2]) && (!c || c == '$'))
		*flag = FALSE_E;
	while (c && c != '\'' && c != '\"' && !is_blank_cc(c) \
		&& c != '$' && c != '=')
	{
		if (c == '?')
		{
			++tmp;
			break ;
		}
		++tmp;
		c = data[tmp];
	}
	*end = tmp;
}
