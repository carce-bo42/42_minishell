/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_launching.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carce-bo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 19:11:56 by carce-bo          #+#    #+#             */
/*   Updated: 2021/09/22 16:40:23 by carce-bo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	open_hdoc_fd(t_nod *node)
{
	char	*hdoc_path;

	hdoc_path = NULL;
	if (!node->hdoc_name)
		return ;
	else
	{
		hdoc_path = ft_strjoin(PATH_TO_TMP, node->hdoc_name);
		node->fdi = open(hdoc_path, O_RDONLY);
		free(hdoc_path);
	}
}

/*Here, fdi and fdo are auxiliar file descriptors we use
 * so we dont lose them after redirecting input / ouput somewhere
 * from the father process. The last call to sup stdin stdout and close
 * is meant to reset stdin and stdout back to normal.*/
void	truly_launch_from_father(t_nod *node)
{
	int		fdi;
	int		fdo;

	fdi = dup(0);
	fdo = dup(1);
	dup_stdin_stdout_and_close(node->fdi, node->fdo);
	exec_builtin(node->cmd, FATHER);
	dup_stdin_stdout_and_close(fdi, fdo);
}

void	launch_from_fork(t_nod *node)
{
	g_shell->status = ON_EXE;
	g_shell->pid = fork();
	if (g_shell->pid == 0)
		call_execve(node);
	else
	{
		ft_signal_main();
		close_all_fds(node);
		wait_childs();
		g_shell->status = ON_READ;
	}
}

void	launch_builtins_from_father(t_nod *node)
{
	if (node->launch == OK)
	{
		clear_envar_defs(&node->cmd);
		open_hdoc_fd(node);
		if (node->cmd[0])
		{
			if (ft_isbuiltin(node->cmd))
				truly_launch_from_father(node);
			else
				launch_from_fork(node);
		}
	}
}

void	launch_processes(void)
{
	int		i;
	t_nod	*node;

	g_shell->status = ON_EXE;
	i = g_shell->n_proc;
	node = g_shell->p_lst;
	if (i == 1)
		launch_builtins_from_father(node);
	else
		launch_from_childs(node, i);
	g_shell->pid = 0;
	g_shell->status = ON_READ;
}
