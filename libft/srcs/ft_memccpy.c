/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carce-bo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 15:13:00 by carce-bo          #+#    #+#             */
/*   Updated: 2021/09/20 15:14:31 by carce-bo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	const unsigned char	*aux_src;
	unsigned char		*aux_dst;

	aux_src = (const unsigned char *)src;
	aux_dst = (unsigned char *)dst;
	if ((!*aux_src && !*aux_dst) || n == 0 || dst == src)
		return (NULL);
	while (n-- > 0)
	{
		*(aux_dst) = *(aux_src);
		if (*aux_src == (unsigned char)c)
			return ((void *)++aux_dst);
		aux_dst++;
		aux_src++;
	}
	return (NULL);
}
