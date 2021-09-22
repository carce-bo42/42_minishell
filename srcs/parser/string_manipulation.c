/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_manipulation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carce-bo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 22:40:12 by carce-bo          #+#    #+#             */
/*   Updated: 2021/09/20 19:35:38 by carce-bo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isvalid_env_start(char a, int consider_q_mark)
{
	int	ret;

	ret = 0;
	if (consider_q_mark == Q_MARK_OK)
	{
		if ((a >= 'a' && a <= 'z') || (a >= 'A' && a <= 'Z')
			|| a == '_' || a == '?')
			ret = 1;
	}
	else
	{
		if ((a >= 'a' && a <= 'z') || (a >= 'A' && a <= 'Z')
			|| a == '_')
			ret = 1;
	}
	return (ret);
}

int	ft_isvalid_env_core(char a)
{
	int	ret;

	ret = 0;
	if (ft_isalnum(a) || a == '_')
		ret = 1;
	return (ret);
}

void	edit_string(char **str, int *i, int envar)
{
	if (**str == '\"')
	{
		**str = '*';
		while (*(++(*str)) != '\"')
		{
			if (**str == '$' && envar == OK)
			{
				if (ft_isvalid_env_start(*(*str + 1), Q_MARK_OK))
				{
					**str = '&';
					(*i)--;
				}
			}
			(*i)++;
		}
	}
	else
	{
		**str = '*';
		while (*(++(*str)) != '\'')
			(*i)++;
	}
	**str = '*';
}

/* computes the length of the string that it has to take out
 * from the piece of command. it should exactly coincide with
 * the mesure of the strings bash uses as args/filenames,
 * exhibiting commas and allowing appended strings to start or
 * ends of comma strings when not spaced. An example of this would
 * be: << "hey""dude" is a heredoc whichs EOF is heydude, and so is
 * << "hey"dude, <<hey"dude", and any combination you can imagine
 * from this. Tedious.
 * This function apart from computing this length it marks with a
 * '*' those chars that will not have to be written inside the
 * final string that has to be gathered. 2 in 1 :D*/
int	string_length_bash(char *str, int envar)
{
	int	i;

	i = 0;
	while (*str == ' ')
		str++;
	while (*str != ' ' && *str != '<' && *str != '>' && *str)
	{
		if (*str == '$' && envar == OK)
		{
			if (ft_isvalid_env_start(*(str + 1), Q_MARK_OK))
				*str++ = '\\';
		}
		if (*str == '\"' || *str == '\'')
			edit_string(&str, &i, envar);
		else
			i++;
		str++;
	}
	return (i);
}

/* A pointer mover. We work with 2 strings, the one that has something inside
 * the commas, and the one that doesnt. This is because its easier to work with
 * a string that does not look inside "" / '' strings, so we can spot which
 * redirection, pipe or whatever is relevant or not when parsing.
 * Minishell  SHOULD NOT workr when given <<, >>, <, >, | inside commas. These
 *will always have to be gathered as arguments for a command. Just like bash.*/
void	place_str_pointers(char **aux, char **str_blank, char **str_full, int i)
{
	long long int	displacement;

	while (**aux == ' ')
		(*aux)++;
	displacement = *aux - *str_blank;
	if (str_full)
	{
		while (displacement-- > 0)
		{
			if ((int)displacement <= i)
				**str_full = ' ';
			*str_full = *str_full + 1;
		}
	}
	displacement = *aux - *str_blank;
	while (displacement-- > 0)
	{
		if ((int)displacement <= i)
			**str_blank = ' ';
		*str_blank = *str_blank + 1;
	}
}
