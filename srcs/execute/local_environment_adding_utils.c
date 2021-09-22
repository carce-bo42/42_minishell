/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_to_local_env_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carce-bo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 19:05:46 by carce-bo          #+#    #+#             */
/*   Updated: 2021/09/21 12:52:02 by carce-bo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	replace_value_on_local_env(t_var *nod, char *name, char *value)
{
	free(name);
	free(nod->value);
	nod->value = value;
}

t_var	*new_env_var(char *name, char *value)
{
	t_var	*nod;

	nod = malloc(sizeof(t_var));
	nod->name = name;
	nod->value = value;
	nod->next = NULL;
	return (nod);
}

int	check_if_def(char *str)
{
	if (!str)
		return (0);
	if (ft_isvalid_env_start(*str, Q_MARK_KO))
	{
		while (ft_isvalid_env_core(*str))
			str++;
		if (*str == '=')
			return (1);
	}
	return (0);
}
