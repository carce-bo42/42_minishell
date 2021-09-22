/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carce-bo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 18:53:36 by carce-bo          #+#    #+#             */
/*   Updated: 2021/09/20 18:58:32 by carce-bo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	order_env(void)
{
	int			i;
	int			j;
	int			k;
	char		*aux;

	k = 0;
	while (g_shell->env[k])
		k++;
	i = 0;
	while (i <= k - 1)
	{
		j = i + 1;
		while (j <= k - 1)
		{
			if (ft_strcmp(g_shell->env[i], g_shell->env[j]) > 0)
			{
				aux = g_shell->env[j];
				g_shell->env[j] = g_shell->env[i];
				g_shell->env[i] = aux;
			}
			j++;
		}
		i++;
	}
}

/* ((When called from export with no arguments, ))*/
/* All env entries have to be set from name=value to name="value".
 * This is carrying out that. With the exception that if export has
 * exported some variable that has not been defined, it only pops out
 * when you call export without arguments, with no value or equal 
 * sign. [export a] makes env not show a, but export withour arguments
 * will show at the end "declare -x a". I mark these special entries
 * with a \* at the start, so they can be identified and printed or
 * not when necessary.*/
void	create_propper_env_entry(char *name, char *value, int i)
{
	char	*aux1;
	char	*aux2;

	free(g_shell->env[i]);
	if (*value != '\\')
	{
		aux1 = ft_strjoin(name, "=\"");
		aux2 = ft_strjoin(aux1, value);
		g_shell->env[i] = ft_strjoin(aux2, "\"");
		free_two_ptrs(aux1, aux2);
	}
	else
		g_shell->env[i] = ft_strjoin("*", name);
	free_two_ptrs(name, value);
}

void	add_commas_to_env(void)
{
	char	*aux_name;
	char	*aux_value;
	char	*aux;
	int		i;

	i = 0;
	while (g_shell->env[i])
	{
		aux = g_shell->env[i];
		aux_name = get_var_name(aux);
		while (*aux != '=')
			aux++;
		aux_value = ft_strdup(++aux);
		create_propper_env_entry(aux_name, aux_value, i);
		i++;
	}
}

void	print_ordered_env(void)
{
	pid_t	pid;
	int		i;

	i = 0;
	pid = fork();
	if (pid == 0)
	{
		order_env();
		add_commas_to_env();
		while (g_shell->env[i])
		{
			if (*g_shell->env[i] != '*')
				printf("declare -x %s\n", g_shell->env[i]);
			else
				printf("declare -x %s\n", (++(g_shell->env[i])));
			i++;
		}
		exit(0);
	}
	else
		waitpid(pid, NULL, 0);
}

void	ft_env(int mode)
{
	int		i;
	char	*name;

	i = 0;
	update_q_mark_variable(0);
	if (mode == 0)
	{
		while (g_shell->env[i])
		{
			name = get_var_name(g_shell->env[i]);
			if (*(g_shell->env[i] + ft_strlen(name) + 1) != '\\')
				printf("%s\n", g_shell->env[i]);
			free(name);
			i++;
		}
	}
	else
		print_ordered_env();
}
