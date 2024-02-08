/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz <rvaz@student.42lisboa.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 17:28:39 by rvaz              #+#    #+#             */
/*   Updated: 2024/02/08 13:09:17 by rvaz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	init_data(t_data *data)
{
	data->mlx = NULL;
	data->mlx_win = NULL;
	data->image.north_img.img = NULL;
	data->image.north_img.addr = NULL;
	data->image.north_img.color_grid = NULL;
	data->image.east_img.img = NULL;
	data->image.east_img.addr = NULL;
	data->image.east_img.color_grid = NULL;
	data->image.south_img.img = NULL;
	data->image.south_img.addr = NULL;
	data->image.south_img.color_grid = NULL;
	data->image.west_img.img = NULL;
	data->image.west_img.addr = NULL;
	data->image.west_img.color_grid = NULL;
	data->map.map = NULL;
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
	begining_time_stamp(data);
	data->enemy_indx = 0;
}

static void	init_mlx_minimap(t_data *data)
{
	int	size;
	int	size2;

	size = 32;
	size2 = 320;
	data->mlx_win_mm = mlx_new_window(data->mlx, 352, 352, "test");
	data->image.mm_floor_img = mlx_xpm_file_to_image(data->mlx, "./textures/minimap/mm_floor.xpm", &size, &size);
	data->image.mm_vacum_img = mlx_xpm_file_to_image(data->mlx, "./textures/minimap/mm_vacum.xpm", &size2, &size2);
	data->image.mm_wall_img = mlx_xpm_file_to_image(data->mlx, "./textures/minimap/mm_wall.xpm", &size, &size);
	size2 = 352;
	data->image.frame_x = mlx_xpm_file_to_image(data->mlx, "./textures/minimap/frame_x.xpm", &size2, &size);
	data->image.frame_y = mlx_xpm_file_to_image(data->mlx, "./textures/minimap/frame_y.xpm", &size, &size2);
}

static void	init_mlx(t_data *data)
{
	data->mlx = mlx_init();
	init_mlx_minimap(data);
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
	data->player.move = 0;
	data->player.move_cam = 0;
	data->player.mouse = (t_2d_point){0, 0};
	data->player.mov_dir = (t_2d_point){0, 0};
	data->player.mouse_toggle = 1;
}

void	initializer(t_data *data)
{
	init_data(data);
	init_mlx(data);
	init_player(data);
	data->enemy_list = NULL;
}
