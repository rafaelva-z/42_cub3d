/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz <rvaz@student.42lisboa.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 02:32:24 by fda-estr          #+#    #+#             */
/*   Updated: 2024/01/26 02:06:00 by rvaz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_free(char const *s1, char const *s2, int tofree)
{
	char	*sj;
	size_t	s1len;
	size_t	s2len;

	if (!s1)
		return ((char *)s2);
	if (!s2)
		return ((char *)s1);
	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	sj = malloc(sizeof(char) * (s1len + s2len + 1));
	if (!sj)
		return (NULL);
	if (s1)
		ft_strlcpy(sj, s1, s1len + 1);
	if (s2)
		ft_strlcat(sj, s2, (s1len + s2len + 1));
	if (s1 && (tofree == 1 || tofree == 3))
		free((char *) s1);
	if (s2 && (tofree == 2 || tofree == 3))
		free((char *) s2);
	return (sj);
}
