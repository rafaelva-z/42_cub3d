/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz <rvaz@student.42lisboa.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 18:34:12 by fda-estr          #+#    #+#             */
/*   Updated: 2024/02/21 12:47:35 by rvaz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	dir_init(t_data *data, char c)
{
	if (c == MAP_PLAYER_NORTH)
	{
		data->player.dir = (t_point){0, -1};
		data->player.plane = (t_point){(double)START_FOV / 100, 0};
	}
	else if (c == MAP_PLAYER_SOUTH)
	{
		data->player.dir = (t_point){0, 1};
		data->player.plane = (t_point){-(double)START_FOV / 100, 0};
	}
	else if (c == MAP_PLAYER_WEST)
	{
		data->player.dir = (t_point){-1, 0};
		data->player.plane = (t_point){0, -(double)START_FOV / 100};
	}
	else if (c == MAP_PLAYER_EAST)
	{
		data->player.dir = (t_point){1, 0};
		data->player.plane = (t_point){0, (double)START_FOV / 100};
	}
}

void	map_and_player_init(t_data *data)
{
	char	c;
	int		i;
	int		j;

	i = -1;
	while (data->map.map[++i])
	{
		j = -1;
		while (data->map.map[i][++j])
		{
			// THIS IF CAN BE MADE BETTER BY COMPARING TO A STRING "NSEW"
			if (data->map.map[i][j] == MAP_PLAYER_NORTH || data->map.map[i][j] == MAP_PLAYER_SOUTH
				|| data->map.map[i][j] == MAP_PLAYER_WEST || data->map.map[i][j] == MAP_PLAYER_EAST)
			{
				c = data->map.map[i][j];
				break ;
			}
		}
	}
	data->map.size.x = matrix_sizer(data->map.map, 'w');
	data->map.size.y = matrix_sizer(data->map.map, 'h');
	data->player.pos.x = coordinate_finder(data->map.map, c, 'x') + 0.5;
	data->player.pos.y = coordinate_finder(data->map.map, c, 'y') + 0.5;
	dir_init(data, c);
	data->map.map[coordinate_finder(data->map.map, c, 'y')]
		[coordinate_finder(data->map.map, c, 'x')] = '0';
}
