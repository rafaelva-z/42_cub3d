/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-estr <fda-estr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 23:05:31 by fda-estr          #+#    #+#             */
/*   Updated: 2024/01/22 00:10:53 by fda-estr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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
	{
		printf("Error: invalid identifier\n");		//	Error handling
		matrix_deleter (&data->file->file);
		exit (1);
	}
	while (prod[++i])
	{
		if (prod[i] == ' ')
		{
			printf("Error: invalid identifier\n");		//	Error handling
			matrix_deleter (&data->file->file);
			exit (1);
		}
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
		{
			printf("Invalid identifier\n");				//	Error handling
			matrix_deleter (&dt->file->file);
			exit (1);
		}
	}
	if (!dt->file->ceiling_file || !dt->file->floor_file
			|| !dt->file->west_file || !dt->file->north_file
			|| !dt->file->east_file || !dt->file->south_file)
	{
		printf("Error: Doubled identifier\n");
		matrix_deleter (&dt->file->file);
		exit (1);
	}
}
