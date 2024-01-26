/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-estr <fda-estr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 18:09:57 by fda-estr          #+#    #+#             */
/*   Updated: 2024/01/24 18:17:00 by fda-estr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void draw_cursor(t_data *data)
{
	int	i;
	int	j;
	
	i = -1;
	while (++i < 3)
	{
		j = -1;
		while (++j <= 10)
			mlx_pixel_put(data->mlx, data->mlx_win, 159 + i, 155 + j, 0xff0000);
	}
	i = -1;
	while (++i < 3)
	{
		j = -1;
		while (++j <= 10)
			mlx_pixel_put(data->mlx, data->mlx_win, 155 + j, 159 + i, 0xff0000);
	}
	i = -3;
	while (++i < 3)
	{
		j = -3;
		while (++j < 3)
			mlx_pixel_put(data->mlx, data->mlx_win, 160 + (25 * data->player.dir.x) + i, 160 + (25 * data->player.dir.y) + j, 0xff0000);
	}
}

static void	print_tile(t_data *data, t_2d_point print, t_2d_point offset)
{
	void	*tile;
	int		x;
	int		y;

	x = (int) print.x;
	y = (int) print.y;
	tile = NULL;
	printf("%f , %f\n", print.x, print.y);
	printf("%f , %f\n", data->map.size.x, data->map.size.y);
	if (print.x < 0 || print.y < 0 || print.x >= data->map.size.x + 1 || print.y >= data->map.size.y + 1|| data->map.map[y - 1][x - 1] == ' ')
		return;
	else if (data->map.map[y - 1][x - 1] == '0')
		tile = data->ig.mm_floor_img;
	else if (data->map.map[y - 1][x - 1] == '1')
		tile = data->ig.mm_wall_img;
	if (tile)
		mlx_put_image_to_window(data->mlx, data->mlx_win, tile, 32 * (print.x - offset.x),
		32 * (print.y - offset.y));
}

static void	draw_minimap(t_data *data)
{
	int	i;
	int j;
	t_2d_point print;
	t_2d_point offset;

	offset = (t_2d_point) {data->player.pos.x - 3.5, data->player.pos.y - 3.5};
	i = -7;
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->ig.mm_vacum_img, 0, 0);
	while (++i < 5)
	{
		j = -7;
		while (++j < 5)
		{
			print = (t_2d_point) {data->player.pos.x - j, data->player.pos.y - i};
			print_tile(data, print, offset);
		}
	}
	draw_cursor(data);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->ig.frame_x, 0, 320);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->ig.frame_y, 320, 0);
}

static int	ft_hooks(int keycode, t_data *data)
{
	if (keycode == 65307)
		free_and_exit(data, "Game terminated\n");
	if (keycode == 97 || keycode == 115 || keycode == 119 || keycode == 100)
		draw_minimap(data);
	return (0);
}

void	minimap(t_data *data)
{
	int size;
	int size2;


	size = 32;
	size2 = 320;
	data->mlx = mlx_init();
	data->mlx_win = mlx_new_window(data->mlx, 1000, 1000, "test");
	data->ig.mm_floor_img = mlx_xpm_file_to_image(data->mlx, "./textures/minimap/mm_floor.xpm", &size, &size);
	data->ig.mm_vacum_img = mlx_xpm_file_to_image(data->mlx, "./textures/minimap/mm_vacum.xpm", &size2, &size2);
	data->ig.mm_wall_img = mlx_xpm_file_to_image(data->mlx, "./textures/minimap/mm_wall.xpm", &size, &size);
	size2 = 352;
	data->ig.frame_x = mlx_xpm_file_to_image(data->mlx, "./textures/minimap/frame_x.xpm", &size2, &size);
	data->ig.frame_y = mlx_xpm_file_to_image(data->mlx, "./textures/minimap/frame_y.xpm", &size, &size2);
	mlx_key_hook(data->mlx_win, ft_hooks, data);
	mlx_loop(data->mlx);
}
