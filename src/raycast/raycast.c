/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz <rvaz@student.42lisboa.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 18:41:12 by rvaz              #+#    #+#             */
/*   Updated: 2024/01/26 01:09:33 by rvaz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/**
 * @brief	Converts the distance from the player to the wall to the wall height
 * 			in pixels.
*/
static double	get_wall_height(double wall_distance)
{
	double	OldValue = wall_distance;
	double	OldMin = 0;
	double	OldMax = 30;
	double	NewMin = WIN_HEIGHT;
	double	NewMax = 1;
	
	return ((((OldValue - OldMin) * (NewMax - NewMin)) / (OldMax - OldMin)) + NewMin);
}

/**
 * @brief	The raycast main function
*/
void	raycast(t_data *data)
{
	int			r;
	t_ray		ray;
	double		angle_step;

	r = 0;
	ray.dir = (t_2d_point){data->player.dir.x, data->player.dir.y};
	angle_step = data->player.fov / WIN_WIDTH;
	while (r < WIN_WIDTH)
	{

		rotate_point(&ray.dir, angle_step);
		if (DEBUG == 2)
		{
			printf("%d.\t", r);
			printf("new_dist: %f\n", get_wall_height(dda(&data->player.pos, &ray, data)));
		}
		else
		{
			get_wall_height(dda(&data->player.pos, &ray, data));
		}
		r++;
	}
}
