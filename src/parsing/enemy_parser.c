/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-estr <fda-estr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 22:37:41 by fda-estr          #+#    #+#             */
/*   Updated: 2024/02/20 21:18:10 by fda-estr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	enemy_init(t_data *data, int y, int x)
{
	int				ran;
	struct timeval	time;
	int				index;
	
	if (gettimeofday(&time, NULL) < 0)
		free_and_exit(data, ERR_TIME, 1);
	srand(time.tv_usec);
	ran = rand() % 7;
	index = data->sprite_amt;
	data->sprites[index].texture = data->textures[EB0_IMG];
	data->sprites[index].pos = (t_point){x + 0.5, y + 0.5};
	data->sprites[index].dir = (t_point){1, 0};
	data->sprites[index].current_frame = ran;
	data->sprites[index].type = SPRT_ENEMY;
	data->sprites[index].coliders[0].x = 0.60 * data->sprites[index].dir.x;
	data->sprites[index].coliders[0].y = 0.60 * data->sprites[index].dir.y;
	rotate_point(&data->sprites[index].coliders[0], 45);
	data->sprites[index].coliders[1].x = 0.60 * data->sprites[index].dir.x;
	data->sprites[index].coliders[1].y = 0.60 * data->sprites[index].dir.y;
	rotate_point(&data->sprites[index].coliders[1], -45);
	data->sprite_order[index] = index;
	data->sprites[index].move = false;
	data->sprites[index].follow = false;
	data->sprite_amt++;
	}

static void	door_init(t_data *data, int i, int j)
{
	int index;
	
	index = data->sprite_amt;
	data->sprites[index].texture = data->textures[EB0_IMG];
	data->sprites[index].pos = (t_point){i , j };
	data->sprites[index].dir = (t_point){0, 0};
	data->sprites[index].current_frame = D0_IMG;
	data->sprites[index].type = SPRT_DOOR;
	data->sprites[index].coliders[0] = data->sprites[index].dir;
	data->sprites[index].coliders[1] = data->sprites[index].dir;
	data->sprites[index].move = false;
	data->sprites[index].follow = false;
	data->sprite_order[index] = index;
	data->sprite_amt++;
}

void	enemy_parser(t_data *data)
{
	int	i;
	int	j;

	data->sprite_amt = matrix_finder(data->map.map, "MD");
	data->sprites = calloc(data->sprite_amt, sizeof(t_sprite));
	data->sprite_order = calloc(data->sprite_amt, sizeof(int));
	data->sprite_amt = 0;
	i = -1;
	while (data->map.map[++i])
	{
		j = -1;
		while (data->map.map[i][++j])
		{
			if (data->map.map[i][j] == 'M')
			{
				enemy_init(data, i, j);
				data->map.map[i][j] = '0';
			}
			if (data->map.map[i][j] == 'D')
				door_init(data, i, j);
		}
	}

	
		
}