/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz <rvaz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 17:32:59 by rvaz              #+#    #+#             */
/*   Updated: 2024/03/18 16:37:58 by rvaz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	free_color_grid(t_img *img)
{
	int	i;

	i = -1;
	while (++i < img->width)
		free (img->color_grid[i]);
	free (img->color_grid);
}

static void	free_textures(t_data *data)
{
	int	i;

	if (!data->textures)
		return ;
	i = -1;
	while (++i < 44)
	{
		if (!data->textures[i])
			continue ;
		if (data->textures[i]->color_grid)
			free_color_grid(data->textures[i]);
		if (data->textures[i]->img)
			mlx_destroy_image(data->mlx, data->textures[i]->img);
		free(data->textures[i]);
	}
	free(data->textures);
}

void	free_data(t_data *data)
{
	if (data->z_buffer)
		free (data->z_buffer);
	if (data->file)
	{
		if (data->file->file)
			matrix_deleter(&data->file->file);
		free(data->file);
		data->file = NULL;
	}
	if (data->map.map)
		matrix_deleter(&data->map.map);
	if (data->map.minimap)
		matrix_deleter(&data->map.minimap);
	if (data->img)
	{
		mlx_destroy_image(data->mlx, data->img->img);
		free(data->img);
	}
	if (data->mlx_win)
		mlx_destroy_window(data->mlx, data->mlx_win);
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
}

void	free_file(t_file *file)
{
	if (file->file)
		matrix_deleter(&file->file);
	free (file);
}

void	free_sprites(t_data *data)
{
	if (data->sprites)
		free(data->sprites);
	if (data->sprt_order)
		free(data->sprt_order);
}

void	free_and_exit(t_data *data, char *msg, int exit_status)
{
	mlx_do_key_autorepeaton(data->mlx);
	mlx_mouse_show(data->mlx, data->mlx_win);
	if (msg)
		ft_putstr_fd(msg, 2);
	if (data)
	{
		free_textures(data);
		free_data(data);
		free_sprites(data);
	}
	exit(exit_status);
}
