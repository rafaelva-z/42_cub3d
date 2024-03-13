/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz <rvaz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 23:05:31 by fda-estr          #+#    #+#             */
/*   Updated: 2024/03/13 19:27:29 by rvaz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static char	*identifier_skipper(t_data *data, char *s)
{
	char	*prod;
	int		i;

	i = -1;
	prod = s;
	while (*prod && *prod != ' ')
		prod++;
	while (*prod && *prod == ' ')
		prod++;
	if (!(*prod))
		free_and_exit(data, "Error: invalid identifier\n", 1);
	while (prod[++i])
	{
		if (prod[i] == ' ')
			free_and_exit(data, "Error: invalid identifier\n", 1);
	}
	return (prod);
}

void	identifier_init(t_data *dt)
{
	int	i;

	i = -1;
	while (++i < 6)
	{
		if (!ft_strncmp(dt->file->file[i], "NO ", 3))
			dt->file->north_file = identifier_skipper(dt, dt->file->file[i]);
		else if (!ft_strncmp(dt->file->file[i], "SO ", 3))
			dt->file->south_file = identifier_skipper(dt, dt->file->file[i]);
		else if (!ft_strncmp(dt->file->file[i], "WE ", 3))
			dt->file->west_file = identifier_skipper(dt, dt->file->file[i]);
		else if (!ft_strncmp(dt->file->file[i], "EA ", 3))
			dt->file->east_file = identifier_skipper(dt, dt->file->file[i]);
		else if (!ft_strncmp(dt->file->file[i], "F ", 2))
			dt->file->floor_file = identifier_skipper(dt, dt->file->file[i]);
		else if (!ft_strncmp(dt->file->file[i], "C ", 2))
			dt->file->ceiling_file = identifier_skipper(dt, dt->file->file[i]);
		else
			free_and_exit(dt, "Error: Invalid identifier\n", 1);
	}
	if (!dt->file->ceiling_file || !dt->file->floor_file
		|| !dt->file->west_file || !dt->file->north_file
		|| !dt->file->east_file || !dt->file->south_file)
		free_and_exit(dt, "Error: Doubled identifier\n", 1);
}

static int	colour_parsing(t_data *data, char *str)
{
	char	**colour_char;
	int		r;
	int		g;
	int		b;

	colour_char = ft_split(str, ',');
	if (!colour_char)
		free_and_exit(data, ERR_MALLOC, 1);
	if (matrix_sizer(colour_char, 'h') != 3)
	{
		matrix_deleter(&colour_char);
		free_and_exit(data, ERR_MAP, 1);
	}
	r = ft_atoi(colour_char[0]);
	g = ft_atoi(colour_char[1]);
	b = ft_atoi(colour_char[2]);
	matrix_deleter(&colour_char);
	if (r > 255 || g > 255 || b > 255)
		free_and_exit(data, ERR_MAP, 1);
	return ((r << 16) + (g << 8) + b);
}

void	ceiling_floor_init(t_data *data)
{
	if ((int)ft_strlen(data->file->ceiling_file)
		!= str_finder(data->file->ceiling_file, "1234567890,"))
		image_init(data, data->textures[C_IMG], data->file->ceiling_file);
	else
		data->ceiling_colour = colour_parsing(data, data->file->ceiling_file);
	if ((int)ft_strlen(data->file->floor_file)
		!= str_finder(data->file->floor_file, "1234567890,"))
		image_init(data, data->textures[F_IMG], data->file->floor_file);
	else
		data->floor_colour = colour_parsing(data, data->file->floor_file);
}
