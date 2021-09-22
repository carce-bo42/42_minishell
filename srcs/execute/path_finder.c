/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_finder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carce-bo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 19:09:06 by carce-bo          #+#    #+#             */
/*   Updated: 2021/09/21 13:17:23 by carce-bo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**put_bars_and_cmd_on_path(char **path, char *cmd)
{
	int		i;
	char	*aux_1;
	char	*aux_2;

	i = 0;
	while (path[i])
	{
		aux_1 = path[i];
		path[i] = ft_strjoin(path[i], "/");
		aux_2 = path[i];
		path[i] = ft_strjoin(path[i], cmd);
		free(aux_1);
		free(aux_2);
		i++;
	}
	return (path);
}

char	**get_paths(char *cmd)
{
	int		i;
	char	*aux;
	char	*aux2;
	char	**paths_wo_bar;

	i = 0;
	while (g_shell->env[i])
	{
		if (!ft_strncmp(g_shell->env[i], "PATH=", 5))
			break ;
		i++;
	}
	if (!g_shell->env[i])
		command_not_found_error(cmd);
	aux = g_shell->env[i];
	while (*aux != '=')
		aux++;
	aux2 = ft_strdup(++aux);
	paths_wo_bar = ft_split(aux2, ':');
	free(aux2);
	return (put_bars_and_cmd_on_path(paths_wo_bar, cmd));
}

/* So I had pipex done, and we could use access there. Here we cant, 
 * so we have to use this fstat weird function to mimic it. Only problem
 * would be to find a directory named /bin/ls. S_ISDIR gives 0 in case
 * the file checked by fstat is not a directory, so here we go.*/
int	ft_access(char *path)
{
	int			fd;
	int			is_file;
	struct stat	aux;

	is_file = 0;
	fd = open(path, O_RDONLY);
	if (fd != -1)
	{
		fstat(fd, &aux);
		if (!S_ISDIR(aux.st_mode))
			is_file = 1;
		close(fd);
	}
	return (is_file);
}

int	check_if_path_absolute(char **cmd)
{
	char	*aux;

	aux = *cmd;
	if (*aux == '/' || *aux == '.')
	{
		if (ft_access(aux))
			return (OK);
		else
			return (KO);
	}
	else
		return (KO);
}

/*Function that will get the correct path to the binary command
 * specified by cmd (the  > 0 entries of this matrix are the corresponding
 * flags if specified). It first gets every path in the PATH env variable,
 * then it adds a / and the exec name to form the correct path (if it
 * exists), and then checks with access(2) wether there is one path
 * that can find the binary, and in that case it returns it.*/
char	*find_exec_path(char **cmd)
{
	char	**exec_paths;
	char	*path;
	int		i;

	if (check_if_path_absolute(cmd))
		return (ft_strdup(*cmd));
	exec_paths = get_paths(*cmd);
	path = NULL;
	i = 0;
	while (exec_paths[i])
	{
		if (ft_access(exec_paths[i]))
		{
			path = ft_strdup(exec_paths[i]);
			break ;
		}
		i++;
	}
	free_matrix(exec_paths);
	if (!path)
		command_not_found_error(*cmd);
	return (path);
}
