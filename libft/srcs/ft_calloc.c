/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carce-bo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 15:12:06 by carce-bo          #+#    #+#             */
/*   Updated: 2021/09/20 15:14:06 by carce-bo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;
	void	*aux;
	size_t	len;

	len = count * size;
	ptr = malloc(len);
	if (!ptr)
		return (NULL);
	aux = ptr;
	while (len-- > 0)
		*(unsigned char *)aux++ = '\0';
	return (ptr);
}
