/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carce-bo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 15:13:35 by carce-bo          #+#    #+#             */
/*   Updated: 2021/09/20 15:14:51 by carce-bo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*out;
	char			*aux;
	unsigned int	idx;
	size_t			len;

	if (!s || !f)
		return (NULL);
	len = ft_strlen(s);
	out = (char *)malloc(sizeof(char) * len + 1);
	if (!out)
		return (NULL);
	aux = out;
	idx = 0;
	while (idx < len && aux)
	{
		*aux++ = (*f)(idx, *(s + idx));
		idx++;
	}
	*aux = '\0';
	return (out);
}
