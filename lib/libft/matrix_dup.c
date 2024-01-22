/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_dup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-estr <fda-estr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 18:47:06 by fda-estr          #+#    #+#             */
/*   Updated: 2024/01/22 11:54:57 by fda-estr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	copy(char **mtx, char **dup)
{
	int	i;
	int	j;

	i = 0;
	while (mtx[i])
	{
		j = 0;
		while (mtx[i][j])
		{
			dup[i][j] = mtx[i][j];
			j++;
		}
		i++;
	}
}

char	**matrix_dup(char **mtx)
{
	int		i;
	int		j;
	char	**dup;

	i = 0;
	while (mtx[i])
		i++;
	dup = malloc(sizeof(char *) * (i + 1));
	if (!dup)
		return (NULL);
	dup[i] = 0;
	i = 0;
	while (mtx[i])
	{
		j = 0;
		while (mtx[i][j])
			j++;
		dup[i] = malloc(sizeof(char *) * (j + 1));
		if (!dup[i])
			return (NULL);
		dup[i][j] = 0;
		i++;
	}
	copy(mtx, dup);
	return (dup);
}
