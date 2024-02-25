/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz <rvaz@student.42lisboa.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 14:57:49 by rvaz              #+#    #+#             */
/*   Updated: 2024/02/25 14:22:44 by rvaz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	is_inside_map(t_point point, t_point map_size)
{
	if (point.x >= 0 && point.x < map_size.x
		&& point.y >= 0 && point.y < map_size.y)
		return (1);
	return (0);
}

int	is_player(t_point point, t_data *data)
{
	if ((int)point.y == (int)data->player.pos.y
		&& (int)point.x == (int)data->player.pos.x)
		return (-1);
	return (0);
}

int	is_wall(t_point point, t_data *data)
{
	if (data->map.map[(int)point.y][(int)point.x] == '1')
		return (1);
	return (0);
}

int	is_door(t_point current, t_data *data)
{
	if (data->map.map[(int)current.y][(int)current.x] == MAP_DOOR)
		return (D_CLOSED);
	else if (data->map.map[(int)current.y][(int)current.x] == MAP_MOVING_DOOR)
		return (D_MOVING);
	else if (data->map.map[(int)current.y][(int)current.x] == MAP_OPEN_DOOR)
		return (D_OPEN);
	return (0);
}
