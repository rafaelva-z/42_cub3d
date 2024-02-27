/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-estr <fda-estr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 14:02:24 by fda-estr          #+#    #+#             */
/*   Updated: 2024/02/26 14:13:12 by fda-estr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

t_point	pixel_offset(t_data *data)
{
	t_point		offset;
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

static void	draw_tile(t_img *img, t_img *texture, int x, int y)
{
	int	i;
	int	j;

	i = -1;
	while (++i < MM_TILE_WIDTH)
	{
		j = -1;
		if ((x + i) < 0 || (x + i) > MM_WIDTH)
			continue ;
		while (++j < MM_TILE_HEIGHT)
		{
			if ((y + j) > 0 && (y + j) < MM_HEIGHT)
				draw_pixel(img, x + i, y + j, texture->color_grid[j][i]);
		}
	}
}

void	map_to_tile(t_data *data, t_point print, t_point offset, t_point pix_os)
{
	t_img	*tile;
	int		x;
	int		y;

	x = (int) print.x;
	y = (int) print.y;
	tile = NULL;
	if (print.x < 1 || print.y < 1 || print.x >= data->map.size.x + 1
		|| print.y >= data->map.size.y + 1
		|| data->map.minimap[y - 1][x - 1] == ' '
			|| data->map.minimap[y - 1][x - 1] < 0)
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
