/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carce-bo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 11:48:14 by carce-bo          #+#    #+#             */
/*   Updated: 2021/09/22 13:57:59 by carce-bo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_new_environment(char *name, char *value)
{
	char	**new_env;
	char	*aux;
	int		i;

	new_env = malloc(sizeof(char *) * ((int)ft_matrixlen(g_shell->env) + 2));
	i = 0;
	while (g_shell->env[i])
	{
		new_env[i] = ft_strdup(g_shell->env[i]);
		i++;
	}
	aux = ft_strjoin(name, "=");
	new_env[i++] = ft_strjoin(aux, value);
	new_env[i] = NULL;
	free_three_ptrs(aux, name, value);
	free_matrix(g_shell->env);
	g_shell->env = new_env;
}

/* There are two possibilities. If the value comes from the local
 * environment, then the environment matrix has to add a new entry
 * to it. If the value comes from the global env, then the
 * correspondent entry is the one that has to change, thus the size
 * of the matrix remains unchanged. */
void	reconstruct_environment(char *name, char *value)
{
	int		entry;
	char	*aux;

	aux = NULL;
	entry = find_env(name);
	if (entry == -1)
		create_new_environment(name, value);
	else
	{
		aux = ft_strjoin(name, "=");
		free(g_shell->env[entry]);
		g_shell->env[entry] = ft_strjoin(aux, value);
		free_three_ptrs(aux, name, value);
	}
}

void	check_for_already_defined(char *name, char *value)
{
	int		prev_def;
	char	*aux;

	aux = value;
	check_for_local_value(name, &value);
	if (aux == value)
		prev_def = KO;
	else
		prev_def = OK;
	if (prev_def == OK)
		reconstruct_environment(name, value);
	else
		create_new_environment(name, value);
}

void	add_to_global_env(char *name, char *value, int stat)
{
	if (stat == NOTDEFINED)
		check_for_already_defined(name, value);
	else
		create_new_environment(name, value);
}
