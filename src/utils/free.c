/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-estr <fda-estr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 17:32:59 by rvaz              #+#    #+#             */
/*   Updated: 2024/02/10 17:46:43 by fda-estr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	free_color_grid(t_img *img)
{
	int i;

	i = -1;
	while (++i < img->columns_created)
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
		printf("texture pointer[%d]: %p\n", i, data->textures[i]);
		if (data->textures[i]->img)
			mlx_destroy_image(data->mlx, data->textures[i]->img);
		free (data->textures[i]);
	}
		free (data->textures);
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
	if (data->map.minimap)
		matrix_deleter(&data->map.minimap);
	if (data->img)
	{
		mlx_destroy_image(data->mlx, data->img->img);
		free(data->img);
	}
	if (data->mlx_win_mm)
		mlx_destroy_window(data->mlx, data->mlx_win_mm);
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
	mlx_mouse_show(data->mlx, data->mlx_win);
	if (msg)
		ft_putstr_fd(msg, 2);
	if (data)
	{
		delete_list(data->enemy_list);
		free_textures(data);
		free_data(data);
	}
	exit(exit_status);
}
