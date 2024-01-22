/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-estr <fda-estr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 12:03:00 by fda-estr          #+#    #+#             */
/*   Updated: 2024/01/22 21:51:28 by fda-estr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	character_check(t_data *data)
{
	int	size;

	size = matrix_sizer(data->map, 'c');
	if (size != matrix_finder(data->map, "10 NSEW"))
		free_and_exit(data, "Map Error: invalid character\n");
	if (matrix_finder(data->map, "NSEW") != 1)
		free_and_exit(data, "Map Error: invalid starting coordinate\n");
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
	free (prod);
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
	char	**dup;
	int		i;
	int		j;
	int		flag;

	i = 0;
	flag = 0;
	dup = map_dup(data->map);
	while (dup[++i + 1] && flag == 0)
	{
		j = -1;
		while (dup[i][++j] && flag == 0)
		{
			if (dup[i][j] == '1' || dup[i][j] == ' ')
				continue ;
			if (neighbors_check(dup, i, j))
				flag = 1;
		}
	}
	if (flag == 1 || str_finder(dup[0], "0NSEW") || str_finder(dup[i], "0NSEW"))
	{
		matrix_deleter(&dup);
		free_and_exit(data, "Error: invalid map borders\n");
	}
	matrix_deleter(&dup);
}

void	map_check(t_data *data)
{
	int	i;

	i = -1;
	data->map = data->file->file + 6;
	character_check(data);
	borther_check(data);
	while (data->map[++i])
		if (!str_finder(data->map[i], "1"))
			free_and_exit(data, "Error: Map cannot contain empty lines\n");
}
