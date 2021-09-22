/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carce-bo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 15:13:30 by carce-bo          #+#    #+#             */
/*   Updated: 2021/09/20 15:14:48 by carce-bo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	k;
	size_t	l;

	k = 0;
	l = ft_strlen(dest);
	if (l < size)
	{
		i = ft_strlen(src) + l;
		if (size > i + 1)
			j = i + 1;
		else
			j = size;
		while (k + 1 < j - l)
		{
			dest[l + k] = src[k];
			k++;
		}
		dest[l + k] = '\0';
	}
	else
		i = ft_strlen(src) + size;
	return (i);
}
