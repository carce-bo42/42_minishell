/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carce-bo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 18:58:21 by carce-bo          #+#    #+#             */
/*   Updated: 2021/09/22 13:57:07 by carce-bo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_export_arg(char *arg)
{
	if (ft_isvalid_env_start(*arg, Q_MARK_KO))
	{
		while (ft_isvalid_env_core(*arg))
			arg++;
		if (*arg == '=' || !*arg)
			return (1);
		else
			return (0);
	}
	else
		return (0);
}

int	parse_argument(char *arg)
{
	char	*name;
	int		name_entry;

	if (check_export_arg(arg))
	{
		name = get_var_name(arg);
		if (!*(arg + ft_strlen(name)))
		{
			free(name);
			return (NOTDEFINED);
		}
		name_entry = find_env(name);
		free(name);
		if (name_entry == -1)
			return (DEFINITION);
		else
			return (REDEFINITION);
	}
	else
		return (EXPORT_ERROR);
}

void	check_for_local_value(char *name, char **prev_value)
{
	char	*local_value;

	local_value = get_var_value(name, EXPORT_CALL);
	if (*local_value != '\\')
	{
		free(*prev_value);
		*prev_value = local_value;
	}
	else
		free(local_value);
}

void	ft_export(char **argv)
{
	int		i;
	int		arg_type;
	char	*value;
	char	*name;

	i = 1;
	update_q_mark_variable(0);
	if (!argv[1])
		ft_env(1);
	while (argv[i])
	{
		arg_type = parse_argument(argv[i]);
		name = get_var_name(argv[i++]);
		if (arg_type != NOTDEFINED && arg_type != EXPORT_ERROR)
			value = ft_strdup(argv[i - 1] + ft_strlen(name) + 1);
		if (arg_type == DEFINITION)
			add_to_global_env(name, value, DEFINITION);
		else if (arg_type == REDEFINITION)
			overwrite_env_value(name, value);
		else if (arg_type == NOTDEFINED)
			add_to_global_env(name, ft_strdup("\\"), NOTDEFINED);
		else
			export_error(argv[i - 1], name);
	}
}
