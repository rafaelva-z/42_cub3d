/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz <rvaz@student.42lisboa.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 22:27:02 by fda-estr          #+#    #+#             */
/*   Updated: 2024/02/22 13:45:30 by rvaz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	rotate_enemy(t_sprite *enemy, double angle)
{
	rotate_point(&enemy->dir, angle);
	rotate_point(&enemy->coliders[0], angle);
	rotate_point(&enemy->coliders[1], angle);
}