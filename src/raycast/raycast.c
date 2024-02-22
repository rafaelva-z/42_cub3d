/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz <rvaz@student.42lisboa.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 18:41:12 by rvaz              #+#    #+#             */
/*   Updated: 2024/02/22 12:00:57 by rvaz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/**
 * @brief	Sets the texture to be drawn on the wall based on "side" variable
 * 			form the given ray. 0 West/East; 1 North/South; 3/4 Door.
*/
void	set_wall_texture(t_img **txt_lst, t_ray *r, t_sprite *door, t_img **txt)
{
	if (r->side == 0)
	{
		if (r->dir.x < 0)
			*txt = txt_lst[WE_IMG];
		else
			*txt = txt_lst[EA_IMG];
	}
	else if (r->side == 1)
	{
		if (r->dir.y < 0)
			*txt = txt_lst[NO_IMG];
		else
			*txt = txt_lst[SO_IMG];
	}
	else if (r->side == 3 || r->side == 4)
	{
		if (door)
			*txt = txt_lst[D0_IMG + door->current_frame];
		else
			*txt = txt_lst[D0_IMG];
	}
}

/**
 * @brief	
*/
static void	draw_wall(t_data *data, int r, t_ray *ray, t_sprite *door)
{
	int		sky_size;
	t_img	*texture;

	sky_size = ((WIN_HEIGHT - ray->wall_height) / 2) + data->player.vertical;
	set_wall_texture(data->textures, ray, door, &texture);
	draw_vertical_line_texture((t_point){r, sky_size}, texture, data, ray);
}


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
 * @brief	A raycast function that draws only opening/closing doors
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
		draw_wall(data, r, &ray, door); // draw door
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

/**
 * @brief	The raycast main function
*/
void	rc_enemy(t_data *data, t_sprite *enemy)
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
