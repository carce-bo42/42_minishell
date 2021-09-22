/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   several_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carce-bo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 19:14:46 by carce-bo          #+#    #+#             */
/*   Updated: 2021/09/22 13:17:49 by carce-bo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	*copy_new_pipe_into_old(int p[2])
{
	int	*output;

	output = malloc(sizeof(int) * 2);
	output[0] = p[0];
	output[1] = p[1];
	return (output);
}

void	subst_fd_for_pipe(int *node_fd, int new_fd, int fd)
{
	if (fd == IN)
	{
		if (*node_fd == 0)
			*node_fd = new_fd;
		else
			close(new_fd);
	}
	else if (fd == OUT)
	{
		if (*node_fd == 1)
			*node_fd = new_fd;
		else
			close(new_fd);
	}
}

void	execute_child(t_nod *node, int new_pip[2], int old_pip[2])
{
	clear_envar_defs(&node->cmd);
	open_hdoc_fd(node);
	if (node->p_nbr != 1)
		subst_fd_for_pipe(&node->fdi, old_pip[0], IN);
	if (node->p_nbr != g_shell->n_proc)
		subst_fd_for_pipe(&node->fdo, new_pip[1], OUT);
	else
		close(new_pip[1]);
	if (node->cmd[0])
	{
		if (ft_isbuiltin(node->cmd))
		{
			dup_stdin_stdout_and_close(node->fdi, node->fdo);
			exec_builtin(node->cmd, CHILD);
		}
		else
			call_execve(node);
	}
}

void	father_during_child_exec(t_nod *node, int new_pip[2], int *old_pip[2])
{
	ft_signal_main();
	close(new_pip[1]);
	if (node->p_nbr != 1)
	{
		close((*old_pip)[0]);
		free(*old_pip);
	}
	if (node->p_nbr == g_shell->n_proc)
		close(new_pip[0]);
	else
		*old_pip = copy_new_pipe_into_old(new_pip);
	close_all_fds(node);
}

void	launch_from_childs(t_nod *node, int i)
{
	int		new_pip[2];
	int		*old_pip;

	old_pip = NULL;
	while (i > 0)
	{
		pipe(new_pip);
		g_shell->pid = fork();
		if (g_shell->pid == 0)
		{
			close(new_pip[0]);
			if (node->launch == OK)
				execute_child(node, new_pip, old_pip);
			else
				exit(0);
		}
		else
			father_during_child_exec(node, new_pip, &old_pip);
		node = node->next;
		i--;
	}
	wait_childs();
}
