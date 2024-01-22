/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_finder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-estr <fda-estr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 19:39:36 by fda-estr          #+#    #+#             */
/*   Updated: 2024/01/22 11:59:50 by fda-estr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*New protection: if the string c contains repeted characters*/

#include "libft.h"

int	str_finder(char *s, char *c)
{
	int	i;
	int	j;
	int	n;

	i = 0;
	n = 0;
	if (!s || !c)
		return (0);
	while (s[i])
	{
		j = 0;
		while (c[j])
		{
			if (s[i] == c[j])
				n++;
			j++;
		}
		i++;
	}
	return (n);
}
