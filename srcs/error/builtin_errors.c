/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_errors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carce-bo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 18:59:20 by carce-bo          #+#    #+#             */
/*   Updated: 2021/09/20 18:59:22 by carce-bo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export_error(char *arg, char *name)
{
	free(name);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd("export: ", 2);
	ft_putstr_fd("`", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	g_shell->q_mark_err = 1;
	update_q_mark_variable(1);
}

void	cd_error(char *path)
{
	if (g_shell->q_mark_err == 0)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(" No such file or directory\n", 2);
		update_q_mark_variable(1);
	}
}

void	exit_error(char *arg, int type)
{
	ft_putstr_fd("minishell: exit: ", 2);
	if (type == 0)
	{
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": numeric argument required\n", 2);
	}
	else
	{
		ft_putstr_fd("too many arguments\n", 2);
		update_q_mark_variable(1);
	}
}

void	unset_error(char *arg)
{
	ft_putstr_fd("minishell :", 2);
	ft_putstr_fd(" unset: ", 2);
	ft_putstr_fd("`", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("`': not a valid identifier\n", 2);
	update_q_mark_variable(1);
}
