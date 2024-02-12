/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-estr <fda-estr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 12:03:00 by fda-estr          #+#    #+#             */
/*   Updated: 2024/02/10 23:37:00 by fda-estr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	character_check(t_data *data)
{
	int	size;

	size = matrix_sizer(data->map.map, 'c');
	if (size != matrix_finder(data->map.map, "10 NSEWDM"))
		free_and_exit(data, "cub3d: Map Error: invalid character\n", 1);
	if (matrix_finder(data->map.map, "NSEW") != 1)
		free_and_exit(data, "cub3d: Map Error: invalid starting coordinate\n", 1);
}

static char *str_duplicator(char *prod, int len)
{
	char	*temp;
	int		i;

	temp = ft_calloc(sizeof(char), len + 1);
	if (!temp)
		return (NULL);								//	Error handling
	ft_strlcpy(temp, prod, ft_strlen(prod) + 1);
	i = -1;
	while (temp[++i])
		;
	while (i < len)
		temp[i++] = ' ';
	free(prod);
	return (temp);
}

static char	**map_dup(char **map)
{
	char	**prod;
	int		len;
	int		i;

	prod = matrix_dup(map);
	len = matrix_sizer(prod, 'w');
	i = -1;
	while (prod[++i])
		prod[i] = str_duplicator(prod[i], len);
	return (prod);
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
		free_and_exit(data, "cub3d: Error: invalid map borders\n", 1);
}

static void	minimap_negative(char **minimap)
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

void	map_check(t_data *data)
{
	int	i;

	i = -1;
	data->map.map = map_dup(data->file->file + 6);
	if (!data->map.map)
		free_and_exit(data, ERR_MALLOC, 1);
	data->map.minimap = map_dup(data->file->file + 6);
	if (!data->map.map)
		free_and_exit(data, ERR_MALLOC, 1);
	minimap_negative(data->map.minimap);
	character_check(data);
	borther_check(data);
	while (data->map.map[++i])
		if (!str_finder(data->map.map[i], "1"))
			free_and_exit(data, "cub3d: Error: Map cannot contain empty lines\n", 1);
	map_and_player_init(data);
}
