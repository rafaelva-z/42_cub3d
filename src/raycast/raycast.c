/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz <rvaz@student.42lisboa.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 18:41:12 by rvaz              #+#    #+#             */
/*   Updated: 2024/01/26 15:50:59 by rvaz             ###   ########.fr       */
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
	double	OldMin = 1;
	double	OldMax = 30;
	double	NewMin = WIN_HEIGHT - 2;
	double	NewMax = 1;
	double	NewValue;

	NewValue = (((OldValue - OldMin) * (NewMax - NewMin)) / (OldMax - OldMin)) + NewMin;
	if (NewValue < NewMax)
		NewValue = NewMax;
	else if (NewValue > NewMin)
		NewValue = NewMin;
	return (NewValue);
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
	rotate_point(&ray.dir, -data->player.fov / 2);
	angle_step = data->player.fov / WIN_WIDTH;
	while (r < WIN_WIDTH)
	{
		rotate_point(&ray.dir, angle_step);
		int	wall_height;
		//wall_height = get_wall_height(dda(&data->player.pos, &ray, data));
		//the '* cos(...)' is to fix the curvy lines 
		wall_height = get_wall_height(dda(&data->player.pos, &ray, data) * cos(atan2(ray.dir.y, ray.dir.x) - atan2(data->player.dir.y, data->player.dir.x)));

		draw_line((t_vector){(t_2d_point){r, 1},
			(t_2d_point){r, (WIN_HEIGHT - wall_height) / 2}}, data->img, SKY_COLOR);
		draw_line((t_vector){(t_2d_point){r, (WIN_HEIGHT - wall_height) / 2},
			(t_2d_point){r, (WIN_HEIGHT + wall_height) / 2}}, data->img, WALL_COLOR);
		draw_line((t_vector){(t_2d_point){r, (WIN_HEIGHT - (WIN_HEIGHT - wall_height) / 2)},
			(t_2d_point){r, (WIN_HEIGHT)}}, data->img, FLOOR_COLOR);
		r++;
	}
}
