/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz <rvaz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 17:28:39 by rvaz              #+#    #+#             */
/*   Updated: 2024/03/18 17:37:17 by rvaz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	init_data(t_data *data)
{
	data->mlx = NULL;
	data->mlx_win = NULL;
	data->map.map = NULL;
	data->map.minimap = NULL;
	data->start_time = get_timestamp(data);
	data->sprites = NULL;
	data->sprt_order = NULL;
	texture_array_init(data);
	data->next_frame = 0;
	data->ceiling_colour = -1;
	data->floor_colour = -1;
	data->z_buffer = NULL;
	data->file = malloc(sizeof(t_file));
	if (!data->file)
		free_and_exit(data, ERR_MALLOC, 1);
	data->file->file = NULL;
	data->file->north_file = NULL;
	data->file->east_file = NULL;
	data->file->south_file = NULL;
	data->file->west_file = NULL;
	data->file->floor_file = NULL;
	data->file->ceiling_file = NULL;
	data->z_buffer = calloc(WIN_WIDTH, sizeof(double));
	if (!data->z_buffer)
		free_and_exit(data, ERR_MALLOC, 1);
}

static void	init_mlx(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		free_and_exit(data, ERR_MLX_INIT, 1);
	data->mlx_win = mlx_new_window(data->mlx, WIN_WIDTH, WIN_HEIGHT, WIN_TITLE);
	if (!data->mlx_win)
		free_and_exit(data, ERR_MLX_WIN, 1);
	data->img = malloc(sizeof(t_img));
	if (!data->img)
		free_and_exit(data, ERR_MALLOC, 1);
	data->img->img = mlx_new_image(data->mlx, WIN_WIDTH, WIN_HEIGHT);
	data->img->addr = mlx_get_data_addr(data->img->img,
			&(data->img->bits_per_pixel), &(data->img->line_length),
			&(data->img->endian));
	mlx_do_key_autorepeatoff(data->mlx);
}

static void	init_player(t_data *data)
{
	data->player.fov = START_FOV;
	data->player.vertical = 0;
	data->player.actions = 0;
	data->player.mov_dir = (t_point){0, 0};
	data->player.mouse_toggle = 1;
}

void	initializer(t_data *data)
{
	init_data(data);
	init_mlx(data);
	init_player(data);
}
