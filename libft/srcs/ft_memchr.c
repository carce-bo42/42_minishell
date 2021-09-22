/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carce-bo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 15:13:03 by carce-bo          #+#    #+#             */
/*   Updated: 2021/09/20 15:14:32 by carce-bo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*aux;

	aux = (unsigned char *)s;
	while (n-- > 0)
	{
		if (*aux == (unsigned char)c)
			return ((void *)aux);
		aux++;
	}
	return (NULL);
}
