/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz <rvaz@student.42lisboa.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 13:05:35 by rvaz              #+#    #+#             */
/*   Updated: 2024/02/15 10:36:59 by rvaz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/**
 * @brief	returns the sum of two points.
*/
t_point	vector_add(t_point v1, t_point v2)
{
	return ((t_point){v1.x + v2.x, v1.y + v2.y});
}
/**
 * @brief	normalizes the given vector.
*/
void	vector_norm(t_point *vector)
{
	double	length;

	if (vector->x == 0 && vector->y == 0)
		return ;
	length = sqrt((vector->x * vector->x) + (vector->y * vector->y));
	vector->x /= length;
	vector->y /= length;
}

/**
 * @brief	rotates the given point around {0, 0} by "angle" degrees.
 * @note	The angle is converted to radians in order to be used with the
 *			cos/sin functions from the math.h lib
*/
void	rotate_point(t_point *point, double angle)
{
	t_point	rot;

	if (angle == 0)
		return ;
	angle *= M_PI / 180;
	rot.x = point->x * cos(angle) - point->y * sin(angle);
	rot.y = point->y * cos(angle) + point->x * sin(angle);
	point->x = rot.x;
	point->y = rot.y;
}

/**
 * @brief	rotates the given point around {0, 0} by "angle" degrees and
 * 			returns the result.
*/
t_point	vector_rotate(t_point point, double angle)
{
	t_point	rot;

	if (angle == 0)
		return (point);
	angle *= M_PI / 180;
	rot.x = point.x * cos(angle) - point.y * sin(angle);
	rot.y = point.y * cos(angle) + point.x * sin(angle);
	return (rot);
}