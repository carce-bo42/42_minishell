/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stderr_outputs_extra.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carce-bo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 23:52:21 by carce-bo          #+#    #+#             */
/*   Updated: 2021/09/20 16:18:59 by carce-bo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	multiline_error(int *q_mark_err)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd("unclosed commas were found on command\n", 2);
	*q_mark_err = 42;
	update_q_mark_variable(42);
}

void	parse_error_near(char *str, int	*q_mark_err)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd("syntax error near unexpected token `", 2);
	write(2, str, 1);
	ft_putstr_fd("\'\n", 2);
	*q_mark_err = 258;
	update_q_mark_variable(258);
}

void	forbidden_char_found(char *str, int *q_mark_err)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd("found forbidden char: `", 2);
	write(2, str, 1);
	ft_putstr_fd("\'\n", 2);
	*q_mark_err = 42;
	update_q_mark_variable(42);
}

void	call_error(void)
{
	ft_putstr_fd("No such thing as minishell scripting...\n\n\n", 2);
	ft_putstr_fd("                                               ...yet\n", 2);
	exit(42);
}

void	command_not_found_error(char *cmd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd("command not found\n", 2);
	exit(127);
}
