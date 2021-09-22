/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carce-bo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 15:13:41 by carce-bo          #+#    #+#             */
/*   Updated: 2021/09/20 15:14:54 by carce-bo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	len;
	char	*aux;

	aux = (char *)s;
	len = ft_strlen(s) + 1;
	while (len > 0)
	{
		if (*(aux + --len) == (char)c)
			return (aux + len);
	}
	return (NULL);
}
