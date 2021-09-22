/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_descriptor_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carce-bo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 19:09:41 by carce-bo          #+#    #+#             */
/*   Updated: 2021/09/22 13:17:47 by carce-bo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_all_fds(t_nod *node)
{
	if (node->fdi != 0)
	{
		close(node->fdi);
		node->fdi = 0;
	}
	if (node->fdo != 1)
	{
		close(node->fdo);
		node->fdo = 1;
	}
}

/* Function that comes in VERY handy when working with pipes. It
 * duplicates the STDIN fildescriptor to some new_in, and does the
 * same for STDOUT, then proceeds to close these new_in/new_out fd's,
 * since they are now accessible through 0 and 1, respectively.*/
void	dup_stdin_stdout_and_close(int new_in, int new_out)
{
	if (new_in != 0)
	{
		if (dup2(new_in, 0) == -1)
			error_msg();
		close(new_in);
	}
	if (new_out != 1)
	{
		if (dup2(new_out, 1) == -1)
			error_msg();
		close(new_out);
	}
}

void	call_execve(t_nod *node)
{
	char	*path;
	char	**env;

	ft_signal_main();
	dup_stdin_stdout_and_close(node->fdi, node->fdo);
	path = find_exec_path(node->cmd);
	env = clone_environment(g_shell->env, KO);
	if (execve(path, node->cmd, env) == -1)
		error_msg();
}

void	get_q_mark(int stat)
{
	if (g_shell->assign_error == OK)
	{
		if (WIFEXITED(stat))
			update_q_mark_variable(WEXITSTATUS(stat));
		else if (WIFSIGNALED(stat))
			update_q_mark_variable(WTERMSIG(stat) + 128);
		else if (WIFSTOPPED(stat))
			update_q_mark_variable(WSTOPSIG(stat));
	}
	g_shell->assign_error = OK;
}

void	wait_childs(void)
{
	int		n_process;
	int		stat;
	pid_t	pid;

	n_process = g_shell->n_proc;
	while (n_process > 0)
	{
		pid = wait(&stat);
		if (pid == g_shell->pid)
			get_q_mark(stat);
		n_process--;
	}
}
