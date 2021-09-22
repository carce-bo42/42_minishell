/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comand_argument_gathering.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carce-bo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 22:37:06 by carce-bo          #+#    #+#             */
/*   Updated: 2021/09/20 19:27:19 by carce-bo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prepare_line_for_split(char *str)
{
	while (*str)
	{
		if (*str == '\'')
		{
			while (*(++str) != '\'')
			{
				if (*str == ' ')
					*str = '*';
			}
			str++;
		}
		else if (*str == '\"')
		{
			while (*(++str) != '\"')
			{
				if (*str == ' ')
					*str = '*';
			}
			str++;
		}
		else
			str++;
	}
}

void	convert_argument_correctly(char **arg)
{
	char	*actual_arg;
	char	*aux;
	char	*str;
	int		len;

	len = string_length_bash(*arg, KO);
	actual_arg = malloc(sizeof(char) * (len + 1));
	aux = actual_arg;
	str = *arg;
	while (len > 0)
	{
		if (*str != '*')
		{
			*aux++ = *str;
			len--;
		}
		str++;
	}
	*aux = '\0';
	free(*arg);
	*arg = actual_arg;
}

void	clean_args_on_cmd(char **cmd)
{
	int	i;
	int	j;

	i = 0;
	while (cmd[i])
	{
		j = 0;
		while (cmd[i][j])
		{
			if (cmd[i][j] == '*')
				cmd[i][j] = ' ';
			j++;
		}
		i++;
	}
	i = 0;
	while (cmd[i])
	{
		convert_argument_correctly(&cmd[i]);
		i++;
	}
}

void	gather_args(t_nod *node)
{
	prepare_line_for_split(node->line);
	node->cmd = ft_split(node->line, ' ');
	clean_args_on_cmd(node->cmd);
	if (!node->cmd[0])
	{
		free_matrix(node->cmd);
		node->cmd = NULL;
		node->launch = KO;
	}
}

void	gather_process_arguments(void)
{
	int		i;
	t_nod	*node;

	i = g_shell->n_proc;
	node = g_shell->p_lst;
	while (i > 0)
	{
		if (node->launch == OK)
		{
			expand_vars_outside_strings(node);
			gather_args(node);
		}
		node = node->next;
		i--;
	}
}
