/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carce-bo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 15:13:39 by carce-bo          #+#    #+#             */
/*   Updated: 2021/09/20 15:14:53 by carce-bo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	n_size;

	if (!*needle)
		return ((char *)haystack);
	n_size = ft_strlen(needle);
	while (*haystack && len-- > 0)
	{
		if (*haystack == *needle)
		{
			if (ft_strncmp(haystack, needle, n_size) == 0)
			{
				if (len + 1 >= n_size)
					return ((char *)haystack);
			}
		}
		haystack++;
	}
	return (NULL);
}
