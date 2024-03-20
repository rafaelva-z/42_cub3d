/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz <rvaz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 13:11:16 by fda-estr          #+#    #+#             */
/*   Updated: 2024/03/20 14:49:10 by rvaz             ###   ########.fr       */
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
	data->sprites[index].state = E_IDLE;
	data->sprites[index].follow_timer = 0;
	data->sprt_order[index] = index;
	data->sprite_amt++;
}

static void	door_init(t_data *data, int i, int j)
{
	int	index;

	index = data->sprite_amt;
	data->sprites[index].texture = data->textures[EB0_IMG];
	data->sprites[index].pos = (t_point){j + 0.5, i + 0.5};
	data->sprites[index].dir = (t_point){0, 0};
	data->sprites[index].current_frame = 0;
	data->sprites[index].type = SPRT_DOOR;
	data->sprites[index].state = D_CLOSED;
	data->sprt_order[index] = index;
	data->sprite_amt++;
}

void	sprite_parser(t_data *data)
{
	int	i;
	int	j;

	data->sprite_amt = matrix_finder(data->map.map, "MD");
	data->sprites = ft_calloc(data->sprite_amt, sizeof(t_sprite));
	data->sprt_order = ft_calloc(data->sprite_amt, sizeof(int));
	data->sprite_amt = 0;
	i = -1;
	while (data->map.map[++i])
	{
		j = -1;
		while (data->map.map[i][++j])
		{
			if (data->map.map[i][j] == MAP_ENEMY)
			{
				enemy_init(data, i, j);
				data->map.map[i][j] = MAP_EMPTY;
			}
			if (data->map.map[i][j] == MAP_DOOR)
				door_init(data, i, j);
		}
	}
}
