/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz <rvaz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 17:28:39 by rvaz              #+#    #+#             */
/*   Updated: 2024/01/25 18:00:59 by rvaz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	init_data(t_data *data)
{
	data->mlx = NULL;
	data->mlx_win = NULL;
	data->north_img = NULL;
	data->east_img = NULL;
	data->south_img = NULL;
	data->west_img = NULL;
	data->map.map = NULL;
	data->file = malloc(sizeof(t_file));
	if (!data->file)
		free_and_exit(data, ERR_MALLOC);
	data->file->file = NULL;
	data->file->north_file = NULL;
	data->file->east_file = NULL;
	data->file->south_file = NULL;
	data->file->west_file = NULL;
	data->file->floor_file = NULL;
	data->file->ceiling_file = NULL;
}

static void	init_mlx(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		free_and_exit(data, ERR_MLX_INIT);
	data->mlx_win = mlx_new_window(data->mlx, WIN_WIDTH, WIN_HEIGHT, "Cub3D");
	if (!data->mlx_win)
		free_and_exit(data, ERR_MLX_WIN);
}

void	initializer(t_data *data)
{
	init_data(data);
	init_mlx(data);
}
