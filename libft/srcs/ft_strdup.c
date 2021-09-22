/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carce-bo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 15:13:26 by carce-bo          #+#    #+#             */
/*   Updated: 2021/09/20 15:14:46 by carce-bo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	char	*output_str;
	int		i;

	output_str = (char *) malloc(sizeof (*src) * (ft_strlen(src) + 1));
	if (!output_str)
		return (NULL);
	i = 0;
	while (src[i] != '\0')
	{
		output_str[i] = src[i];
		i++;
	}
	output_str[i] = '\0';
	return (output_str);
}
