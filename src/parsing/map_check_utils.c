/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-estr <fda-estr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 18:34:12 by fda-estr          #+#    #+#             */
/*   Updated: 2024/02/26 13:32:00 by fda-estr         ###   ########.fr       */
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
		data->player.plane = (t_point){-1 * (double) START_FOV / 100, 0};
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

void	map_and_player_init(t_data *data, int i, int j)
{
	char	c;

	i = -1;
	while (data->map.map[++i])
	{
		j = -1;
		while (data->map.map[i][++j])
		{
			if (data->map.map[i][j] == MAP_PLAYER_NORTH
					|| data->map.map[i][j] == MAP_PLAYER_SOUTH
					|| data->map.map[i][j] == MAP_PLAYER_WEST
					|| data->map.map[i][j] == MAP_PLAYER_EAST)
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

char	*str_duplicator(char *prod, int len, t_data *data)
{
	char	*temp;
	int		i;

	temp = ft_calloc(sizeof(char), len + 1);
	if (!temp)
		free_and_exit(data, ERR_MALLOC, 1);
	ft_strlcpy(temp, prod, ft_strlen(prod) + 1);
	i = -1;
	while (temp[++i])
		;
	while (i < len)
		temp[i++] = ' ';
	free(prod);
	return (temp);
}

char	**map_dup(char **map, t_data *data)
{
	char	**prod;
	int		len;
	int		i;

	prod = matrix_dup(map);
	if (!prod)
		free_and_exit(data, ERR_MALLOC, 1);
	len = matrix_sizer(prod, 'w');
	i = -1;
	while (prod[++i])
		prod[i] = str_duplicator(prod[i], len, data);
	return (prod);
}

void	minimap_negative(char **minimap)
{
	int	i;
	int	j;

	i = -1;
	while (minimap[++i])
	{
		j = -1;
		while (minimap[i][++j])
		{
			if (minimap[i][j] != '1' && minimap[i][j] != ' ')
				minimap[i][j] = '0' * -1;
			else
				minimap[i][j] *= -1;
		}
	}
}
