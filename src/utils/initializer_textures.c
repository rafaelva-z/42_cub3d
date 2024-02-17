/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer_textures.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz <rvaz@student.42lisboa.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 20:22:12 by fda-estr          #+#    #+#             */
/*   Updated: 2024/02/15 14:31:43 by rvaz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	texture_array_init(t_data *data)
{
	int	i;

	data->textures = malloc(sizeof(t_img *) * 44);
	if (!data->textures)
		free_and_exit(data, ERR_MALLOC, 1);
	i = -1;
	while (++i < 44)
	{
		data->textures[i] = (t_img *)malloc(sizeof(t_img));
		if (!data->textures[i])
			free_and_exit(data, ERR_MALLOC, 1);
		data->textures[i]->img = NULL;
		data->textures[i]->addr = NULL;
		data->textures[i]->bits_per_pixel = 0;
		data->textures[i]->line_length = 0;
		data->textures[i]->endian = 0;
		data->textures[i]->height = 0;
		data->textures[i]->width = 0;
		data->textures[i]->color_grid = NULL;
	}	
}

