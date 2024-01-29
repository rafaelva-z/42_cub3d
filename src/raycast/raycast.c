/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz <rvaz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 18:41:12 by rvaz              #+#    #+#             */
/*   Updated: 2024/01/29 19:44:46 by rvaz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/**
 * @brief	Converts the distance from the player to the wall to the wall height
 * 			in pixels.
*/
static double	get_wall_height(double wall_distance)
{
	if (wall_distance > WIN_HEIGHT)
		return (WIN_HEIGHT);
	else
		return (WIN_HEIGHT / wall_distance);
		
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
	//		rotate_point(&ray.dir, -data->player.fov / 2);
	//		angle_step = data->player.fov / WIN_WIDTH;
	r = -WIN_WIDTH / 2; 
	while (r < WIN_WIDTH / 2)
	{
		ray.dir = (t_2d_point){data->player.dir.x, data->player.dir.y};
		//		rotate_point(&ray.dir, angle_step);
		if (r)
			angle_step = r * (data->player.fov / WIN_WIDTH);
		else
			angle_step = 0;
		rotate_point(&ray.dir, angle_step);
		int	sky_size;
		int	wall_height;
			//	The '* cos(...)' is to fix the curvy lines 
			//	before -> wall_height = get_wall_height(dda(&data->player.pos, &ray, data));
		wall_height = get_wall_height(dda(&data->player.pos, &ray, data) * cos(atan2(ray.dir.y, ray.dir.x) - atan2(data->player.dir.y, data->player.dir.x))) / (data->player.fov * 0.0151);
		sky_size = ((WIN_HEIGHT - wall_height) / 2) + data->player.vertical;
		if (sky_size + wall_height > WIN_HEIGHT)
			sky_size = WIN_HEIGHT - wall_height;
		else if (sky_size <= 0)
			sky_size = 1;
		draw_line((t_2d_point){r + WIN_WIDTH / 2, 0},
			sky_size, data->img, SKY_COLOR);
		draw_line((t_2d_point){r + WIN_WIDTH / 2, sky_size + wall_height},
			WIN_HEIGHT - (sky_size + wall_height), data->img, FLOOR_COLOR);
		draw_line((t_2d_point){r + WIN_WIDTH / 2, sky_size},
			wall_height, data->img, 0);
		r++;
	}
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img->img, 0, 0);
}

/** NOTE 
*	- Looks like it is possible to enter a wall trough the corner
*/