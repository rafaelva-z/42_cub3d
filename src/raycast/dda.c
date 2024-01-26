/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz <rvaz@student.42lisboa.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 17:06:39 by rvaz              #+#    #+#             */
/*   Updated: 2024/01/26 03:20:18 by rvaz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	dda_def_step_ray(t_player *player, t_2d_point *step_size,
		t_2d_point *ray, t_2d_point *step)
{
	if (player->dir.x < 0)
	{
		step->x = -1;
		ray->x = (player->pos.x - ceil(player->pos.x)) * step_size->x;
	}
	else
	{
		step->x = 1;
		ray->x = ((ceil(player->pos.x) + 1) - player->pos.x) * step_size->x;
	}
	if (player->dir.y < 0)
	{
		step->y = -1;
		ray->y = (player->pos.y - ceil(player->pos.y)) * step_size->y;
	}
	else
	{
		step->y = 1;
		ray->y = ((ceil(player->pos.y) + 1) - player->pos.y) * step_size->y;
	}
}

double	dda(t_2d_point *start, t_ray *ray, t_data *data)
{
	t_2d_point	current;
	t_2d_point	step_size;
	t_2d_point	step;
	t_2d_point	ray_len;

	ray->distance = 0;
	step_size.x = sqrt(1 + (ray->dir.y / ray->dir.x) * (ray->dir.y / ray->dir.x));
	step_size.y = sqrt(1 + (ray->dir.x / ray->dir.y) * (ray->dir.x / ray->dir.y));
	current = (t_2d_point){start->x, start->y};
	dda_def_step_ray(&data->player, &step_size, &ray_len, &step);
	// Make functions for these checks \/ (is_wall() && is_inside_map())
	while (is_inside_map(current, data->map.size) && !is_wall(current, data))
	{
		if (ray_len.x < ray_len.y)
		{
			current.x += step.x;
			ray->distance = ray_len.x;
			ray_len.x += step_size.x;
		}
		else
		{
			current.y += step.y;
			ray->distance = ray_len.y;
			ray_len.y += step_size.y;
		}
	}
	ray->last_hit = current;
	if (DEBUG == 2)
		printf("Dist: %f (x)%f (y)%f [%d, %d]\t", ray->distance, current.x, current.y, (int)current.x, (int)current.y);
	return (ray->distance);
}
