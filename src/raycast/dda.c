/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-estr <fda-estr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 17:06:39 by rvaz              #+#    #+#             */
/*   Updated: 2024/02/20 16:20:15 by fda-estr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/**
 *	@brief	Initializes "step" based on the ray direction, and "raylen" to the
 *			ray starting position based on the current map cell.
*/
static void	dda_start(t_player *player, t_point *step_size,
		t_point *raylen, t_point *step, t_ray *ray)
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

static void	raycast_loop(t_point *current, t_point *raylen,
		t_point *step, int *side, t_point *step_size)
{
	if (raylen->x < raylen->y)
	{
		raylen->x += step_size->x;
		current->x += step->x;
		*side = 0;
	}
	else
	{
		raylen->y += step_size->y;
		current->y += step->y;
		*side = 1;
	}
}

/**
 *	@brief	Digital Differential Analyzer - This algorithm calculates the
 			length from the starting point to the nearest wall in a straight
			line.
*/

void	dda_enemy(t_ray *ray, t_data *data)
{
	t_point	current;
	t_point	step_size;
	t_point	step;
	t_point	ray_len;

	ray->distance = 0;
	step_size.x = fabs(1.0 / ray->dir.x);
	step_size.y = fabs(1.0 / ray->dir.y);
	current = (t_point){data->player.pos.x, data->player.pos.y};
	dda_start(&data->player, &step_size, &ray_len, &step, ray);
	while (is_inside_map(current, data->map.size) && !is_wall(current, data))
	{
		raycast_loop(&current, &ray_len, &step, &ray->side, &step_size);
		if (is_player(current, data))
		{
			ray->distance = -1;
			return ;
		}
	}
}

void	dda(t_ray *ray, t_data *data)
{
	t_point	current;
	t_point	step_size;
	t_point	step;
	t_point	ray_len;

	step_size.x = fabs(1.0 / ray->dir.x);
	step_size.y = fabs(1.0 / ray->dir.y);
	current = (t_point){data->player.pos.x, data->player.pos.y};
	dda_start(&data->player, &step_size, &ray_len, &step, ray);
	while (is_inside_map(current, data->map.size) && !is_wall(current, data))
		raycast_loop(&current, &ray_len, &step, &ray->side, &step_size);
	if (ray->side == 0)
		ray->distance = ray_len.x - step_size.x;
	else
		ray->distance = ray_len.y - step_size.y;
}
