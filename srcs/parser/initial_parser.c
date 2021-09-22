/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initial_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carce-bo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 22:31:42 by carce-bo          #+#    #+#             */
/*   Updated: 2021/09/20 19:31:29 by carce-bo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	clean_exit(void)
{
	rl_clear_history();
	free(g_shell);
	write(2, "exit\n", 6);
	exit(0);
}

int	initial_parser(void)
{
	char	*aux;

	if (!g_shell->rl)
		clean_exit();
	add_history(g_shell->rl);
	aux = g_shell->rl;
	while (*aux)
	{
		if (*aux >= 9 && *aux <= 13)
			*aux = ' ';
		aux++;
	}
	g_shell->parse_rl = ft_strdup(g_shell->rl);
	g_shell->rl_tofree = g_shell->parse_rl;
	if (comma_parser(&g_shell->parse_rl, &g_shell->q_mark_err)
		|| redirection_pipe_parser(&g_shell->parse_rl, &g_shell->q_mark_err))
	{
		free(g_shell->rl_tofree);
		free(g_shell->rl);
		return (1);
	}
	return (0);
}
