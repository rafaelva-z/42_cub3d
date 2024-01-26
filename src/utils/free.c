/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz <rvaz@student.42lisboa.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 17:32:59 by rvaz              #+#    #+#             */
/*   Updated: 2024/01/26 00:27:31 by rvaz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	free_data(t_data *data)
{
	if (!data)
		return ;
	if (data->file)
	{
		if (data->file->file)
			matrix_deleter(&data->file->file);
		free (data->file);
	}
	if (data->map.map)
		matrix_deleter(&data->map.map);
	if (data->mlx_win)
		mlx_destroy_window(data->mlx, data->mlx_win);
	if (data->mlx)
		free(data->mlx);
}

void	free_and_exit(t_data *data, char *msg, int exit_status)
{
	if (msg)
		ft_putstr_fd(msg, 2);
	if (data)
		free_data(data);
	exit(exit_status);
}
