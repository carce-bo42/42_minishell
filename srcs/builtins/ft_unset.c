/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carce-bo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 18:57:00 by carce-bo          #+#    #+#             */
/*   Updated: 2021/09/20 18:58:46 by carce-bo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_unset_arg(char *arg)
{
	if (ft_isvalid_env_start(*arg, Q_MARK_KO))
	{
		while (ft_isvalid_env_core(*arg))
			arg++;
		if (!*arg)
			return (0);
		else
			return (1);
	}
	else
		return (1);
}

/* I should always check for the deletion of the
 * first value of the local_envar_list, BUT GUESS WHAT MY FIRST
 * VAR_NAME IS ? AND IT CANNOT BE EITHER EXPORTED OR UNSET
 * HAHA I WIN. So i didnt cover it. Should be fine.*/
static void	delete_node(char *name)
{
	t_var	*node;
	t_var	*prev_node;

	node = g_shell->envar;
	prev_node = NULL;
	while (node)
	{
		if (!ft_strncmp(node->name, name, ft_maxlen(node->name, name)))
		{
			prev_node->next = node->next;
			free_three_ptrs(node->name, node->value, node);
			break ;
		}
		prev_node = node;
		node = node->next;
	}
}

static void	remove_from_env(int entry_to_remove)
{
	int		len;
	char	**new_env;
	int		i;
	int		j;

	i = 0;
	j = 0;
	len = ft_matrixlen(g_shell->env);
	new_env = malloc(sizeof(char *) * len);
	while (g_shell->env[i])
	{
		if (i != entry_to_remove)
			new_env[j++] = ft_strdup(g_shell->env[i]);
		i++;
	}
	new_env[j] = NULL;
	free_matrix(g_shell->env);
	g_shell->env = new_env;
}

static void	remove_from_all_env(char *name)
{
	int		i;
	char	*aux;

	i = 0;
	aux = ft_strjoin(name, "=");
	while (g_shell->env[i])
	{
		if (!ft_strncmp(aux, g_shell->env[i], ft_strlen(aux)))
		{
			remove_from_env(i);
			break ;
		}
		i++;
	}
	free(aux);
	delete_node(name);
}

void	ft_unset(char **av)
{
	int	i;
	int	show_error;

	i = 1;
	update_q_mark_variable(0);
	while (av[i])
	{
		show_error = check_unset_arg(av[i]);
		if (!show_error)
			remove_from_all_env(av[i]);
		else
			unset_error(av[i]);
		i++;
	}
}
