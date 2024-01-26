/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-estr <fda-estr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 18:34:12 by fda-estr          #+#    #+#             */
/*   Updated: 2024/01/25 21:31:23 by rvaz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"


static void	dir_init(t_data *data, char c)
{
	if (c == 'N')
		data->player.dir = (t_2d_point){0, -1};
	else if (c == 'S')
		data->player.dir = (t_2d_point){0, 1};
	else if (c == 'W')
		data->player.dir = (t_2d_point){-1, 0};
	else if (c == 'E')
		data->player.dir = (t_2d_point){1, 0};
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
			if (data->map.map[i][j] == 'N' || data->map.map[i][j] == 'S'
				|| data->map.map[i][j] == 'W' || data->map.map[i][j] == 'E')
			{
				c = data->map.map[i][j];
				break ;
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
