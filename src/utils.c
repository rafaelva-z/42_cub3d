/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz <rvaz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 16:16:32 by fda-estr          #+#    #+#             */
/*   Updated: 2024/01/25 15:30:44 by rvaz             ###   ########.fr       */
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
	data->map.map = NULL;
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

void	free_data(t_data *data)
{
	if (!data)
		return ;
	if (data->file)
	{
		if (data->file->file)
			matrix_deleter(&data->file->file);
		free (data->file);
	}
	if (data->map.map)
		matrix_deleter(&data->map.map);
	if (data->mlx_win)
		mlx_destroy_window(data->mlx, data->mlx_win);
	if (data->mlx)
		free(data->mlx);
}

void	free_and_exit(t_data *data, char *msg)
{
	if (msg)
		ft_putstr_fd(msg, 2);
	if (data)
		free_data(data);
	exit(0);
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
