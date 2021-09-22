/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sophisticated_frees.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carce-bo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 19:16:40 by carce-bo          #+#    #+#             */
/*   Updated: 2021/09/22 16:44:22 by carce-bo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_process_list(void)
{
	t_nod	*node;
	t_nod	*aux;

	node = g_shell->p_lst;
	while (node)
	{
		free_matrix(node->cmd);
		aux = node;
		node = node->next;
		free_three_ptrs(aux->line_save, aux->line_aux_save, aux);
		aux = NULL;
	}
}

void	unlink_one_heredoc(char **hdoc_name)
{
	char	*aux;

	aux = ft_strjoin(PATH_TO_TMP, *hdoc_name);
	unlink(aux);
	free_two_ptrs(*hdoc_name, aux);
	*hdoc_name = NULL;
}

void	unlink_all_heredocs(void)
{
	t_nod	*node;
	char	*current_path;
	int		i;

	i = g_shell->n_proc;
	node = g_shell->p_lst;
	current_path = getcwd(NULL, 0);
	chdir(PATH_TO_TMP);
	while (i > 0)
	{
		if (node->hdoc_name)
		{
			unlink(node->hdoc_name);
			free(node->hdoc_name);
		}
		node = node->next;
		i--;
	}
	chdir(current_path);
	free(current_path);
}
