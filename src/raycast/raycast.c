/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz <rvaz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 18:41:12 by rvaz              #+#    #+#             */
/*   Updated: 2024/01/24 18:53:03 by rvaz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	raycast(t_data *data)
{
	int	r;
	t_2d_point	ray_dir;

	// data.player->pos = (t_2d_point){3, 3};
	// data.player->dir = (t_2d_point){0, -1};
	// data.map_size = (t_2d_point){10, 10};
	r = 0;
	ray_dir = data->player.dir;
	while (r < WIN_WIDTH)
	{

		rotate_point(&data->player.dir, 0);
		dda(&data->player.pos, &data->player.dir, &data);
		r++;
	}
}
