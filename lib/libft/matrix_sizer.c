/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_sizer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-estr <fda-estr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 20:36:42 by fda-estr          #+#    #+#             */
/*   Updated: 2024/01/22 15:12:59 by fda-estr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*Only workes with rectangular matrixes appart from c (character count)*/
/*d = the dimention [Height (h) width(w) area (a)]*/

static int character_count(char **mtx)
{
	int	i;
	int	j;
	int	count;

	i = -1;
	count = 0;
	while (mtx[++i])
	{
		j = -1;
		while (mtx[i][++j])
			count++;
	}
	return (count);
}

static int	max_width(char **mtx)
{
	int	i;
	int	len;
	int	max_len;

	i = -1;
	max_len = 0;
	while (mtx[++i])
	{
		len = ft_strlen(mtx[i]);
		if (len > max_len)
			max_len = len;
	}
	return (max_len);
}

int	matrix_sizer(char **mtx, char d)
{
	int	h;
	int	w;

	h = 0;
	while (mtx[h])
		h++;
	w = max_width(mtx);
	if (d == 'h' || d == 'H')
		return (h);
	else if (d == 'w' || d == 'W')
		return (w);
	else if (d == 'a' || d == 'A')
		return (h * w);
	else if (d == 'c' || d == 'C')
		return (character_count(mtx));
	else
		return (0);
}
