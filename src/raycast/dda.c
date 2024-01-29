/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz <rvaz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 17:06:39 by rvaz              #+#    #+#             */
/*   Updated: 2024/01/29 19:18:49 by rvaz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	dda_def_step_ray(t_player *player, t_2d_point *step_size,
		t_2d_point *raylen, t_2d_point *step, t_ray *ray)
{
	if (ray->dir.x < 0)
	{
		step->x = -1;
		raylen->x = (player->pos.x - floor(player->pos.x)) * step_size->x;
	}
	else
	{
		step->x = 1;
		raylen->x = ((floor(player->pos.x) + 1) - player->pos.x) * step_size->x;
	}
	if (ray->dir.y < 0)
	{
		step->y = -1;
		raylen->y = (player->pos.y - floor(player->pos.y)) * step_size->y;
	}
	else
	{
		step->y = 1;
		raylen->y = ((floor(player->pos.y) + 1) - player->pos.y) * step_size->y;
	}
}

double	dda(t_2d_point *start, t_ray *ray, t_data *data)
{
	t_2d_point	current;
	t_2d_point	step_size;
	t_2d_point	step;
	t_2d_point	ray_len;

	ray->distance = 0;
	step_size.x = fabs(1.0 / ray->dir.x);
    step_size.y = fabs(1.0 / ray->dir.y);
	//printf("step_size: %f, %f\n", step_size.x, step_size.y);
	current = (t_2d_point){start->x, start->y};
	dda_def_step_ray(&data->player, &step_size, &ray_len, &step, ray);
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
	{
		//printf("hit wall: %f, %f | ", current.x, current.y);
		//printf("start: %f, %f\n", start->x, start->y);
		//printf("ray_len: %f, %f | ", ray_len.x, ray_len.y);
		//printf("step_size: %f, %f\n", step_size.x, step_size.y);
		printf("Dist: %f (x)%f (y)%f [%d, %d]\n====================================\n", ray->distance, current.x, current.y, (int)current.x, (int)current.y);
	}
	return (ray->distance);
}
