/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forbidden_stuff_parser.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carce-bo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 17:30:52 by carce-bo          #+#    #+#             */
/*   Updated: 2021/08/23 17:13:21 by carce-bo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	fbdn_parser(char **str, int *q_mark_err)
{
	char	*aux;

	aux = *str;
	while (*aux == ' ')
		aux++;
	if (*aux == '|')
	{
		parse_error_near(aux, q_mark_err);
		return (1);
	}
	while (*aux)
	{
		if (*aux == ')' || *aux == ')' || *aux == ';'
			|| *aux == '*' || (*aux == '\\') || *aux == '&')
		{
			forbidden_char_found(aux, q_mark_err);
			return (1);
		}
		aux++;
	}
	return (0);
}

static char	*r_redirection_piece(char *str, int *q_mark_err)
{
	str++;
	if (*str == '>')
		str++;
	while (*str == ' ' && *str)
		str++;
	if (*str != '>' && *str != '<' && *str != '|' && *str)
		return (str);
	else
	{
		parse_error_near(str, q_mark_err);
		return (NULL);
	}
}

static char	*l_redirection_piece(char *str, int *q_mark_err)
{
	str++;
	if (*str == '<')
		str++;
	while (*str == ' ' && *str)
		str++;
	if (*str != '>' && *str != '<' && *str != '|' && *str)
		return (str);
	else
	{
		parse_error_near(str, q_mark_err);
		return (NULL);
	}
}

static char	*pipe_piece(char *str, int *q_mark_err)
{
	str++;
	while (*str == ' ' && *str)
		str++;
	if (*str != '|' && *str)
		return (str);
	else
	{
		parse_error_near(str, q_mark_err);
		return (NULL);
	}
}

int	redirection_pipe_parser(char **str, int *q_mark_err)
{
	char	*aux;

	aux = *str;
	if (fbdn_parser(str, q_mark_err))
		return (1);
	while (*aux)
	{
		if (*aux == '>' || *aux == '<' || *aux == '|')
		{
			if (*aux == '>')
				aux = r_redirection_piece(aux, q_mark_err);
			else if (*aux == '<')
				aux = l_redirection_piece(aux, q_mark_err);
			else
				aux = pipe_piece(aux, q_mark_err);
			if (!aux)
				break ;
		}
		else
			aux++;
	}
	if (!aux)
		return (1);
	return (0);
}
