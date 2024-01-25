/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz <rvaz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 18:41:12 by rvaz              #+#    #+#             */
/*   Updated: 2024/01/25 15:15:15 by rvaz             ###   ########.fr       */
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
	t_2d_point	ray_dir;
	double		angle_step;

	//Provisory map and variable values
	data->map.map = malloc(sizeof(char **) * 11);
	data->map.map[0] = ft_strdup("1111111111");
	data->map.map[1] = ft_strdup("1000000001");
	data->map.map[2] = ft_strdup("1000000001");
	data->map.map[3] = ft_strdup("1000000101");
	data->map.map[4] = ft_strdup("1000000011");
	data->map.map[5] = ft_strdup("1000000001");
	data->map.map[6] = ft_strdup("1000000001");
	data->map.map[7] = ft_strdup("1000000001");
	data->map.map[8] = ft_strdup("1000000001");
	data->map.map[9] = ft_strdup("1111111111");
	data->map.map[10] = NULL;
	data->player.fov = 66;
	data->player.pos = (t_2d_point){6, 7};
	data->player.dir = (t_2d_point){0, -1};
	data->map.size = (t_2d_point){10, 10};
	//end of provisory map and variable values
	r = 0;
	ray_dir = (t_2d_point){data->player.dir.x, data->player.dir.y};
	angle_step = data->player.fov / WIN_WIDTH;
	while (r < WIN_WIDTH)
	{
		rotate_point(&ray_dir, angle_step);
		printf("%d.\t", r);
		printf("new_dist: %f\n", get_wall_height(dda(&data->player.pos, &ray_dir, data)));
		r++;
	}
}
