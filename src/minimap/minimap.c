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

static void	print_tile(t_data *data, t_2d_point print, t_2d_point offset)
{
	void	*tile;
	int		x;
	int		y;

	x = (int) print.x;
	y = (int) print.y;
	tile = NULL;
	printf("x: %d\ty: %d\n", x, y);
	printf("char: %c\n", data->map.map[y][x]);
	if (print.x < 0 || print.y < 0 || data->map.map[y][x] == ' ')
		tile = data->mm_vacum_img;
	else if (data->map.map[y][x] == '0')
		tile = data->mm_floor_img;
	else if (data->map.map[y][x] == '1')
		tile = data->mm_wall_img;
	mlx_put_image_to_window(data->mlx, data->mlx_win, tile, print.x - offset.x,
		print.y - offset.y);
	mlx_pixel_put(data->mlx, data->mlx_win, 160, 160, 0xff0000);
}

static void	draw_minimap(t_data *data)
{
	int			i;
	int			j;
	t_2d_point	print;
	t_2d_point	offset;

	offset = (t_2d_point){data->player.pos.x - 5, data->player.pos.y - 5};
	i = -7;
	while (++i < 11)
	{
		j = -7;
		while (++j < 11)
		{
			print = (t_2d_point){data->player.pos.x - j, data->player.pos.y - i};
			print_tile(data, print, offset);
		}
	}
}

static int	ft_hooks(int keycode, t_data *data)
{
	printf("keycode: %d\n", keycode);
	matrix_printer(data->map.map);
	if (keycode == 65307)
		free_and_exit(data, MSG_EXIT, 0);
	if (keycode == 97 || keycode == 115 || keycode == 119 || keycode == 100)
		draw_minimap(data);
	return (0);
}

void	minimap(t_data *data)
{
	int size;


	size = 32;
	data->mlx = mlx_init();
	if (!data->mlx)
		printf("fodeu...");
	data->mlx_win = mlx_new_window(data->mlx, 320, 320, "test");
	data->mm_floor_img = mlx_xpm_file_to_image(data->mlx, "textures/mini_map/mm_floor.xpm", &size, &size);
	data->mm_vacum_img = mlx_xpm_file_to_image(data->mlx, "textures/mini_map/mm_vacum.xpm", &size, &size);
	data->mm_wall_img = mlx_xpm_file_to_image(data->mlx, "textures/mini_map/mm_wall.xpm", &size, &size);
	mlx_key_hook(data->mlx_win, ft_hooks, &data);
	mlx_loop(data->mlx);
}