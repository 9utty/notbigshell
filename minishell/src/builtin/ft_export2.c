/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gulee <gulee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 20:46:29 by jinkim2           #+#    #+#             */
/*   Updated: 2022/08/31 21:26:38 by gulee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	replace_export(t_env *tmp, char *str);
t_env	*make_new_env(char *key, char *value, char *str);
void	add_new_env(char *key, char *str, t_env *env);
void	check_argu(char **av, t_env *env);
int		ft_export(t_node *head);

void	replace_export(t_env *tmp, char *str)
{
	char	*value;
	int		i;

	i = 0;
	while (str[i] != '=')
		i++;
	value = ft_strdup(ft_strchr(str, '=') + 1);
	if (!value)
		exit (12);
	free (tmp->value);
	tmp->value = value;
}

t_env	*make_new_env(char *key, char *value, char *str)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		exit (12);
	if (value)
	{
		new->key = key;
		new->value = value;
	}
	else
	{
		new->key = ft_strdup(str);
		new->value = 0;
	}
	new->next = 0;
	return (new);
}

void	add_new_env(char *key, char *str, t_env *env)
{
	char	*value;
	t_env	*tmp;
	t_env	*new;

	if (key)
		value = ft_strdup(ft_strchr(str, '=') + 1);
	else
		value = 0;
	new = make_new_env(key, value, str);
	tmp = env;
	while (tmp)
	{
		if (ft_strcmp(new->key, tmp->key) > 0 && \
		ft_strcmp(new->key, tmp->next->key))
		{
			new->next = tmp->next;
			tmp->next = new;
		}
		tmp = tmp->next;
	}
}

void	check_argu(char **av, t_env *env)
{
	int		i;
	char	*key;
	t_env	*tmp;

	i = 1;
	while (av[i])
	{
		if (valid_argu(av[i]))
		{
			key = get_key(av[i]);
			tmp = check_exist(key, env);
			if (key && tmp)
				replace_export(tmp, av[i]);
			else
				add_new_env(key, av[i], env);
		}
		else
			printf("minishell: export: \'%s\': not a valid identifier\n", av[i]);
		i++;
	}
}

int	ft_export(t_node *head)
{
	t_env	*env;
	int		ac;
	char	**av;

	env = table_get()->env;
	av = get_av(head->data, &ac);
	if (ac == 1)
		print_export(env);
	else
		check_argu(av, env);
	return (0);
}
