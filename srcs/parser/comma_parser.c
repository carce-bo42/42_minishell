/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comma_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carce-bo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 17:33:57 by carce-bo          #+#    #+#             */
/*   Updated: 2021/09/20 16:43:27 by carce-bo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Function that is called whenever a \" is found inside a str, outside
 * a \' string. This is extremely important, since \' is silenced by \" and
 * viceversa */
static char	*d_comma_str_parser(char *str, int *q_mark_err)
{
	str++;
	while (*str != '\"' && *str)
		*str++ = ' ';
	if (!*str)
	{
		multiline_error(q_mark_err);
		return (NULL);
	}
	else
		return (str);
	return (str);
}

static char	*s_comma_str_parser(char *str, int *q_mark_err)
{
	str++;
	while (*str != '\'' && *str)
		*str++ = ' ';
	if (!*str)
	{
		multiline_error(q_mark_err);
		return (NULL);
	}
	else
		return (str);
	return (str);
}

/* The string that commes in here should be the one duplicated
 * from the readline output. It will be formatted in such a way
 * anything between a correct string will be turned into spaces, 
 * so it can correctly work as bash process strings:
 * in: cat a ">> b << lol <<<<<<< >>>>>>>>>>>>>>>>>>"
 * parsed: cat a "                                    "
 * so i dont raise a parse error from the <<< or >>>.*/
int	comma_parser(char **str, int *q_mark_err)
{
	char	*aux;

	aux = *str;
	while (*aux)
	{
		if (*aux == '\"' || *aux == '\'')
		{
			if (*aux == '\"')
				aux = d_comma_str_parser(aux, q_mark_err);
			else
				aux = s_comma_str_parser(aux, q_mark_err);
			if (!aux)
				return (1);
		}
		aux++;
	}
	return (0);
}
