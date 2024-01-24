/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz <rvaz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 16:16:32 by fda-estr          #+#    #+#             */
/*   Updated: 2024/01/24 17:14:20 by rvaz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	initializer(t_data *data)
{
	data->mlx = NULL;
	data->mlx_win = NULL;
	data->north_img = NULL;
	data->east_img = NULL;
	data->south_img = NULL;
	data->west_img = NULL;
	data->map = NULL;
	data->player = NULL;
	data->file = malloc(sizeof(t_file));
	if (!data->file)
		return ;		//	Error handler
	data->file->file = NULL;
	data->file->north_file = NULL;
	data->file->east_file = NULL;
	data->file->south_file = NULL;
	data->file->west_file = NULL;
	data->file->floor_file = NULL;
	data->file->ceiling_file = NULL;
}

void	free_and_exit(t_data *data, char *msg)
{
	if (msg)
		ft_putstr_fd(msg, 2);
	if (data->file)
	{
		if (data->file->file)
			matrix_deleter(&data->file->file);
		free (data->file);
	}
	if (data->player)
		free (data->player);
	exit (0);
}

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