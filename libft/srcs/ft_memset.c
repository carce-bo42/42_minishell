/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carce-bo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 15:13:11 by carce-bo          #+#    #+#             */
/*   Updated: 2021/09/20 15:14:35 by carce-bo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	a;
	unsigned char	*aux;

	aux = (unsigned char *)b;
	a = (unsigned char)c;
	while (len-- > 0)
		*(aux++) = a;
	return (b);
}
