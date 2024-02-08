/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer_textures.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-estr <fda-estr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 20:22:12 by fda-estr          #+#    #+#             */
/*   Updated: 2024/02/06 20:38:55 by fda-estr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	initializer_textures(t_data *data)
{
	data->image.enemy_front = malloc(sizeof(t_img *) * 7);
	if (data->image.enemy_front)
		free_and_exit(data, ERR_MALLOC, 1);
	data->image.enemy_back = malloc(sizeof(t_img *) * 7);
	if (data->image.enemy_back)
		free_and_exit(data, ERR_MALLOC, 1);
	data->image.enemy_left = malloc(sizeof(t_img *) * 7);
	if (data->image.enemy_left)
		free_and_exit(data, ERR_MALLOC, 1);
	data->image.enemy_right = malloc(sizeof(t_img *) * 7);
	if (data->image.enemy_right)
		free_and_exit(data, ERR_MALLOC, 1);
}