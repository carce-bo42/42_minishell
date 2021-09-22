/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrixlen.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carce-bo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 15:12:56 by carce-bo          #+#    #+#             */
/*   Updated: 2021/09/20 15:14:28 by carce-bo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Returns the number of sttrings inside an
 * array of strings. It does not count the last
 * NULL pointer.*/
size_t	ft_matrixlen(char **matrix)
{
	size_t	len;

	len = 0;
	if (!matrix)
		return (0);
	while (matrix[len])
		len++;
	return (len);
}
