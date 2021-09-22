/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carce-bo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 15:13:44 by carce-bo          #+#    #+#             */
/*   Updated: 2021/09/20 15:14:56 by carce-bo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*aux_str;
	char	*str;

	if (!s)
		return (ft_strdup(""));
	if (len == 0)
		return (ft_strdup(""));
	if (start > ft_strlen(s) - 1)
		return (ft_strdup(""));
	if (len > ft_strlen(s) - start - 1)
		len = ft_strlen(s) - start ;
	str = (char *)malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	aux_str = str;
	while (len-- > 0 && *(s + start))
		*aux_str++ = *(s++ + start);
	*aux_str = '\0';
	return (str);
}
