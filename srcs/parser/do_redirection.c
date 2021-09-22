/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carce-bo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 19:32:54 by carce-bo          #+#    #+#             */
/*   Updated: 2021/09/22 16:38:43 by carce-bo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	open_on_append_mode(t_nod *node, char *filename)
{
	if (node->fdo != 1)
		close(node->fdo);
	node->fdo = open(filename, O_APPEND | O_RDWR | O_CREAT, 00644);
	if (node->fdo == -1)
		error_msg_relative_to_file(filename, node);
}

void	open_on_truncate_mode(t_nod *node, char *filename)
{
	if (node->fdo != 1)
		close(node->fdo);
	node->fdo = open(filename, O_CREAT | O_RDWR | O_TRUNC, 00644);
	if (node->fdo == -1)
		error_msg_relative_to_file(filename, node);
}

int	check_for_hdoc_priority(char *str)
{
	while (*str)
	{
		if (*str == '\\')
			return (-1);
		str++;
	}
	return (0);
}

void	open_to_input(t_nod *node, char *filename)
{
	int	fd;

	fd = check_for_hdoc_priority(node->line);
	if (fd == -1)
	{
		fd = open(filename, O_RDONLY);
		if (fd == -1)
			error_msg_relative_to_file(filename, node);
		close(fd);
	}
	else
	{
		if (node->hdoc_name)
			unlink_one_heredoc(&(node->hdoc_name));
		if (node->fdi != 0)
			close(node->fdi);
		node->fdi = open(filename, O_RDONLY);
		if (node->fdi == -1)
			error_msg_relative_to_file(filename, node);
	}
}

/* red can be single or double, and red_io will give the reader and the code
 * a hint as to what the redirection is redirecting, input or output.*/
void	do_redirection(t_nod *node, char **aux, int red, int red_io)
{
	char	*filename;
	int		displacement;

	place_str_pointers(aux, &node->line_aux, &node->line, red);
	filename = filename_gatherer(&node->line, node);
	if (node->launch == OK)
	{
		if (red == DOUBLE && red_io == OUTPUT)
			open_on_append_mode(node, filename);
		else if (red == SINGLE && red_io == OUTPUT)
			open_on_truncate_mode(node, filename);
		else
			open_to_input(node, filename);
	}
	free(filename);
	displacement = node->line - node->line_save;
	displacement -= (node->line_aux - node->line_aux_save);
	move_str_pointers(&node->line_aux, aux, displacement);
}
