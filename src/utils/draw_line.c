/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz <rvaz@student.42lisboa.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 17:45:18 by rvaz              #+#    #+#             */
/*   Updated: 2024/02/15 16:45:18 by rvaz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/**
 * This function needs to be optimized
*/
void	draw_vertical_line_texture(t_point print_pos, t_img *texture, t_data *data, t_ray *ray)
{
	t_point	t_pos;
	double		t_step;
	int			size;
	int			t_start_x;
	int			color;
	double		wallX;
	
	if (ray->side == 0)
		wallX = data->player.pos.y + ray->distance * ray->dir.y;
	else
		wallX = data->player.pos.x + ray->distance * ray->dir.x;
	wallX -= floor(wallX);
	size = ray->wall_height;
	t_start_x = wallX * texture->width;
	if ((ray->dir.x < 0 && ray->side == 0) || (ray->dir.y > 0 && ray->side == 1))
		t_start_x = texture->width - t_start_x - 1;
	t_step = (double)texture->height / (double)ray->wall_height;
	t_pos = (t_point){t_start_x, 0};
	if (print_pos.x >= WIN_WIDTH || print_pos.y >= WIN_HEIGHT || size <= 0)
		return ;
	if (print_pos.y < 0)
	{
		t_pos.y += t_step * -print_pos.y;
		size += print_pos.y;
		print_pos.y -= print_pos.y;
	}
	while (size > 0)
	{
		color = texture->color_grid[(int)t_pos.y][(int)t_pos.x];
		for (double i = ray->distance; i > 1 ; i -= 0.3)
			color = (color & 0xfefefefe) >> 1;
		if (print_pos.x < 0 || print_pos.y > WIN_HEIGHT || print_pos.x > WIN_WIDTH)
			return ;
		if (print_pos.y >= 0)
			draw_pixel(data->img, print_pos.x, print_pos.y, color);
		print_pos.y++;
		size--;
		t_pos.y += t_step;
	}
}

void	draw_vertical_line(t_point start, int size, t_img *img, int color)
{
	int	y_pos;

	if (start.x >= WIN_WIDTH || start.y >= WIN_HEIGHT || size <= 0)
		return ;
	y_pos = start.y;
	if (color == -1)
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

void	draw_vert_line_grad_center(t_img *img, int x, int vertical)
{
	int	y;
	int b;
	int	sky_color;
	int	floor_color;

	sky_color = (SKY_COLOR & 0xfefefefe) >> 1;
	floor_color = FLOOR_COLOR;
	b = WIN_HEIGHT - 1;
	if (x >= WIN_WIDTH || x < 0)
		return ;
	y = 0;
	while (y < WIN_HEIGHT / 2 + vertical)
		draw_pixel(img, x, y++, sky_color);
	while (b > y)
	{
		if (!(b % 200) || !(b % 300))
			floor_color = (floor_color & 0xfefefefe) >> 1;
		draw_pixel(img, x, b--, floor_color);
	}
}
