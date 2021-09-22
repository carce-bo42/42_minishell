/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carce-bo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 23:53:29 by carce-bo          #+#    #+#             */
/*   Updated: 2021/09/22 13:16:47 by carce-bo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wait_for_hdoc_state(void)
{
	int	stat;

	if (g_shell->pid != 0)
	{
		signal(SIGINT, ft_signal_stop_all_process_launch);
		wait(&stat);
		if (g_shell->assign_error == OK)
			update_q_mark_variable(stat);
		g_shell->assign_error = OK;
	}
}

/*Fucntion that handles signals, on the three possible cases I can 
 * come up with. First is ON_READ, which is the default state of the shell.
 * Then theres ON_HDOC, which is the status in which the shell is when it is 
 * both reading input from stdin and writing it on an hdoc. The final status
 * is ON_EXE, which is the one that the shell is while commands are
 * being executed.*/
void	ft_signal_main(void)
{
	signal(SIGTERM, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_DFL);
	if (g_shell->status == ON_READ)
		signal(SIGINT, ft_signal_ctrl_c);
	else if (g_shell->status == ON_HDOC)
		wait_for_hdoc_state();
	else
	{
		if (g_shell->pid != 0)
		{
			signal(SIGINT, ft_signal_ctrl_d_process);
			signal(SIGQUIT, ft_send_ctrl_c_to_child);
		}
	}
}
