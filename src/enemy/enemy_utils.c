/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-estr <fda-estr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 22:27:02 by fda-estr          #+#    #+#             */
/*   Updated: 2024/02/25 17:15:04 by fda-estr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	rotate_enemy(t_sprite *enemy, double angle)
{
	rotate_point(&enemy->dir, angle);
	rotate_point(&enemy->coliders[0], angle);
	rotate_point(&enemy->coliders[1], angle);
}

double	distance_calc(t_point p1, t_point p2)
{
	double	dist;

	dist = sqrt(pow((p2.x - p1.x), 2) + pow((p2.y - p1.y), 2));
	return (dist);
}

void	get_colid_pos(t_point *cld_pos_1, t_point *cld_pos_2, t_sprite *spt)
{
	cld_pos_1->x = spt->coliders[0].x + spt->pos.x;
	cld_pos_1->y = spt->coliders[0].y + spt->pos.y;
	cld_pos_2->x = spt->coliders[1].x + spt->pos.x;
	cld_pos_2->y = spt->coliders[1].y + spt->pos.y;
}
