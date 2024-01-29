/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz <rvaz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 17:28:39 by rvaz              #+#    #+#             */
/*   Updated: 2024/01/29 16:26:07 by rvaz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	init_data(t_data *data)
{
	data->mlx = NULL;
	data->mlx_win = NULL;
	data->ig.north_img = NULL;
	data->ig.east_img = NULL;
	data->ig.south_img = NULL;
	data->ig.west_img = NULL;
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
}

static void	init_mlx_minimap(t_data *data)
{
	int size;
	int size2;


	size = 32;
	size2 = 320;
	data->mlx_mm = mlx_init();			//	ONLY FOR TESTING
	data->mlx_win_mm = mlx_new_window(data->mlx_mm, 352, 352, "test");
	data->ig.mm_floor_img = mlx_xpm_file_to_image(data->mlx_mm, "./textures/minimap/mm_floor.xpm", &size, &size);
	data->ig.mm_vacum_img = mlx_xpm_file_to_image(data->mlx_mm, "./textures/minimap/mm_vacum.xpm", &size2, &size2);
	data->ig.mm_wall_img = mlx_xpm_file_to_image(data->mlx_mm, "./textures/minimap/mm_wall.xpm", &size, &size);
	size2 = 352;
	data->ig.frame_x = mlx_xpm_file_to_image(data->mlx_mm, "./textures/minimap/frame_x.xpm", &size2, &size);
	data->ig.frame_y = mlx_xpm_file_to_image(data->mlx_mm, "./textures/minimap/frame_y.xpm", &size, &size2);
}

static void	init_mlx(t_data *data)
{
	data->mlx = mlx_init();
	init_mlx_minimap(data);
	if (!data->mlx)
		free_and_exit(data, ERR_MLX_INIT, 1);
	data->mlx_win = mlx_new_window(data->mlx, WIN_WIDTH, WIN_HEIGHT, "Cub3D - fda-est & rvaz");
	if (!data->mlx_win)
		free_and_exit(data, ERR_MLX_WIN, 1);
	data->img = malloc(sizeof(t_img));
	if (!data->img)
		free_and_exit(data, ERR_MALLOC, 1);
	data->img->img = mlx_new_image(data->mlx, WIN_WIDTH, WIN_HEIGHT); // what is this
	data->img->addr = mlx_get_data_addr(data->img->img, 
			&(data->img->bits_per_pixel), &(data->img->line_length),
			&(data->img->endian));
}

void	initializer(t_data *data)
{
	init_data(data);
	init_mlx(data);
	data->player.pos = (t_2d_point){1, 1};
	data->player.dir = (t_2d_point){0, 1};
	data->player.fov = START_FOV;
	data->player.vertical = 0;
}
