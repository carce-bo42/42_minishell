/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carce-bo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 15:13:31 by carce-bo          #+#    #+#             */
/*   Updated: 2021/09/20 15:14:48 by carce-bo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	len;

	if (!src || !dest)
		return (0);
	len = ft_strlen(src);
	if (size == 0)
		return (len);
	while (size-- > 1 && *src)
		*dest++ = *src++;
	*dest = '\0';
	return (len);
}
