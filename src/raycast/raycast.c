/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz <rvaz@student.42lisboa.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 18:41:12 by rvaz              #+#    #+#             */
/*   Updated: 2024/02/03 21:45:23 by rvaz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	draw_column(t_data *data, int r, t_ray *ray)
{
	int		sky_size;
	t_img	*texture;

	if (ray->side == 0)
	{
		if (data->player.pos.x > ray->last_hit.x)
			texture = &data->image.east_img;
		else
			texture = &data->image.west_img;
	}
	else
	{
		if (data->player.pos.y > ray->last_hit.y)
			texture = &data->image.south_img;
		else
			texture = &data->image.north_img;
	}
	sky_size = ((WIN_HEIGHT - ray->wall_height) / 2) + data->player.vertical;
	if (sky_size + ray->wall_height > WIN_HEIGHT)
		sky_size = WIN_HEIGHT - ray->wall_height;
	// else if (sky_size <= 0)
	// 	sky_size = 1;
	draw_vertical_line((t_2d_point){r, 0},
		sky_size, data->img, SKY_COLOR);
	draw_vertical_line((t_2d_point){r, sky_size + ray->wall_height},
		WIN_HEIGHT - (sky_size + ray->wall_height), data->img, FLOOR_COLOR);
	// draw_vertical_line((t_2d_point){r, sky_size},
	// 	ray->wall_height, data->img, 0);
	draw_vertical_line_texture((t_2d_point){r, sky_size}, texture, data, ray);
}

/**
 * @brief	Converts the distance from the player to the wall to the wall height
 * 			in pixels.
*/
static double	get_wall_height(double wall_distance)
{
	if (wall_distance > WIN_HEIGHT)
		return (WIN_HEIGHT);
	else
		return (WIN_HEIGHT / wall_distance);
}

/**
 * @brief	The raycast main function
*/
void	raycast(t_data *data)
{
	int			r;
	t_ray		ray;
	double		camera_x;

	r = 0;
	while (r < WIN_WIDTH)
	{
		camera_x = 2 * r / (double)WIN_WIDTH - 1;
		ray.dir.x = data->player.dir.x + data->player.plane.x * camera_x;
		ray.dir.y = data->player.dir.y + data->player.plane.y * camera_x;
		dda(&ray, data);
		ray.wall_height = get_wall_height(ray.distance * (data->player.fov * 0.0151));
		draw_column(data, r, &ray);
		r++;
	}
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img->img, 0, 0);
}
