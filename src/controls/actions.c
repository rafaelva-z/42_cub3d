/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz <rvaz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 14:59:53 by rvaz              #+#    #+#             */
/*   Updated: 2024/03/18 16:26:07 by rvaz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/**
 * @brief	Updates the player's movement direction based on the keys pressed
*/
static void	calc_move_dir(t_player *player)
{
	if (player->actions & 1 << MOVE_FORWARD_B
		&& !(player->actions & 1 << MOVE_BACK_B))
		player->mov_dir = player->dir;
	if (player->actions & 1 << MOVE_BACK_B
		&& !(player->actions & 1 << MOVE_FORWARD_B))
		player->mov_dir = vector_add(player->mov_dir,
				vector_rotate(player->dir, 180));
	if (player->actions & 1 << MOVE_RIGHT_B
		&& !(player->actions & 1 << MOVE_LEFT_B))
		player->mov_dir = vector_add(player->mov_dir,
				vector_rotate(player->dir, 90));
	if (player->actions & 1 << MOVE_LEFT_B
		&& !(player->actions & 1 << MOVE_RIGHT_B))
		player->mov_dir = vector_add(player->mov_dir,
				vector_rotate(player->dir, -90));
}

/**
 * @brief	Updates the player's position based on the movement direction
*/
int	move_player(t_data *data)
{
	t_player	*player;
	uint64_t	time;
	t_point		pos_to_check;

	time = get_timestamp(data) - data->curr_time;
	player = &data->player;
	if (!player->actions)
		return (0);
	player->mov_dir = (t_point){0, 0};
	calc_move_dir(player);
	vector_norm(&player->mov_dir);
	player->mov_dir = (t_point){player->mov_dir.x * MOVE_SPD,
		player->mov_dir.y * MOVE_SPD};
	pos_to_check = vector_add(player->mov_dir,
			vector_add(player->pos, player->mov_dir));
	if (!is_wall(pos_to_check, data) && is_door(pos_to_check, data) <= 1)
	{
		player->pos = vector_add(player->pos, player->mov_dir);
		return (1);
	}
	return (0);
}

/**
 * @brief	Updates the player's rotation based on the keys pressed
*/
int	rotate_player(t_player *player)
{
	if (player->actions & 1 << ROT_B && player->actions & 1 << RROT_B)
		return (0);
	if (player->actions & 1 << ROT_B)
	{
		rotate_point(&player->dir, ROT_SPD);
		rotate_point(&player->plane, ROT_SPD);
	}
	else if (player->actions & 1 << RROT_B)
	{
		rotate_point(&player->dir, -ROT_SPD);
		rotate_point(&player->plane, -ROT_SPD);
	}
	return (1);
}

void	toggle_mouse(t_data *data)
{
	data->player.mouse_toggle = !data->player.mouse_toggle;
}

void	door_interactions(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->sprite_amt)
	{
		if (data->sprites[i].type != SPRT_DOOR || (data->sprites[i].type
				== SPRT_DOOR && data->sprites[i].state == D_MOVING))
			continue ;
		if (data->sprites[i].dist_player < 1.5
			&& data->sprites[i].dist_player > (double)0.55)
		{
			if (data->sprites[i].state == D_CLOSED)
			{
				data->sprites[i].state = D_OPENING;
				data->sprites[i].current_frame = 0;
			}
			else if (data->sprites[i].state == D_OPEN)
			{
				data->sprites[i].state = D_CLOSING;
				data->sprites[i].current_frame = 6;
			}
			data->map.map[(int)data->sprites[i].pos.y]
			[(int)data->sprites[i].pos.x] = MAP_MOVING_DOOR;
		}
	}
}
