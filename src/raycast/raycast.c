/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz <rvaz@student.42lisboa.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 18:41:12 by rvaz              #+#    #+#             */
/*   Updated: 2024/02/25 14:22:41 by rvaz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	rc_fc_loop(t_point *r, t_point raydir0, t_point raydir1, t_point *color, t_data *data)
{
	t_point	t_step;			// distance between each x ray
	double	distance;		// distance from the camera to the floor
	t_point	real_pos;		// current position x and y
	t_point	t_pos;

	while (++r->y < WIN_HEIGHT)
	{
		distance = (0.5 * WIN_HEIGHT) / (r->y - WIN_HEIGHT / 2); // camera height divided by y position relative to center of the screen
		t_step.x = distance * (raydir1.x - raydir0.x) / WIN_WIDTH;
		t_step.y = distance * (raydir1.y - raydir0.y) / WIN_WIDTH;
		real_pos.x = data->player.pos.x + distance * raydir0.x;
		real_pos.y = data->player.pos.y + distance * raydir0.y;
		r->x = -1;
		while (++r->x < WIN_WIDTH)
		{
			t_pos.x = (int)(TEXTURE_WIDTH * (real_pos.x - (int)real_pos.x) * 2) & (TEXTURE_WIDTH - 1);
			t_pos.y = (int)(TEXTURE_HEIGHT * (real_pos.y - (int)real_pos.y) * 2) & (TEXTURE_HEIGHT - 1);
			real_pos.x += t_step.x;
			real_pos.y += t_step.y;
			color->x = data->textures[F_IMG]->color_grid[(int)t_pos.y][(int)t_pos.x];
			color->y = data->textures[C_IMG]->color_grid[(int)t_pos.y][(int)t_pos.x];
			draw_pixel(data->img, (int)r->x, (int)r->y, shader(color->x, r->y, 500, 45, 0));
			draw_pixel(data->img, (int)r->x, WIN_HEIGHT - (int)r->y, shader(color->y, r->y, 500, 45, 0));
		}
	}
}

/**
 * @brief	Draws the floor and ceiling
*/
void	rc_floor_ceiling(t_data *data)
{
	t_point	r;				// current ray position
	t_point	raydir0;		// leftmost ray
	t_point	raydir1;		// rightmost ray
	t_point color;

	r.y = -1;
	raydir0.x = data->player.dir.x - data->player.plane.x;
	raydir0.y = data->player.dir.y - data->player.plane.y;
	raydir1.x = data->player.dir.x + data->player.plane.x;
	raydir1.y = data->player.dir.y + data->player.plane.y;
	rc_fc_loop(&r, raydir0, raydir1, &color, data);
}

/**
 * @brief	A raycast function that draws the walls
*/
void	rc_walls(t_data *data, t_player *player)
{
	t_ray		ray;
	double		camera_x;
	int			r;

	r = 0;
	while (r < WIN_WIDTH)
	{
		camera_x = 2.0 * r / (double)WIN_WIDTH - 1.0;
		ray.dir.x = player->dir.x + player->plane.x * camera_x;
		ray.dir.y = player->dir.y + player->plane.y * camera_x;
		dda(&ray, data);
		ray.wall_height = WIN_HEIGHT
			/ (ray.distance * (data->player.fov * 0.0151));
		data->z_buffer[r] = ray.distance;
		draw_wall(data, r, &ray, NULL);
		r++;
	}
}

/**
 * @brief	A raycast function that draws only opening or closing doors
*/
void	rc_door(t_data *data, t_sprite *door, t_player *player)
{
	t_ray		ray;
	double		camera_x;
	int			r;

	r = -1;
	while (++r < WIN_WIDTH)
	{
		camera_x = 2.0 * r / (double)WIN_WIDTH - 1.0;
		ray.dir.x = player->dir.x + player->plane.x * camera_x;
		ray.dir.y = player->dir.y + player->plane.y * camera_x;
		dda_door(&ray, data);
		ray.wall_height = WIN_HEIGHT
			/ (ray.distance * (data->player.fov * 0.0151));
		if (ray.wall_height < 0)
			continue ;
		draw_wall(data, r, &ray, door);
	}
}

/**
 * @brief	The main raycast function that draws the player pov
 * 			on the program window.
*/
void	rc_player(t_data *data)
{
	rc_floor_ceiling(data);
	rc_walls(data, &data->player);
	rc_sprites(data);
}
