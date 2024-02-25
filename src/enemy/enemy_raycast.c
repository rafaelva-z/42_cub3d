/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_raycast.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz <rvaz@student.42lisboa.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 17:35:38 by rvaz              #+#    #+#             */
/*   Updated: 2024/02/24 17:35:53 by rvaz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	rc_enemy(t_data *data, t_sprite *enemy)
{
	t_ray		ray;
	int			r;

	r = 0;
	ray.dir.x = enemy->dir.x;
	ray.dir.y = enemy->dir.y;
	rotate_point(&ray.dir, -(ENEMY_FOV / 2));
	while (r < ENEMY_FOV)
	{
		dda_enemy(&ray, data);
		if (ray.distance == -1)
		{
			enemy->state = E_FOLLOW;
			return ;
		}
		rotate_point(&ray.dir, 1);
		r++;
	}
}