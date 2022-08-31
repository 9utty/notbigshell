/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_replace.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gulee <gulee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 22:44:55 by gulee             #+#    #+#             */
/*   Updated: 2022/08/31 21:50:25 by gulee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*replace_env(char *data, int start, int end, t_bool flag)
{
	int		index;
	char	*env;
	char	*tmp;
	char	*buf;
	char	*str;

	index = 0;
	if (end - start < 1 && flag == FALSE_E)
		return (ft_strdup("$"));
	else if (end - start < 1 && flag == TRUE_E)
		return (ft_strdup(""));
	str = ft_substr(data, start, end - start);
	while (str[index] && !is_blank_cc(str[index]))
		++index;
	env = ft_substr(str, 0, index);
	tmp = get_env_state(env);
	if (!str[index])
		buf = ft_strdup(tmp);
	else
		buf = ft_strjoin(tmp, str + index);
	free(tmp);
	tmp = NULL;
	free(str);
	str = NULL;
	return (buf);
}

static void	replace_home(t_node *data)
{
	char	*home;
	char	*path;
	char	*org;

	home = env_get("HOME");
	if (!home || !home[0])
		home = getenv("HOME");
	if (data && data->data[0] == '~' && \
		(!data->data[1] || (data->data[1] && data->data[1] == '/')))
	{
		org = ft_substr(data->data, 1, ft_strlen(data->data) - 1);
		path = ft_strjoin(home, org);
		free(org);
		org = data->data;
		data->data = path;
		free(org);
		org = NULL;
	}
}

static void	set_value(int *dquote, int *front, int *end)
{
	*dquote = FALSE_E;
	*end = -1;
	*front = 0;
}

static void	replace_token(char *rest, char *org_data)
{
	int	dquote;
	int	front;
	int	end;
	int	flag;

	set_value(&dquote, &front, &end);
	while (org_data[++end])
	{
		if (org_data[end] == SQUOTE_E && dquote == FALSE_E)
			join_squote(rest, org_data, &front, &end);
		else if (org_data[end] == DQUOTE_E)
		{
			dquote = !dquote;
			front = join_str(rest, org_data, front, end);
		}
		else if (org_data[end] == '$')
		{
			front = join_str(rest, org_data, front, end++);
			find_end_position(org_data, &end, &flag);
			env_join(&rest, replace_env(org_data, front, end, flag) \
				, &front, &end);
		}
		else if (!org_data[end + 1])
			join_str(rest, org_data, front, end + 1);
	}
}

void	replace(t_node *node)
{
	char	*org_data;

	if (!node)
		return ;
	replace_home(node);
	if (ft_strcmp(node->data, "$")) // 같으면 0 다르면 반환값있음
	{
		org_data = node->data;
		// node->data = ft_strdup("");
		replace_token(node->data, org_data);
		// free(org_data);
		// org_data = NULL;
	}
	replace(node->left);
	replace(node->right);
}
