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

static void	draw_cursor(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	while (++i < 3)
	{
		j = -1;
		while (++j <= 10)
			draw_pixel(data->img_mm, 159 + i, 155 + j, 0xff0000);
	}
	i = -1;
	while (++i < 3)
	{
		j = -1;
		while (++j <= 10)
			draw_pixel(data->img_mm, 155 + j, 159 + i, 0xff0000);
	}
	i = -3;
	while (++i < 3)
	{
		j = -3;
		while (++j < 3)
			draw_pixel(data->img_mm, 160 + (25 * data->player.dir.x) + i, 160
				+ (25 * data->player.dir.y) + j, 0xff0000);
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

void	minimap(t_data *data)
{
	int		i;
	int		j;
	t_point	print;
	t_point	offset;
	t_point	pix_os;

	map_view(data);
	pix_os = pixel_offset(data);
	draw_vacum_tile(data->img_mm, data->textures[MMV_IMG], 0, 0);
	offset = (t_point){data->player.pos.x - 4, data->player.pos.y - 4};
	i = -7;
	while (++i < 5)
	{
		j = -7;
		while (++j < 5)
		{
			print = (t_point){data->player.pos.x - j, data->player.pos.y - i};
			map_to_tile(data, print, offset, pix_os);
		}
	}
	draw_cursor(data);
	mlx_put_image_to_window(data->mlx,
		data->mlx_win, data->img_mm->img, 0, 0);
}
