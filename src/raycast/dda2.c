/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz <rvaz@student.42lisboa.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 19:37:32 by rvaz              #+#    #+#             */
/*   Updated: 2024/02/24 18:27:25 by rvaz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	dda_door(t_ray *ray, t_data *data)
{
	t_point	current;

	ray->step_size.x = fabs(1.0 / ray->dir.x);
	ray->step_size.y = fabs(1.0 / ray->dir.y);
	current = (t_point){data->player.pos.x, data->player.pos.y};
	dda_start(&data->player, ray);
	while (is_inside_map(current, data->map.size) && !is_wall(current, data))
	{
		ray->side = dda_loop(&current, ray);
		if (is_door(current, data) == D_MOVING)
			if (dda_door_ray(ray, &data->player, current))
				return ;
	}
	ray->distance = -1;
}

int	dda_door_ray_case1(t_ray *ray, t_player *player, t_ray *ray_copy)
{
	double	wall_x;

	if (ray->side == 1)
	{
		wall_x = player->pos.x + (ray_copy->length.y - ray->step_size.y)
			* ray->dir.x;
		wall_x -= floor(wall_x);
		if (ray->dir.x > 0)
			wall_x = 1 - wall_x;
		if (wall_x > 0.5)
			ray->distance = ray_copy->length.y - ray->step_size.y;
		else
		{
			ray->side = 3;
			ray->distance = ray_copy->length.x - 0.5 * ray->step_size.x;
		}
	}
	else
	{
		ray->side = 3;
		ray->distance = ray_copy->length.x - 1.5 * ray->step_size.x;
	}
	return (1);
}

int	dda_door_ray_case2(t_ray *ray, t_player *player, t_ray *ray_copy)
{
	double	wall_x;

	if (ray->side == 1)
	{
		ray->side = 4;
		ray->distance = ray_copy->length.y - 1.5 * ray->step_size.y;
	}
	else
	{
		wall_x = player->pos.y + (ray_copy->length.x - ray->step_size.x)
			* ray->dir.y;
		wall_x -= floor(wall_x);
		if (ray->dir.y > 0)
			wall_x = 1 - wall_x;
		if (wall_x > 0.5)
			ray->distance = ray_copy->length.x - ray->step_size.x;
		else
		{
			ray->side = 4;
			ray->distance = ray_copy->length.y - 0.5 * ray->step_size.y;
		}
	}
	return (1);
}

int	dda_door_ray(t_ray *ray, t_player *player, t_point current)
{
	int		side;
	t_ray	ray_copy;

	side = ray->side;
	ray_copy = *ray;
	ray->side = dda_loop(&current, &ray_copy);
	if (side == 0)
		return (dda_door_ray_case1(ray, player, &ray_copy));
	else if (side == 1)
		return (dda_door_ray_case2(ray, player, &ray_copy));
	return (0);
}
