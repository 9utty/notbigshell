/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gulee <gulee@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 15:49:26 by jinkim2           #+#    #+#             */
/*   Updated: 2022/08/30 15:32:18 by gulee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <sys/stat.h>

int		go_home(char *str, t_env *env);
void	print_cd_err(char *str);
void	renewal_pwd(t_env *env, char *pwd);
int		ft_cd(t_node *head);

int	go_home(char *str, t_env *env)
{
	(void)env;
	if (!ft_strcmp(str, "HOME") || !ft_strcmp(str, "~") || !env_get(str))
	{
		if (!ft_strcmp(env_get("HOME"), ""))
			printf("HOME not set\n");
		else
			return (chdir(env_get("HOME")));
	}
	return (0);
}

void	print_cd_err(char *str)
{
	struct stat	*buf;

	buf = malloc(sizeof(stat));
	if (!buf)
		exit (12);
	lstat(str, buf);
	if (buf->st_mode == 0)
		printf ("shellname: cd: %s: No such file or directory\n", str);
	if (buf->st_mode == 16384)
		printf ("shellname: cd: %s: Permission denied\n", str);
	if (buf->st_mode == 33261)
		printf("shellname: cd: %s: Not a directory\n", str);
	free (buf);
}

void	renewal_pwd(t_env *env, char *pwd)
{
	t_env	*tmp;
	char	*old_pwd;

	tmp = env;
	old_pwd = ft_strdup(env_get("PWD"));
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, "OLDPWD"))
		{
			free (tmp->value);
			tmp->value = old_pwd;
		}
		else if (!ft_strcmp(tmp->key, "PWD"))
		{
			free (tmp->value);
			tmp->value = ft_strdup(pwd);
		}
		tmp = tmp->next;
	}
}

int	ft_cd(t_node *head)
{
	t_env		*env;
	int			ret;
	int			ac;
	char		**av;

	env = table_get()->env;
	av = get_av(head->data, &ac);
	if (ac == 1 || (av[1] && go_home(av[1], env)))
		ret = chdir(env_get("HOME"));
	else if (!ft_strcmp(av[1], "-"))
		ret = chdir(env_get("OLDPWD"));
	else
		ret = chdir(av[1]);
	if (ret == -1)
	{
		print_cd_err(av[1]);
		return (1);
	}
	else
		renewal_pwd(env, av[1]);
	return (0);
}
