/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz <rvaz@student.42lisboa.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 17:45:18 by rvaz              #+#    #+#             */
/*   Updated: 2024/02/03 20:23:27 by rvaz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	draw_vertical_line_texture(t_2d_point start, t_img *texture, t_data *data, t_ray *ray)
{
	int			y_pos;
	t_2d_point	t_pos;
	double		t_step;
	int			size;

	size = ray->wall_height;
	t_step = (double)TEXTURE_HEIGHT / (double)ray->wall_height;
	y_pos = start.y;
	int t_x_start = (ray->last_hit.x - (int)ray->last_hit.x) * TEXTURE_WIDTH;
	t_pos = (t_2d_point){t_x_start, 0};

	if (start.x >= WIN_WIDTH || start.y >= WIN_HEIGHT || size <= 0)
		return ;
	while (size > 0)
	{
		if (start.x >= 0 && y_pos >= 0
			&& y_pos < WIN_HEIGHT && start.x < WIN_WIDTH)
			draw_pixel(data->img, start.x, y_pos, texture->color_grid[(int)t_pos.x][(int)t_pos.y]);
		y_pos++;
		size--;
		t_pos.y += t_step;
	}
	//printf("last hit: %f %f | t_pos_x: %f | t_pos_y: %f\n", ray->last_hit.x, ray->last_hit.y, t_pos.x, t_pos.y);
}

void	draw_vertical_line(t_2d_point start, int size, t_img *img, int color)
{
	int	y_pos;

	if (start.x >= WIN_WIDTH || start.y >= WIN_HEIGHT || size <= 0)
		return ;
	y_pos = start.y;
	if (color == 0)
	{
		if (size < WIN_HEIGHT * 0.7)
			color = WALL_COLOR - size / 5;
		else
			color = WALL_COLOR - (WIN_HEIGHT * 0.7) / 5;
	}
	while (size > 0)
	{
		if (start.x >= 0 && y_pos >= 0
			&& y_pos < WIN_HEIGHT && start.x < WIN_WIDTH)
			draw_pixel(img, start.x, y_pos, color);
		y_pos++;
		size--;
	}
}
