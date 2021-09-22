/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carce-bo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 15:13:07 by carce-bo          #+#    #+#             */
/*   Updated: 2021/09/20 15:14:34 by carce-bo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*aux_dst;
	const unsigned char	*aux_src;

	aux_dst = (unsigned char *)dst;
	aux_src = (const unsigned char *)src;
	if (n == 0 || (aux_src == aux_dst))
		return (dst);
	while (n-- > 0)
		*(aux_dst++) = *(aux_src++);
	return (dst);
}
