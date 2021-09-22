/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_responses.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carce-bo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 20:22:44 by carce-bo          #+#    #+#             */
/*   Updated: 2021/09/22 12:30:08 by carce-bo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_signal_ctrl_c(int sig)
{
	(void)sig;
	write(2, "\n\n", 2);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	ft_signal_stop_all_process_launch(int sig)
{
	t_nod	*node;
	int		i;

	(void)sig;
	node = g_shell->p_lst;
	i = g_shell->n_proc;
	while (i > 0)
	{
		node->launch = KO;
		node = node->next;
		i--;
	}
	write(2, "\n", 1);
	update_q_mark_variable(1);
	g_shell->assign_error = KO;
	g_shell->status = ON_EXE;
}

void	ft_signal_ctrl_d_process(int sig)
{
	(void)sig;
	write(2, "\n", 1);
}

void	ft_send_ctrl_c_to_child(int sig)
{
	(void)sig;
	kill(g_shell->pid, SIGINT);
	write(1, "Quit: 3\n", 8);
	g_shell->assign_error = KO;
	update_q_mark_variable(131);
}
