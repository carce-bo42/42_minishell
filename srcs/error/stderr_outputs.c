/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stderr_outputs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carce-bo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 18:29:54 by carce-bo          #+#    #+#             */
/*   Updated: 2021/09/20 16:23:26 by carce-bo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ambiguous_redirect_error(char *name, t_nod *node)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd("$", 2);
	ft_putstr_fd(name, 2);
	ft_putstr_fd(": ambiguous redirect\n", 2);
	node->launch = KO;
	update_q_mark_variable(1);
	if (node->p_nbr == g_shell->n_proc)
		g_shell->assign_error = KO;
}

void	error_msg_relative_to_file(char *file, t_nod *node)
{
	char	*str;

	node->launch = KO;
	str = strerror(errno);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
	update_q_mark_variable(1);
	if (node->p_nbr == g_shell->n_proc)
		g_shell->assign_error = KO;
}

/*This is the error that is raised after execve fails. */
void	error_msg(void)
{
	char	*str;

	str = strerror(errno);
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	exit(errno);
}
