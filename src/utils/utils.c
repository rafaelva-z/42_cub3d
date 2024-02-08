/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz <rvaz@student.42lisboa.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 16:16:32 by fda-estr          #+#    #+#             */
/*   Updated: 2024/02/08 13:06:16 by rvaz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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

void	begining_time_stamp(t_data *data)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) < 0)
		free_and_exit(data, ERR_TIME, 1);
	data->start_time = (time.tv_sec * 1000) + (time.tv_usec / 1000);
}

uint64_t	time_stamp(t_data *data)
{
	struct timeval time;

	if (gettimeofday(&time, NULL) < 0)
		free_and_exit(data, ERR_TIME, 1);
	return((time.tv_sec * 1000) + (time.tv_usec / 1000) - data->start_time);
}
