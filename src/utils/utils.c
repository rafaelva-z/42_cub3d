/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz <rvaz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 16:16:32 by fda-estr          #+#    #+#             */
/*   Updated: 2024/02/07 12:51:12 by rvaz             ###   ########.fr       */
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

	if (angle == 0)
		return ;
	angle *= M_PI / 180;
	rot.x = point->x * cos(angle) - point->y * sin(angle);
	rot.y = point->y * cos(angle) + point->x * sin(angle);
	point->x = rot.x;
	point->y = rot.y;
}

t_2d_point	vector_rotate(t_2d_point point, double angle)
{
	t_2d_point	rot;

	if (angle == 0)
		return (point);
	angle *= M_PI / 180;
	rot.x = point.x * cos(angle) - point.y * sin(angle);
	rot.y = point.y * cos(angle) + point.x * sin(angle);
	return (rot);
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

int	display_error(char *str)
{
	ft_putstr_fd(str, 2);
	return (1);
}

int	is_inside_map(t_2d_point point, t_2d_point map_size)
{
	if (point.x >= 0 && point.x < map_size.x
		&& point.y >= 0 && point.y < map_size.y)
		return (1);
	return (0);
}

int	is_wall(t_2d_point point, t_data *data)
{
	if (data->map.map[(int)point.y][(int)point.x] == '1')
		return (1);
	return (0);
}

void	update_view(t_data *data)
{
	raycast(data);
	minimap(data);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img->img, 0, 0);
	mlx_do_sync(data->mlx);
}

t_2d_point	vector_add(t_2d_point v1, t_2d_point v2)
{
	return ((t_2d_point){v1.x + v2.x, v1.y + v2.y});
}

void	vector_norm(t_2d_point *vector)
{
	double length;

	length = sqrt((vector->x * vector->x) + (vector->y * vector->y));
	vector->x /= length;
	vector->y /= length;
	
}
