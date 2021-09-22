/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carce-bo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 22:36:45 by carce-bo          #+#    #+#             */
/*   Updated: 2021/09/20 19:36:30 by carce-bo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Returns the length of the "process command string". Example:
 * cmd: [ls -l < a >> c | < lol >c cat | grep >> lulz < a hi].
 * ret1 = len(ls -l < a >> c ),
 * ret2 = len( < lol >c cat ),
 * ret3 = len( grep >> lulz < a hi).*/
static size_t	process_str_length(char	*str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '|')
			return (i);
		i++;
	}
	return (i);
}

static void	pointer_mover(char **aux, char **str, size_t len)
{
	if (*(*aux + len) == '|')
	{
		*str = *str + len + 1;
		*aux = *aux + len + 1;
	}
	else
	{
		*str = *str + len;
		*aux = *aux + len;
	}
}

t_nod	*create_pnode(char **aux, char **str, int *n_proc)
{
	t_nod	*process;
	size_t	len;

	process = malloc(sizeof(t_nod));
	process->p_nbr = ++(*n_proc);
	process->fdi = 0;
	process->fdo = 1;
	process->hdoc_name = NULL;
	process->next = NULL;
	process->cmd = NULL;
	process->n_hdoc = 0;
	process->launch = OK;
	len = process_str_length(*aux);
	process->line = ft_substr(*str, 0, len);
	process->line_aux = ft_substr(*aux, 0, len);
	process->line_save = process->line;
	process->line_aux_save = process->line_aux;
	pointer_mover(aux, str, len);
	return (process);
}

void	process_command_parsing(void)
{
	t_nod	*p_nd;

	g_shell->parse_rl = g_shell->rl_tofree;
	g_shell->rl_aux = g_shell->rl;
	p_nd = create_pnode(&g_shell->parse_rl, &g_shell->rl_aux, &g_shell->n_proc);
	g_shell->p_lst = p_nd;
	while (*g_shell->parse_rl)
	{
		p_nd->next = create_pnode(&g_shell->parse_rl,
				&g_shell->rl_aux, &g_shell->n_proc);
		p_nd = p_nd->next;
	}
	free(g_shell->rl_tofree);
	free(g_shell->rl);
}
