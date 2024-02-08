/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz <rvaz@student.42lisboa.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 14:59:53 by rvaz              #+#    #+#             */
/*   Updated: 2024/02/08 12:40:36 by rvaz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	move_player(t_data *data)
{
	// Implementing new movement system with movement vector

	t_player	*player;

	player = &data->player;
	if (!player->move)
		return (0);
	player->mov_dir = (t_2d_point){0, 0};
	if (player->move & 1 << MOVE_FORWARD_B && !(player->move & 1 << MOVE_BACK_B))
		player->mov_dir = player->dir;
	if (player->move & 1 << MOVE_BACK_B && !(player->move & 1 << MOVE_FORWARD_B))
		player->mov_dir = vector_add(player->mov_dir, vector_rotate(player->dir, 180));
	if (player->move & 1 << MOVE_RIGHT_B && !(player->move & 1 << MOVE_LEFT_B))
		player->mov_dir = vector_add(player->mov_dir, vector_rotate(player->dir, 90));
	if (player->move & 1 << MOVE_LEFT_B && !(player->move & 1 << MOVE_RIGHT_B))
		player->mov_dir = vector_add(player->mov_dir, vector_rotate(player->dir, -90));
	vector_norm(&player->mov_dir);
	player->mov_dir = (t_2d_point){player->mov_dir.x * MOVE_SPD, player->mov_dir.y * MOVE_SPD};
	//printf("player->pos: %f %f\n", player->pos.x, player->pos.y);
	//printf("result: %f %f\n", vector_add(player->mov_dir, vector_add(player->pos, player->mov_dir)));
	if (!is_wall(vector_add(player->mov_dir, vector_add(player->pos, player->mov_dir)), data))
	{
		player->pos = vector_add(player->pos, player->mov_dir);
		return (1);
	}
	return (0);
}

int	adjust_fov(t_player *player)
{
	// find a better way to actually change fov
	if (player->move_cam & 1 << ZOOM_IN_B && player->plane.x < 10)
	{
		player->fov -= FOV_SPD;
		player->plane = (t_2d_point){player->plane.x * 0.9, player->plane.y * 0.9};
		return (1);
	}
	else if (player->move_cam & 1 << ZOOM_OUT_B && player->fov < 150)
	{
		player->fov += FOV_SPD;
		player->plane = (t_2d_point){player->plane.x * 1.111111111, player->plane.y * 1.111111111};
		return (1);
	}
	return (0);
}

int	rotate_player(t_player *player)
{
	if (player->move_cam & 1 << ROT_B)
	{
		rotate_point(&player->dir, ROT_SPD);
		rotate_point(&player->plane, ROT_SPD);
	}
	else if (player->move_cam & 1 << RROT_B)
	{
		rotate_point(&player->dir, -ROT_SPD);
		rotate_point(&player->plane, -ROT_SPD);
	}
	return (1);
}

int	vertical_movement(t_player *player)
{
	if (player->move_cam & 1 << LOOK_UP_B && player->vertical < 250)
	{
		player->vertical += VERTICAL_SPD;
		return (1);
	}
	else if (player->move_cam & 1 << LOOK_DOWN_B
		&& player->vertical > -250)
	{
		player->vertical -= VERTICAL_SPD;
		return (1);
	}
	return (0);
}

void	toggle_mouse(t_data *data)
{
	if (data->player.mouse_toggle)
		mlx_mouse_hide(data->mlx, data->mlx_win);
	else
		mlx_mouse_show(data->mlx, data->mlx_win);
	data->player.mouse_toggle = !data->player.mouse_toggle;
}

