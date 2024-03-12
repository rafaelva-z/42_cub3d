/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-estr <fda-estr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 17:06:39 by rvaz              #+#    #+#             */
/*   Updated: 2024/03/09 14:48:35 by fda-estr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/**
 *	@brief	Initializes "step" based on the ray direction, and "raylen" to the
 *			ray starting position based on the current map cell.
*/
void	dda_start(t_point *pos, t_ray *ray)
{
	if (ray->dir.x < 0)
	{
		ray->step_dir.x = -1;
		ray->length.x = (pos->x - floor(pos->x))
			* ray->step_size.x;
	}
	else
	{
		ray->step_dir.x = 1;
		ray->length.x = ((floor(pos->x) + 1)
				- pos->x) * ray->step_size.x;
	}
	if (ray->dir.y < 0)
	{
		ray->step_dir.y = -1;
		ray->length.y = (pos->y - floor(pos->y))
			* ray->step_size.y;
	}
	else
	{
		ray->step_dir.y = 1;
		ray->length.y = ((floor(pos->y) + 1)
				- pos->y) * ray->step_size.y;
	}
}

int	dda_loop(t_point *current, t_ray *ray)
{
	if (ray->length.x < ray->length.y)
	{
		ray->length.x += ray->step_size.x;
		current->x += ray->step_dir.x;
		return (0);
	}
	else
	{
		ray->length.y += ray->step_size.y;
		current->y += ray->step_dir.y;
		return (1);
	}
}

void	dda_enemy(t_ray *ray, t_data *data, t_sprite *enemy)
{
	t_point	current;

	ray->distance = 0;
	ray->step_size.x = fabs(1.0 / ray->dir.x);
	ray->step_size.y = fabs(1.0 / ray->dir.y);
	current = (t_point){enemy->pos.x, enemy->pos.y};
	dda_start(&enemy->pos, ray);
	while (is_inside_map(current, data->map.size) && !is_wall(current, data))
	{
		ray->side = dda_loop(&current, ray);
		if (is_player(current, data))
		{
			ray->distance = -1;
			return ;
		}
	}
	ray->distance = 1;
}

/**
 *	@brief	Digital Differential Analyzer - This algorithm calculates the
 			length from the starting point to the nearest wall (including closed doors) 
			in a straight line.
*/
void	dda(t_ray *ray, t_data *data)
{
	t_point	current;

	ray->step_size.x = fabs(1.0 / ray->dir.x);
	ray->step_size.y = fabs(1.0 / ray->dir.y);
	current = (t_point){data->player.pos.x, data->player.pos.y};
	dda_start(&data->player.pos, ray);
	while (is_inside_map(current, data->map.size) && !is_wall(current, data))
	{
		ray->side = dda_loop(&current, ray);
		if (is_door(current, data) == D_CLOSED)
			if (dda_door_ray(ray, &data->player, current))
				return ;
	}
	if (ray->side == 0)
		ray->distance = ray->length.x - ray->step_size.x;
	else
		ray->distance = ray->length.y - ray->step_size.y;
}
