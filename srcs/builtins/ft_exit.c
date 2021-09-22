/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carce-bo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 18:55:39 by carce-bo          #+#    #+#             */
/*   Updated: 2021/09/20 18:58:36 by carce-bo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_if_isdigit(char *str)
{
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		str++;
	if (*str != '+' && *str != '-' && ft_isdigit((int)*str) == 0)
		return (0);
	if (ft_isdigit((int)*str) == 0)
		str++;
	if (ft_isdigit((int)*str) == 0)
		return (0);
	while (ft_isdigit((int)(*str)))
		str++;
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		str++;
	if (*str)
		return (0);
	else
		return (1);
}

//static uint8_t	ft_ato_uint8(const char *str)
static u_int8_t	ft_ato_uint8(const char *str)
{
	int			sign;
	long long	n;

	sign = 1;
	n = 0;
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		str++;
	if (*str != '+' && *str != '-' && ft_isdigit((int)*str) == 0)
		return (0);
	if (*str == '-')
		sign = -1;
	if (ft_isdigit((int)*str) == 0)
		str++;
	if (ft_isdigit((int)*str) == 0)
		return (0);
	while (ft_isdigit((int)*str))
	{
		n = n * 10 + *str++ - '0';
		if ((n * sign) > UCHAR_MAX)
			return ((u_int8_t)(n * sign));
		if ((n * sign) < 0)
			return ((u_int8_t)(n * sign));
	}
	return ((u_int8_t)(n * sign));
}

void	ft_exit(char **args, int call)
{
	int		is_numeric;

	if (call == FATHER)
		ft_putstr_fd("exit\n", 2);
	if (!args[1])
		exit(0);
	is_numeric = check_if_isdigit(args[1]);
	if (!is_numeric)
	{
		exit_error(args[1], 0);
		exit(255);
	}
	else
	{
		if (!args[2])
			exit((int)ft_ato_uint8(args[1]));
		else
			exit_error(args[1], 1);
	}
}
