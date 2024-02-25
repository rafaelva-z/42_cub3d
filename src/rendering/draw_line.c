/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz <rvaz@student.42lisboa.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 17:45:18 by rvaz              #+#    #+#             */
/*   Updated: 2024/02/24 17:34:06 by rvaz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static double	def_texture_start(t_ray *ray, t_img *texture, int *size,
					t_data *data)
{
	double	wallx;

	if (ray->side == 0 || ray->side == 3)
		wallx = data->player.pos.y + ray->distance * ray->dir.y;
	else if (ray->side == 1 || ray->side == 4)
		wallx = data->player.pos.x + ray->distance * ray->dir.x;
	wallx -= floor(wallx);
	*size = ray->wall_height;
	return (wallx * (double)texture->width);
}

/**
 * @brief	Inverts horizontally the textures on the negative x and y
 * 			directions
*/
int	invert_neg_oriented_textures(t_ray *ray, t_img *texture, int *t_start_x)
{
	if (ray->dir.x < 0 && ray->side == 0
		|| (ray->dir.y > 0 && ray->side == 1))
		return (texture->width - *t_start_x - 1);
	return (*t_start_x);
}

void	jump_negative_value_pixels(t_point *prnt_pos, t_point *t_pos,
		int *size, double t_step)
{
	if ((*prnt_pos).y < 0)
	{
		(*t_pos).y += t_step * -(*prnt_pos).y;
		*size += (*prnt_pos).y;
		(*prnt_pos).y -= (*prnt_pos).y;
	}
}

/**
 * This function needs to be optimized
*/
void	draw_vertical_line_texture(t_point prnt_pos, t_img *texture,
		t_data *data, t_ray *ray)
{
	t_point		t_pos;
	double		t_step;
	int			size;
	int			t_start_x;
	int			color;

	t_start_x = def_texture_start(ray, texture, &size, data);
	t_start_x = invert_neg_oriented_textures(ray, texture, &t_start_x);
	t_step = (double)texture->height / (double)ray->wall_height;
	t_pos = (t_point){t_start_x, 0};
	if (prnt_pos.x >= WIN_WIDTH || prnt_pos.y >= WIN_HEIGHT || size <= 0)
		return ;
	jump_negative_value_pixels(&prnt_pos, &t_pos, &size, t_step);
	while (size > 0)
	{
		color = texture->color_grid[(int)t_pos.y][(int)t_pos.x];
		if (prnt_pos.x < 0 || prnt_pos.y > WIN_HEIGHT || prnt_pos.x > WIN_WIDTH)
			return ;
		if (prnt_pos.y >= 0)
			draw_pixel(data->img, prnt_pos.x, prnt_pos.y,
				shader(color, ray->distance, 1, 0.3, 1));
		prnt_pos.y++;
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

// void	draw_vert_line_grad_center(t_img *img, int x, int vertical)
// {
// 	int	y;
// 	int b;
// 	int	sky_color;
// 	int	floor_color;

// 	sky_color = (SKY_COLOR & 0xfefefefe) >> 1;
// 	floor_color = FLOOR_COLOR;
// 	b = WIN_HEIGHT - 1;
// 	if (x >= WIN_WIDTH || x < 0)
// 		return ;
// 	y = 0;
// 	while (y < WIN_HEIGHT / 2 + vertical)
// 		draw_pixel(img, x, y++, sky_color);
// 	while (b > y)
// 	{
// 		if (!(b % 200) || !(b % 300))
// 			floor_color = (floor_color & 0xfefefefe) >> 1;
// 		draw_pixel(img, x, b--, floor_color);
// 	}
// }
