/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carce-bo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 22:31:31 by carce-bo          #+#    #+#             */
/*   Updated: 2021/09/22 13:21:27 by carce-bo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	write_line_on_hdoc(char *line, int fd);
void	rebuild_aux_strings(t_nod *node);

void	hdoc_engine_start_and_end(t_nod *node, char **path, int stat, char *eof)
{
	if (stat == START)
	{
		*path = getcwd(NULL, 0);
		chdir(PATH_TO_TMP);
		g_shell->status = ON_HDOC;
		clean_other_hdoc(node);
	}
	else
	{
		free(eof);
		chdir(*path);
		free(*path);
	}
}

/* Aquí hace falta meter que me devuelva a la carpeta en la
 * que se encontraba antes de entrar en el directorio de tmp.
 * De momento es tal que vuelve a la carpeta minishell si es que
 * estaba allí, pero podría ser que estuviese en otro sitio.*/
static void	open_heredoc(char *eof, t_nod *node)
{
	char	*line;
	char	*current_path;

	hdoc_engine_start_and_end(node, &current_path, START, NULL);
	g_shell->pid = fork();
	if (g_shell->pid == 0)
	{
		ft_signal_main();
		while (1)
		{
			line = readline("$> ");
			if (!line || !ft_strncmp(line, eof, ft_maxlen(line, eof)))
				exit(0);
			else
				write_line_on_hdoc(line, node->fdi);
		}
	}
	else
		ft_signal_main();
	hdoc_engine_start_and_end(node, &current_path, END, eof);
}

static void	clean_hdoc_strings(t_nod *node)
{
	char	*aux;
	int		counter;

	counter = node->n_hdoc;
	aux = node->line_save;
	while (*aux && (counter > 1))
	{
		aux = ft_strnstr(aux, "\\", ft_strlen(aux));
		*aux = ' ';
		counter--;
	}
	aux = ft_strnstr(aux, "\\", ft_strlen(aux));
	if (!aux)
		return ;
	aux++;
	while (*aux == '*' && *aux)
		*aux++ = ' ';
	node->line = node->line_save;
}

static void	hd_checker(t_nod *node)
{
	char	*aux;
	char	*eof;

	aux = node->line_aux;
	while (*aux)
	{
		aux = ft_strnstr(aux, "<<", ft_strlen(aux));
		if (!aux)
			break ;
		else
		{
			aux = aux + 2;
			place_str_pointers(&aux, &node->line_aux, &node->line, 2);
		}
		eof = eof_gatherer(&node->line, &node->n_hdoc);
		open_heredoc(eof, node);
	}
	if (node->fdi != 0)
		close(node->fdi);
	node->fdi = 0;
	clean_hdoc_strings(node);
}

void	heredoc_piece(void)
{
	int		i;
	t_nod	*node;
	char	*to_free;

	i = g_shell->n_proc;
	node = g_shell->p_lst;
	while (i > 0)
	{
		hd_checker(node);
		rebuild_aux_strings(node);
		node = node->next;
		i--;
	}
	to_free = hdoc_filename(0);
	free(to_free);
}
