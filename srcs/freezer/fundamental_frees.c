/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reasonably_util_frees.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carce-bo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 11:03:39 by carce-bo          #+#    #+#             */
/*   Updated: 2021/09/20 20:47:34 by carce-bo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

void	free_four_ptrs(void *s1, void *s2, void *s3, void *s4)
{
	if (s1)
		free(s1);
	if (s2)
		free(s2);
	if (s3)
		free(s3);
	if (s4)
		free(s4);
}

void	free_three_ptrs(void *str1, void *str2, void *str3)
{
	if (str1)
		free(str1);
	if (str2)
		free(str2);
	if (str3)
		free(str3);
}

void	free_two_ptrs(void *s1, void *s2)
{
	if (s1)
		free(s1);
	if (s2)
		free(s2);
}

void	free_matrix(char **matrix)
{
	int	i;

	i = 0;
	if (!matrix)
		return ;
	else
	{
		while (matrix[i])
			free(matrix[i++]);
		free(matrix[i]);
		free(matrix);
	}
}
