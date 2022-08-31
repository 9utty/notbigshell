/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gulee <gulee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 00:17:36 by gulee             #+#    #+#             */
/*   Updated: 2022/08/31 20:05:20 by gulee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env	*init_env(char *str)
{
	t_env	*new;
	char	*value;

	new = malloc(sizeof(t_env));
	if (!new)
		null_error("env allocation failure error in init env");
	value = ft_strchr(str, '=');
	new->key = ft_substr(str, 0, ft_strlen(str) - ft_strlen(value));
	new->value = ft_substr(value, 1, ft_strlen(value) - 1);
	return (new);
}

t_token_table	*init_token_table(void)
{
	t_token_table	*table;

	table = malloc(sizeof(t_token_table));
	if (!table)
		null_error("Token allocation failure error in init token-table");
	ft_memset(table, 0, sizeof(t_token_table));
	return (table);
}

t_file	*init_file(void)
{
	t_file	*file;

	file = malloc(sizeof(t_file));
	if (!file)
		null_error("File allocation failure error in init file");
	ft_memset(file, 0, sizeof(t_file));
	return (file);
}

void	init_start(char **env, int argc, char **argv)
{
	t_table	*table;

	(void)argc;
	(void)argv;
	print_main_cover();
	table = table_get();
	signal(SIGINT, sig_action);
	signal(SIGQUIT, SIG_IGN);
	table->token_table = init_token_table();
	table->tree = init_tree();
	table->file = init_file();
	set_env(env);
	get_org_term();
}
