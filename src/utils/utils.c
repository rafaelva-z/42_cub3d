/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz <rvaz@student.42lisboa.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 16:16:32 by fda-estr          #+#    #+#             */
/*   Updated: 2024/02/17 12:30:36 by rvaz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

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

int	is_inside_map(t_point point, t_point map_size)
{
	if (point.x >= 0 && point.x < map_size.x
		&& point.y >= 0 && point.y < map_size.y)
		return (1);
	return (0);
}

int	is_wall(t_point point, t_data *data)
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
}
