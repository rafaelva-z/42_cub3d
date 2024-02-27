/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-estr <fda-estr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 12:03:00 by fda-estr          #+#    #+#             */
/*   Updated: 2024/02/26 13:31:00 by fda-estr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	character_check(t_data *data)
{
	int	size;

	size = matrix_sizer(data->map.map, 'c');
	if (size != matrix_finder(data->map.map, "10 NSEWDM"))
		free_and_exit(data, ERR_INV_CHAR, 1);
	if (matrix_finder(data->map.map, "NSEW") != 1)
		free_and_exit(data, ERR_STR_POS, 1);
}

static int	neighbors_check(char **map, int i, int j)
{
	if (j == 0 || map[i + 1][j] == ' ' || map[i - 1][j] == ' '
			|| map[i][j + 1] == ' ' || map[i][j - 1] == ' '
			|| map[i + 1][j] == 0 || map[i - 1][j] == 0 || map[i][j + 1] == 0
			|| map[i][j - 1] == 0)
		return (1);
	return (0);
}

void	borther_check(t_data *data)
{
	int		i;
	int		j;
	int		flag;

	i = 0;
	flag = 0;
	while (data->map.map[++i + 1] && flag == 0)
	{
		j = -1;
		while (data->map.map[i][++j] && flag == 0)
		{
			if (data->map.map[i][j] == '1' || data->map.map[i][j] == ' ')
				continue ;
			if (neighbors_check(data->map.map, i, j))
				flag = 1;
		}
	}
	if (flag == 1 || str_finder(data->map.map[0], "0NSWEM")
		|| str_finder(data->map.map[i], "0SEWNM"))
		free_and_exit(data, ERR_BORD, 1);
}

static void	door_check(t_data *data)
{
	int		i;
	int		j;
	char	**map;

	i = -1;
	map = data->map.map;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] != 'D')
				continue ;
			if (map[i + 1][j] == '1' && map[i - 1][j] == '1'
					&& map[i][j + 1] != '1' && map[i][j - 1] != '1')
				continue ;
			if (map[i + 1][j] != '1' && map[i - 1][j] != '1'
					&& map[i][j + 1] == '1' && map[i][j - 1] == '1')
				continue ;
			free_and_exit(data, ERR_DOOR, 1);
		}
	}
}

void	map_check(t_data *data)
{
	int	i;

	i = -1;
	data->map.map = map_dup(data->file->file + 6, data);
	if (!data->map.map)
		free_and_exit(data, ERR_MALLOC, 1);
	data->map.minimap = map_dup(data->file->file + 6, data);
	if (!data->map.map)
		free_and_exit(data, ERR_MALLOC, 1);
	minimap_negative(data->map.minimap);
	character_check(data);
	borther_check(data);
	door_check(data);
	while (data->map.map[++i])
		if (!str_finder(data->map.map[i], "1"))
			free_and_exit(data, ERR_LINES, 1);
	map_and_player_init(data, 0, 0);
}
