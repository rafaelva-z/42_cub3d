/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-estr <fda-estr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 18:41:12 by rvaz              #+#    #+#             */
/*   Updated: 2024/02/09 16:50:27 by fda-estr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	draw_wall(t_data *data, int r, t_ray *ray)
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
	draw_vertical_line_texture((t_2d_point){r, sky_size}, texture, data, ray);
}

void	draw_floor_and_ceiling(t_data *data)
{
	t_2d_point	r;				// current ray position
	t_2d_point	raydir0;		// leftmost ray
	t_2d_point	raydir1;		// rightmost ray
	int			y; 				// y position relative to center of the screen
	double		pos_z;			// camera height
	double		distance;		// distance from the camera to the floor
	t_2d_point	t_step;			// distance between each x ray
	t_2d_point	real_pos;	// current position x and y
	t_img		*floor_texture;
	t_img		*ceiling_texture;
	int			color_c;
	int			color_f;
	t_2d_point	t_pos;

	floor_texture = data->textures[F_IMG];
	ceiling_texture = data->textures[C_IMG];

	raydir0.x = data->player.dir.x - data->player.plane.x;
	raydir0.y = data->player.dir.y - data->player.plane.y;
	raydir1.x = data->player.dir.x + data->player.plane.x;
	raydir1.y = data->player.dir.y + data->player.plane.y;

	r.y = 0;
	while (r.y < WIN_HEIGHT)
	{
		y = r.y - WIN_HEIGHT / 2;
		pos_z = 0.5 * WIN_HEIGHT;
		distance = pos_z / y;
		t_step.x = distance * (raydir1.x - raydir0.x) / WIN_WIDTH;
		t_step.y = distance * (raydir1.y - raydir0.y) / WIN_WIDTH;
		real_pos.x = data->player.pos.x + distance * raydir0.x;
		real_pos.y = data->player.pos.y + distance * raydir0.y;
		r.x = 0;
		while (++r.x < WIN_WIDTH)
		{
			t_pos.x = (int)(TEXTURE_WIDTH * (real_pos.x - (int)real_pos.x)) & (TEXTURE_WIDTH - 1);
			t_pos.y = (int)(TEXTURE_HEIGHT * (real_pos.y - (int)real_pos.y)) & (TEXTURE_HEIGHT - 1);
			real_pos.x += t_step.x;
			real_pos.y += t_step.y;
			color_f = floor_texture->color_grid[(int)t_pos.y][(int)t_pos.x];
			draw_pixel(data->img, (int)r.x, (int)r.y, color_f);
			color_c = ceiling_texture->color_grid[(int)t_pos.y][(int)t_pos.x];
			draw_pixel(data->img, (int)r.x, WIN_HEIGHT - (int)r.y, color_c);
		}
		r.y++;
	}

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
	draw_floor_and_ceiling(data);
	while (r < WIN_WIDTH)
	{
		camera_x = 2 * r / (double)WIN_WIDTH - 1;
		ray.dir.x = data->player.dir.x + data->player.plane.x * camera_x;
		ray.dir.y = data->player.dir.y + data->player.plane.y * camera_x;
		dda(&ray, data);
		ray.wall_height = WIN_HEIGHT
			/ (ray.distance * (data->player.fov * 0.0151));
		//draw_vert_line_grad_center(data->img, r, data->player.vertical);
		draw_wall(data, r, &ray);
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