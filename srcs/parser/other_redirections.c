/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carce-bo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 22:40:37 by carce-bo          #+#    #+#             */
/*   Updated: 2021/09/22 13:21:44 by carce-bo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*filename_gatherer(char **line, t_nod *node)
{
	char	*filename;
	char	*aux;
	int		len;

	len = string_length_bash(*line, OK);
	add_envar_len(&len, *line, ARGUMENT);
	filename = malloc(sizeof(char) * (len + 1));
	aux = filename;
	write_str_w_envar(line, &aux, &len, node);
	return (filename);
}

void	move_str_pointers(char **str, char **aux, int i)
{
	int	displacement;

	displacement = i;
	while (displacement-- > 0)
		*str = *str + 1;
	displacement = i;
	while (displacement-- > 0)
		*aux = *aux + 1;
}

void	redirection_checker(t_nod *node)
{
	char	*aux;

	aux = node->line_aux;
	while (*aux && node->launch == OK)
	{
		if (*aux == '>' || *aux == '<')
		{
			if (*(aux + 1) == '>')
			{
				aux = aux + 2;
				do_redirection(node, &aux, DOUBLE, OUTPUT);
			}
			else
			{
				if (*aux++ == '>')
					do_redirection(node, &aux, SINGLE, OUTPUT);
				else
					do_redirection(node, &aux, SINGLE, INPUT);
			}
		}
		else
			aux++;
	}
}

void	clean_hdoc_bar(t_nod *node)
{
	char	*aux;

	aux = node->line_save;
	while (*aux)
	{
		if (*aux == '\\')
			*aux = ' ';
		aux++;
	}
	node->line = node->line_save;
	free(node->line_aux_save);
	node->line_aux_save = NULL;
}

void	other_io_redirections(void)
{
	int		i;
	t_nod	*node;

	i = g_shell->n_proc;
	node = g_shell->p_lst;
	while (i > 0)
	{
		if (node->launch == OK)
		{
			redirection_checker(node);
			clean_hdoc_bar(node);
		}
		node = node->next;
		i--;
	}
}
