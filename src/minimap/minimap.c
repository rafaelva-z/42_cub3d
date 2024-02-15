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

static void	map_view(t_data *data)
{
	int	x;
	int	y;

	x = (int) data->player.pos.x;
	y = (int) data->player.pos.y;
	if (data->map.minimap[y - 1][x - 1] < 0)
		data->map.minimap[y - 1][x - 1] *= -1;
	if (data->map.minimap[y - 1][x] < 0)
		data->map.minimap[y - 1][x] *= -1;
	if (data->map.minimap[y - 1][x + 1] < 0)
		data->map.minimap[y - 1][x + 1] *= -1;
	if (data->map.minimap[y][x - 1] < 0)
		data->map.minimap[y][x - 1] *= -1;
	if (data->map.minimap[y][x] < 0)
		data->map.minimap[y][x] *= -1;
	if (data->map.minimap[y][x + 1] < 0)
		data->map.minimap[y][x + 1] *= -1;
	if (data->map.minimap[y + 1][x - 1] < 0)
		data->map.minimap[y + 1][x - 1] *= -1;
	if (data->map.minimap[y + 1][x] < 0)
		data->map.minimap[y + 1][x] *= -1;
	if (data->map.minimap[y + 1][x + 1] < 0)
		data->map.minimap[y + 1][x + 1] *= -1;
}

static t_point	pixel_offset(t_data *data)
{
	t_point	offset;
	int			x;
	int			y;

	x = data->player.pos.x;
	y = data->player.pos.y;
	offset.x = data->player.pos.x - x;
	offset.y = data->player.pos.y - y;
	offset.x *= 32;
	offset.y *= 32;
	return (offset);
}

static void draw_cursor(t_data *data)
{
	int	i;
	int	j;
	
	i = -1;
	while (++i < 3)
	{
		j = -1;
		while (++j <= 10)
			draw_pixel(data->img_mm, 159 + i, 155 + j, 0xff0000);
			// mlx_pixel_put(data->mlx, data->mlx_win_mm, 159 + i, 155 + j, 0xff0000);
	}
	i = -1;
	while (++i < 3)
	{
		j = -1;
		while (++j <= 10)
			draw_pixel(data->img_mm, 155 + j, 159 + i, 0xff0000);
			// mlx_pixel_put(data->mlx, data->mlx_win_mm, 155 + j, 159 + i, 0xff0000);
	}
	i = -3;
	while (++i < 3)
	{
		j = -3;
		while (++j < 3)
			draw_pixel(data->img_mm, 160 + (25 * data->player.dir.x) + i, 160 + (25 * data->player.dir.y) + j, 0xff0000);
			// mlx_pixel_put(data->mlx, data->mlx_win_mm, 160 + (25 * data->player.dir.x) + i, 160 + (25 * data->player.dir.y) + j, 0xff0000);
	}
}

static void	draw_vacum_tile(t_img *img, t_img *texture, int x, int y)
{
	int	i;
	int	j;

	i = -1;
	if (x == MM_WIDTH || y == MM_HEIGHT)
		return ;
	while (++i < MM_WIDTH)
	{
		j = -1;
		while (++j < MM_HEIGHT)
				draw_pixel(img, x + i, y + j, texture->color_grid[y + j][x + i]);
	}
}

static void	draw_tile(t_img *img, t_img *texture, int x, int y)
{
	int	i;
	int	j;

	i = -1;
	while (++i < MM_TILE_WIDTH)
	{
		j = -1;
		if ((x + i) < 0 || (x + i) > MM_WIDTH)
			continue;
		while (++j < MM_TILE_HEIGHT)
		{
			if ((y + j) > 0 && (y + j) < MM_HEIGHT)
				draw_pixel(img, x + i, y + j, texture->color_grid[j][i]);
		}
	}
}

static void	map_to_tile(t_data *data, t_point print, t_point offset, t_point pix_os)
{
	t_img	*tile;
	int		x;
	int		y;

	x = (int) print.x;
	y = (int) print.y;
	tile = NULL;
	if (print.x < 1 || print.y < 1 || print.x >= data->map.size.x + 1 || print.y >= data->map.size.y + 1 || data->map.minimap[y - 1][x - 1] == ' ' || data->map.minimap[y - 1][x - 1] < 0)
		return ;
	else if (data->map.minimap[y - 1][x - 1] == '0')
		draw_tile(data->img_mm, data->textures[MMF_IMG],
			(32 * (print.x - offset.x)) - pix_os.x,
			(32 * (print.y - offset.y)) - pix_os.y);
	else if (data->map.minimap[y - 1][x - 1] == '1')
		draw_tile(data->img_mm, data->textures[MMW_IMG],
			(32 * (print.x - offset.x)) - pix_os.x,
			(32 * (print.y - offset.y)) - pix_os.y);
}

static void	draw_minimap(t_data *data)
{
	int	i;
	int j;
	t_point print;
	t_point offset;
	t_point pix_os;		//pixel offset

	pix_os = pixel_offset(data);
	draw_vacum_tile(data->img_mm, data->textures[MMV_IMG], 0, 0);
	offset = (t_point) {data->player.pos.x - 4, data->player.pos.y - 4};
	i = -7;
	while (++i < 5)
	{
		j = -7;
		while (++j < 5)
		{
			print = (t_point) {data->player.pos.x - j, data->player.pos.y - i};
			map_to_tile(data, print, offset, pix_os);
		}
	}
	draw_cursor(data);
	mlx_put_image_to_window(data->mlx, data->mlx_win_mm, data->img_mm->img, 0, 0);
}

// static int	ft_hooks(int keycode, t_data *data)
// {
// 	if (keycode == 65307)
// 		free_and_exit(data, "Game terminated\n", 0);
// 	if (keycode == 97 || keycode == 115 || keycode == 119 || keycode == 100)
// 		draw_minimap(data);
// 	return (0);
// }


void	minimap(t_data *data)
{
	// (void) data;
	map_view(data);
	draw_minimap(data);
	// int size;
	// int size2;


	// size = 32;
	// size2 = 320;
	// data->mlx = mlx_init();
	// data->mlx_win = mlx_new_window(data->mlx, 1000, 1000, "test");
	// data->ig.mm_floor_img = mlx_xpm_file_to_image(data->mlx, "./textures/minimap/mm_floor.xpm", &size, &size);
	// data->ig.mm_vacum_img = mlx_xpm_file_to_image(data->mlx, "./textures/minimap/mm_vacum.xpm", &size2, &size2);
	// data->ig.mm_wall_img = mlx_xpm_file_to_image(data->mlx, "./textures/minimap/mm_wall.xpm", &size, &size);
	// size2 = 352;
	// data->ig.frame_x = mlx_xpm_file_to_image(data->mlx, "./textures/minimap/frame_x.xpm", &size2, &size);
	// data->ig.frame_y = mlx_xpm_file_to_image(data->mlx, "./textures/minimap/frame_y.xpm", &size, &size2);
	// mlx_key_hook(data->mlx_win, ft_hooks, data);
	// mlx_loop(data->mlx);
}
