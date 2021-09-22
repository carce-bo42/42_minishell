/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_envar_manipulation.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carce-bo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 19:36:33 by carce-bo          #+#    #+#             */
/*   Updated: 2021/09/20 19:37:15 by carce-bo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* String is pointing to a \  or &, hardcoded there to be
 * recognised as enviroment variables to be expanded. */
static char	*modify_length(char *str, int *len, int *i)
{
	char	*var_name;
	char	*var_value;
	int		length_wo_expansion;

	var_name = get_var_name(str);
	var_value = get_var_value(var_name, NOT_EXPORT);
	length_wo_expansion = ft_strlen(var_name);
	free(var_name);
	if (!*var_value)
		*len = *len - length_wo_expansion;
	else
		*len = *len - length_wo_expansion + ft_strlen(var_value);
	*i = *i - length_wo_expansion;
	free(var_value);
	return (str + length_wo_expansion);
}

void	add_envar_len(int *len, char *str, int full_line)
{
	int	i;

	i = *len;
	if (full_line == KO)
	{
		while (*str == ' ')
			str++;
	}
	while (i > 0)
	{
		if (*str == '\\' || *str == '&')
			str = modify_length(++str, len, &i);
		else if (*str != '*')
		{
			str++;
			i--;
		}
		else
			str++;
	}
}

/* Same as the get name of variable. It is meant to only get one char
 * if the variable name starts with a number and not a letter*/
static void	do_expand_var(char **line, char **fname, int *len, char *var_value)
{
	int	i;

	i = 0;
	*((*line)++) = ' ';
	if (!ft_isdigit((*line)[i++]))
	{
		while (ft_isalnum((*line)[i]))
		{
			(*line)[i] = ' ';
			i++;
		}
	}
	**line = ' ';
	*line = *line + i;
	while (*var_value)
	{
		*((*fname)++) = *var_value++;
		*len = *len - 1;
	}
}

static void	expand_var_name(char **line, char **filename, int *len, t_nod *node)
{
	char	*var_name;
	char	*var_value;
	char	*aux;

	var_name = get_var_name((*line + 1));
	var_value = get_var_value(var_name, NOT_EXPORT);
	if (**line == '\\' && var_value)
	{
		aux = ft_strnstr(var_value, " ", ft_maxlen(var_value, " "));
		if (aux)
			ambiguous_redirect_error(var_name, node);
	}
	if (node->launch == OK)
		do_expand_var(line, filename, len, var_value);
	free(var_name);
	free(var_value);
}

void	write_str_w_envar(char **line, char **filename, int *len, t_nod *node)
{
	char	*aux;

	aux = *filename;
	while (*len > 0 && node->launch == OK)
	{
		if (**line == '\\' || **line == '&')
			expand_var_name(line, filename, len, node);
		else if (**line != '*' && **line != '\\' && **line != '&' && **line)
		{
			*((*filename)++) = **line;
			*((*line)++) = ' ';
			*len = *len - 1;
		}
		else
			*((*line)++) = ' ';
	}
	while (**line == '*')
		*((*line)++) = ' ';
	if (node->launch == OK)
		**filename = '\0';
}
