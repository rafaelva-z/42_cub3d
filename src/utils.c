/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-estr <fda-estr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 16:16:32 by fda-estr          #+#    #+#             */
/*   Updated: 2024/01/22 20:26:10 by fda-estr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"



void	initializer(t_data *data)
{
	data->mlx = NULL;
	data->mlx_win = NULL;
	data->north_img = NULL;
	data->east_img = NULL;
	data->south_img = NULL;
	data->west_img = NULL;
	data->map = NULL;
	data->player = NULL;
	data->file = malloc(sizeof(t_file));
	if (!data->file)
		return ;		//	Error handler
	data->file->file = NULL;
	data->file->north_file = NULL;
	data->file->east_file = NULL;
	data->file->south_file = NULL;
	data->file->west_file = NULL;
	data->file->floor_file = NULL;
	data->file->ceiling_file = NULL;
}

void	free_and_exit(t_data *data, char *msg)
{
	if (msg)
		ft_putstr_fd(msg, 2);
	if (data->file)
	{
		if (data->file->file)
			matrix_deleter(&data->file->file);
		free (data->file);
	}
	if (data->player)
		free (data->player);
	exit (0);
}
