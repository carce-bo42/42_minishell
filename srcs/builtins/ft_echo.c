/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carce-bo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 18:58:26 by carce-bo          #+#    #+#             */
/*   Updated: 2021/09/20 18:58:27 by carce-bo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_putstr_space(char *argv[])
{
	int	cont;
	int	j;

	cont = 0;
	while (argv[cont])
		cont++;
	j = 0;
	if (j < cont)
		ft_putstr_fd(" ", STDOUT_FILENO);
}

/* The value for a variable only visible thourgh export with no
 * arguments (declare -x name_of_variable) is a '\\'. Luckily,
 * no extern '\\' can be found in this shell except for the ones
 * I manually put, so I can just skip them when printing a string
 * and everyones happy. You didnt see anthing. */
void	ft_putstr_fd_without_esc_bar(char *str, int fd)
{
	while (*str)
	{
		if (*str != '\\')
			write(fd, str, 1);
		str++;
	}
}

void	ft_echo(char *argv[])
{
	int		i;
	bool	flag;

	flag = 0;
	i = 0;
	if (!argv[1])
	{
		print_and_update("\0", 0);
		return ;
	}
	while (argv[++i] && !ft_strncmp(argv[i], "-n", ft_maxlen(argv[i], "-n")))
		flag = 1;
	while (argv[i])
	{
		ft_putstr_fd_without_esc_bar(argv[i++], STDOUT_FILENO);
		ft_putstr_space(argv);
	}
	if (flag == 0)
		ft_putstr_fd("\n", STDOUT_FILENO);
	update_q_mark_variable(0);
}
