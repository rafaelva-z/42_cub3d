/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz <rvaz@student.42lisboa.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 18:41:12 by rvaz              #+#    #+#             */
/*   Updated: 2024/02/21 15:05:22 by rvaz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	draw_wall(t_data *data, int r, t_ray *ray, t_sprite *door)
{
	int		sky_size;
	t_img	*texture;

	if (ray->side == 0)
	{
		if (ray->dir.x < 0)
			texture = data->textures[WE_IMG];
		else
			texture = data->textures[EA_IMG];
	}
	else if (ray->side == 1)
	{
		if (ray->dir.y < 0)
			texture = data->textures[NO_IMG];
		else
			texture = data->textures[SO_IMG];
	}
	else if (ray->side == 3 || ray->side == 4)
	{
		if (door)
			texture = data->textures[D0_IMG + door->current_frame];
		else
			texture = data->textures[D0_IMG];
	}
	sky_size = ((WIN_HEIGHT - ray->wall_height) / 2) + data->player.vertical;
	draw_vertical_line_texture((t_point){r, sky_size}, texture, data, ray);
}

void	rc_floor_ceiling(t_data *data)
{
	t_point	r;				// current ray position
	t_point	raydir0;		// leftmost ray
	t_point	raydir1;		// rightmost ray
	double	distance;		// distance from the camera to the floor
	t_point	t_step;			// distance between each x ray
	t_point	real_pos;	// current position x and y
	int		color_c;
	int		color_f;
	t_point	t_pos;

	raydir0.x = data->player.dir.x - data->player.plane.x;
	raydir0.y = data->player.dir.y - data->player.plane.y;
	raydir1.x = data->player.dir.x + data->player.plane.x;
	raydir1.y = data->player.dir.y + data->player.plane.y;
	r.y = -1;
	while (++r.y < WIN_HEIGHT)
	{
		distance = (0.5 * WIN_HEIGHT) / (r.y - WIN_HEIGHT / 2); // camera height divided by y position relative to center of the screen
		t_step.x = distance * (raydir1.x - raydir0.x) / WIN_WIDTH;
		t_step.y = distance * (raydir1.y - raydir0.y) / WIN_WIDTH;
		real_pos.x = data->player.pos.x + distance * raydir0.x;
		real_pos.y = data->player.pos.y + distance * raydir0.y;
		r.x = -1;
		while (++r.x < WIN_WIDTH)
		{
			t_pos.x = (int)(TEXTURE_WIDTH * (real_pos.x - (int)real_pos.x) * 2) & (TEXTURE_WIDTH - 1);
			t_pos.y = (int)(TEXTURE_HEIGHT * (real_pos.y - (int)real_pos.y) * 2) & (TEXTURE_HEIGHT - 1);
			real_pos.x += t_step.x;
			real_pos.y += t_step.y;
			color_f = data->textures[F_IMG]->color_grid[(int)t_pos.y][(int)t_pos.x];
			color_c = data->textures[C_IMG]->color_grid[(int)t_pos.y][(int)t_pos.x];
			draw_pixel(data->img, (int)r.x, (int)r.y, shader(color_f, r.y, 500, 45, 0));
			draw_pixel(data->img, (int)r.x, WIN_HEIGHT - (int)r.y, shader(color_c, r.y, 500, 45, 0));
		}
	}
}

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
		//draw_vert_line_grad_center(data->img, r, data->player.vertical);
		data->z_buffer[r] = ray.distance; // sprite casting
		draw_wall(data, r, &ray, NULL);
		r++;
	}
}

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
		draw_wall(data, r, &ray, door); // draw door
	}
}

/**
 * @brief	The raycast main function
*/
void	raycast(t_data *data)
{
	rc_floor_ceiling(data);
	rc_walls(data, &data->player);
	rc_sprites(data);
}

void	enemy_raycast(t_data *data, t_sprite *enemy)
{
	t_ray		ray;
	int			r;

	r = 0;
	ray.dir.x = enemy->dir.x;
	ray.dir.y = enemy->dir.y;
	rotate_point(&ray.dir, -(ENEMY_FOV / 2));
	while (r < ENEMY_FOV)
	{
		dda_enemy(&ray, data);
		if (ray.distance == -1)
		{
			enemy->state = E_FOLLOW;
			return ;
		}
		rotate_point(&ray.dir, 1);
		r++;
	}
}