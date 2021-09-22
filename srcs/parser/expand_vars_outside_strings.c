/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars_outside_strings.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carce-bo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 19:24:27 by carce-bo          #+#    #+#             */
/*   Updated: 2021/09/20 19:28:14 by carce-bo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	wait_for_next_comma(char **str, int *i, char comma)
{
	(*i)++;
	*str = *str + 1;
	while (**str != comma)
	{
		if (comma == '\"')
		{
			if (**str == '$' && ft_isvalid_env_start(*(*str + 1), Q_MARK_OK))
				(*i)--;
		}
		*str = *str + 1;
		(*i)++;
	}
	*str = *str + 1;
	(*i)++;
}

static void	wait_for_next_comma_wo_counter(char **str, char comma)
{
	*str = *str + 1;
	while (**str != comma)
	{
		if (comma == '\"')
		{
			if (**str == '$' && ft_isvalid_env_start(*(*str + 1), Q_MARK_OK))
				**str = '&';
		}
		*str = *str + 1;
	}
	*str = *str + 1;
}

static int	ft_strlen_wo_dollars(char *str)
{
	int	i;

	i = 0;
	while (*str)
	{
		if (*str == '\"')
			wait_for_next_comma(&str, &i, '\"');
		else if (*str == '\'')
			wait_for_next_comma(&str, &i, '\'');
		else if (*str == '$' && ft_isvalid_env_start(*(str + 1), Q_MARK_OK))
			str++;
		else
		{
			str++;
			i++;
		}
	}
	return (i);
}

static void	put_ampersands_on_envars(char **line)
{
	char	*aux;

	aux = *line;
	while (*aux)
	{
		if (*aux == '\'')
			wait_for_next_comma_wo_counter(&aux, '\'');
		else if (*aux == '\"')
			wait_for_next_comma_wo_counter(&aux, '\"');
		else if (*aux == '$' && ft_isvalid_env_start(*(aux + 1), Q_MARK_OK))
			*aux++ = '&';
		else
			aux++;
	}
}

void	expand_vars_outside_strings(t_nod *node)
{
	int		len;

	len = ft_strlen_wo_dollars(node->line);
	put_ampersands_on_envars(&node->line);
	add_envar_len(&len, node->line, FULL_LINE);
	node->line_aux = malloc(sizeof(char) * (len + 1));
	node->line_aux_save = node->line_aux;
	write_str_w_envar(&node->line, &node->line_aux, &len, node);
	free(node->line_save);
	node->line_save = ft_strdup(node->line_aux_save);
	node->line = node->line_save;
}
