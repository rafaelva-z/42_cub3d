/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_sprite.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz <rvaz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 18:53:27 by rvaz              #+#    #+#             */
/*   Updated: 2024/03/12 18:08:26 by rvaz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	update_door_sprite(t_data *data, t_sprite *sprites)
{
	if (sprites->state == D_CLOSED || sprites->state == D_OPEN)
		return ;
	else if (sprites->state == D_OPENING)
		sprites->current_frame++;
	else if (sprites->state == D_CLOSING)
		sprites->current_frame--;
	if (sprites->current_frame > 6)
	{
		sprites->state = D_OPEN;
		sprites->current_frame = 0;
		data->map.map[(int)sprites->pos.y][(int)sprites->pos.x] = MAP_EMPTY;
	}
	else if (sprites->current_frame < 0)
	{
		sprites->state = D_CLOSED;
		sprites->current_frame = 0;
		data->map.map[(int)sprites->pos.y][(int)sprites->pos.x] = MAP_DOOR;
	}
}

void	update_sprite(t_data *data, t_sprite *sprites, int sprite_amt)
{
	int	i;

	i = -1;
	while (++i < sprite_amt)
	{
		if (sprites[i].type == SPRT_DOOR)
			update_door_sprite(data, &sprites[i]);
		else
		{
			sprites[i].current_frame++;
			if (sprites[i].current_frame > 6)
				sprites[i].current_frame = 0;
		}
	}
}
