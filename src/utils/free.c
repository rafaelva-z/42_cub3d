/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-estr <fda-estr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 17:32:59 by rvaz              #+#    #+#             */
/*   Updated: 2024/02/07 16:23:33 by fda-estr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	free_color_grid(int **grid)
{
	int i;

	i = -1;
	while (++i < 64)
		free (grid[i]);
	free (grid);
}

static void	free_data_aux(t_data *data)
{
	if (data->image.north_img.color_grid)
		free_color_grid(data->image.north_img.color_grid);
	if (data->image.east_img.color_grid)
		free_color_grid(data->image.east_img.color_grid);
	if (data->image.south_img.color_grid)
		free_color_grid(data->image.south_img.color_grid);
	if (data->image.west_img.color_grid)
		free_color_grid(data->image.west_img.color_grid);
}

void	free_data(t_data *data)
{
	if (!data)
		return ;
	if (data->file)
	{
		if (data->file->file)
			matrix_deleter(&data->file->file);
		free(data->file);
		data->file = NULL;
	}
	if (data->map.map)
		matrix_deleter(&data->map.map);
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
	if (data->mlx_win_mm)
		mlx_destroy_window(data->mlx_mm, data->mlx_win_mm);
	if (data->mlx_mm)
	{
		mlx_destroy_display(data->mlx_mm);
		free(data->mlx_mm);
	}
	free_data_aux(data);
}

static void destroy_images(t_data *data)
{
	if (data->image.north_img.img)
		mlx_destroy_image(data->mlx, data->image.north_img.img);
	if (data->image.east_img.img)
		mlx_destroy_image(data->mlx, data->image.east_img.img);
	if (data->image.south_img.img)
		mlx_destroy_image(data->mlx, data->image.south_img.img);
	if (data->image.west_img.img)
		mlx_destroy_image(data->mlx, data->image.west_img.img);
	if (data->image.mm_wall_img)
		mlx_destroy_image(data->mlx, data->image.mm_wall_img);
	if (data->image.mm_floor_img)
		mlx_destroy_image(data->mlx, data->image.mm_floor_img);
	if (data->image.mm_vacum_img)
		mlx_destroy_image(data->mlx, data->image.mm_vacum_img);
	if (data->image.frame_x)
		mlx_destroy_image(data->mlx, data->image.frame_x);
	if (data->image.frame_y)
		mlx_destroy_image(data->mlx, data->image.frame_y);
}

void	free_file(t_file *file)
{
	if (file->file)
		matrix_deleter(&file->file);
	free (file);
}

static void	delete_list(t_enemy *node)
{
	t_enemy *temp;

	while (node)
	{
		temp = node->next_enemy;
		free (node);
		node = temp;
	}
}

void	free_and_exit(t_data *data, char *msg, int exit_status)
{
	mlx_do_key_autorepeaton(data->mlx);
	if (msg)
		ft_putstr_fd(msg, 2);
	if (data)
	{
		destroy_images(data);
		delete_list(data->enemy_list);
		free_data(data);
	}
	exit(exit_status);
}
