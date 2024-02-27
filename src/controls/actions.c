/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-estr <fda-estr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 14:59:53 by rvaz              #+#    #+#             */
/*   Updated: 2024/02/27 19:38:42 by fda-estr         ###   ########.fr       */
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

	player = &data->player;
	if (!player->actions)
		return (0);
	player->mov_dir = (t_point){0, 0};
	calc_move_dir(player);
	vector_norm(&player->mov_dir);
	player->mov_dir = (t_point){player->mov_dir.x * MOVE_SPD,
		player->mov_dir.y * MOVE_SPD};
	if (!is_wall(vector_add(player->mov_dir,
				vector_add(player->pos, player->mov_dir)), data)
		&& is_door(vector_add(player->mov_dir,
				vector_add(player->pos, player->mov_dir)), data) <= 1)
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
	if (data->player.mouse_toggle)
		mlx_mouse_hide(data->mlx, data->mlx_win);
	else
		mlx_mouse_show(data->mlx, data->mlx_win);
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

/**
 * @brief	Updates the player's field of view based on the keys pressed
*/
// int	adjust_fov(t_player *player)
// {
// 	// find a better way to actually change fov
// 	if (player->actions & 1 << ZOOM_IN_B && player->plane.x < 10)
// 	{
// 		player->fov -= FOV_SPD;
// 		player->plane = (t_point){player->plane.x * 0.9, player->plane.y * 0.9};
// 		return (1);
// 	}
// 	else if (player->actions & 1 << ZOOM_OUT_B && player->fov < 150)
// 	{
// 		player->fov += FOV_SPD;
// 		player->plane = (t_point){player->plane.x * 1.111111111,
// 			player->plane.y * 1.111111111};
// 		return (1);
// 	}
// 	return (0);
// }

/**
 * @brief	Updates the player's vertical view based on the keys pressed
*/
// int	vertical_movement(t_player *player)
// {
// 	if (player->actions & 1 << LOOK_UP_B && player->vertical < 100)
// 	{
// 		player->vertical += VERTICAL_SPD;
// 		return (1);
// 	}
// 	else if (player->actions & 1 << LOOK_DOWN_B
// 		&& player->vertical > -100)
// 	{
// 		player->vertical -= VERTICAL_SPD;
// 		return (1);
// 	}
// 	return (0);
// }

/**
 * @brief	Toggles the mouse controls and visibility
*/
