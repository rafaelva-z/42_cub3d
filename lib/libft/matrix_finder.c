/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_finder.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-estr <fda-estr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 19:42:05 by fda-estr          #+#    #+#             */
/*   Updated: 2024/01/22 11:55:29 by fda-estr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	matrix_finder(char **mtx, char *s)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while (mtx[i])
	{
		n += str_finder(mtx[i], s);
		i++;
	}
	return (n);
}
