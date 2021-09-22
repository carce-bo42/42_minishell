/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carce-bo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 15:13:43 by carce-bo          #+#    #+#             */
/*   Updated: 2021/09/20 15:14:55 by carce-bo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(const char *s1, const char *set)
{
	int		start;
	int		end;
	size_t	len;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	end = 0;
	len = ft_strlen(s1);
	while (ft_strchr(set, (int)*(s1 + start)) && *(s1 + start))
		start++;
	if (!*(s1 + start))
		return (ft_strdup(""));
	while (ft_strchr(set, (int)*(s1 + len - 1 - end)) && *(s1 + len - 1 - end))
		end++;
	return (ft_substr(s1, start, len - start - end));
}
