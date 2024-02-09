/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-estr <fda-estr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 18:41:12 by rvaz              #+#    #+#             */
/*   Updated: 2024/02/09 16:19:20 by fda-estr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	draw_column(t_data *data, int r, t_ray *ray)
{
	int		sky_size;
	t_img	*texture;

	if (ray->side == 0)
	{
		if (ray->dir.x < 0)
			texture = data->textures[WE_IMG];			// data->image.west_img;
		else
			texture = data->textures[EA_IMG];			// data->image.east_img;
	}
	else
	{
		if (ray->dir.y < 0)
			texture = data->textures[NO_IMG];			// data->image.north_img;
		else
			texture = data->textures[SO_IMG];			// data->image.south_img;
	}
	sky_size = ((WIN_HEIGHT - ray->wall_height) / 2) + data->player.vertical;
	draw_vert_line_grad_center(data->img, r, data->player.vertical);
	draw_vertical_line_texture((t_2d_point){r, sky_size}, texture, data, ray);
}

/**
 * @brief	The raycast main function
*/
void	raycast(t_data *data)
{
	t_ray		ray;
	double		camera_x;
	int			r;
	
	r = 0;
	while (r < WIN_WIDTH)
	{
		camera_x = 2 * r / (double)WIN_WIDTH - 1;
		ray.dir.x = data->player.dir.x + data->player.plane.x * camera_x;
		ray.dir.y = data->player.dir.y + data->player.plane.y * camera_x;
		dda(&ray, data);
		ray.wall_height = WIN_HEIGHT
			/ (ray.distance * (data->player.fov * 0.0151));
		draw_column(data, r, &ray);
		r++;
	}
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img->img, 0, 0);
}

void	enemy_raycast(t_data *data, t_enemy *enemy)
{
	t_ray		ray;
	double		camera_x;
	int			r;

	(void)enemy;
	r = 0;
	while (r < 30) // define a macro for enemy rays
	{
		camera_x = 2 * r / (double)30 - 1;
		ray.dir.x = enemy->dir.x + enemy->plane.x * camera_x;
		ray.dir.y = enemy->dir.y + enemy->plane.y * camera_x;
		dda(&ray, data);
		// check if player was found on ray hit linked list then:
		/*
		if (playerfound())
			follow = 1
		else
			follow = 0
		*/
		r++;
	}
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img->img, 0, 0);
}