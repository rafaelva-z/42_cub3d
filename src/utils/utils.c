/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz <rvaz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 16:16:32 by fda-estr          #+#    #+#             */
/*   Updated: 2024/01/25 17:33:28 by rvaz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/**
 * @brief rotates the given point around {0, 0} by "angle" degrees.
 * @note The angle is converted to radians in order to be used with the
 * cos/sin functions from the math.h lib
*/
void	rotate_point(t_2d_point *point, double angle)
{
	t_2d_point	rot;

	angle *= M_PI / 180;
	rot.x = point->x * cos(angle) - point->y * sin(angle);
	rot.y = point->y * cos(angle) + point->x * sin(angle);
	point->x = rot.x;
	point->y = rot.y;
}

int	coordinate_finder(char **mtx, char c, char axle)
{
	int	i;
	int	j;

	i = 0;
	while (mtx[i])
	{
		j = 0;
		while (mtx[i][j] && mtx[i][j] != c)
			j++;
		if (mtx[i][j] == c)
			break ;
		i++;
	}
	if (axle == 'x')
		return (j);
	else if (axle == 'y')
		return (i);
	else
		return (-1);
}
