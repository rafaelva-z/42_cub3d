/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz <rvaz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 18:41:12 by rvaz              #+#    #+#             */
/*   Updated: 2024/03/12 20:10:25 by rvaz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

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
 * @return	1 if the sprite is a door, 0 if not
*/
short	rc_door(t_data *data, t_sprite *sprite, t_player *player)
{
	t_ray		ray;
	double		camera_x;
	int			r;

	r = -1;
	if (sprite->type != SPRT_DOOR)
		return (0);
	if (sprite->type == D_OPEN || sprite->type == D_CLOSED)
		return (1);
	while (++r < WIN_WIDTH)
	{
		camera_x = 2.0 * (double)r / (double)WIN_WIDTH - 1.0;
		ray.dir.x = player->dir.x + player->plane.x * camera_x;
		ray.dir.y = player->dir.y + player->plane.y * camera_x;
		dda_door(&ray, data, sprite);
		ray.wall_height = WIN_HEIGHT
			/ (ray.distance * (data->player.fov * 0.0151));
		if (ray.wall_height < 0)
			continue ;
		draw_wall(data, r, &ray, sprite);
	}
	return (1);
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
