/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carce-bo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 18:58:14 by carce-bo          #+#    #+#             */
/*   Updated: 2021/09/21 12:00:21 by carce-bo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_env(char *name)
{
	char	*aux;
	int		i;

	i = 0;
	aux = ft_strjoin(name, "=");
	while (g_shell->env[i])
	{
		if (!ft_strncmp(g_shell->env[i], aux, ft_strlen(aux)))
		{
			free(aux);
			return (i);
		}
		i++;
	}
	free(aux);
	return (-1);
}

char	*check_pwd(char *str, int opwd, int home)
{
	char	*s;

	s = NULL;
	if (!str)
	{
		if (home != -1)
			s = ft_strdup(g_shell->env[home] + 5);
		else
			print_and_update("minishell: cd: HOME not set", 1);
	}
	else if (!ft_strncmp(str, "-", ft_maxlen(str, "-")))
	{
		if (opwd != -1)
		{
			s = ft_strdup(g_shell->env[opwd] + 7);
			print_and_update(g_shell->env[opwd] + 7, 0);
		}
		else
			print_and_update("minishell: cd: OLDPWD not set", 1);
	}
	else
		s = ft_strdup(str);
	return (s);
}

void	reconstruct_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	add_to_global_env(ft_strdup("PWD"), pwd, DEFINITION);
}

void	cd_env(int i[2])
{
	char	*new_oldpwd;
	char	*pwd;
	char	*tmp;

	new_oldpwd = NULL;
	pwd = NULL;
	tmp = NULL;
	new_oldpwd = ft_strdup(g_shell->env[i[0]] + 4);
	tmp = getcwd(NULL, 0);
	pwd = ft_strjoin("PWD=", tmp);
	free_two_ptrs(tmp, g_shell->env[i[0]]);
	g_shell->env[i[0]] = pwd;
	if (i[1] == -1)
		add_to_global_env(ft_strdup("OLDPWD"), new_oldpwd, DEFINITION);
	else
	{
		free(g_shell->env[i[1]]);
		g_shell->env[i[1]] = ft_strjoin("OLDPWD=", new_oldpwd);
		free(new_oldpwd);
	}
}

void	ft_cd(char *str)
{
	char	*s;
	int		i[2];

	update_q_mark_variable(0);
	if (find_env("PWD") == -1)
		reconstruct_pwd();
	i[0] = find_env("PWD");
	i[1] = find_env("OLDPWD");
	s = check_pwd(str, i[1], find_env("HOME"));
	if (chdir(s) == -1)
		cd_error(s);
	else
	{
		cd_env(i);
		update_q_mark_variable(0);
	}
	free(s);
}
