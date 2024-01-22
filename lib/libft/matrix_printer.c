/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_printer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-estr <fda-estr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 20:43:12 by fda-estr          #+#    #+#             */
/*   Updated: 2024/01/22 11:56:04 by fda-estr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	matrix_printer(char **mtx)
{
	int		i;
	int		j;
	char	c;

	i = 0;
	c = '\n';
	while (mtx[i])
	{
		j = 0;
		while (mtx[i][j])
		{
			write(1, &mtx[i][j], 1);
			j++;
		}
		write(1, &c, 1);
		i++;
	}
}
