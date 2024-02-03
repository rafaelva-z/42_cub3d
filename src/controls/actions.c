/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz <rvaz@student.42lisboa.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 14:59:53 by rvaz              #+#    #+#             */
/*   Updated: 2024/02/03 16:19:12 by rvaz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	move_player(t_data *data)
{
	t_2d_point	newpos;
	t_player	*player;

	// This needs some work
	player = &data->player;
	newpos = (t_2d_point){0, 0};
	if (player->move & 1 << MOVE_FORWARD_B)
	{
		if (!is_wall((t_2d_point){player->pos.x + player->dir.x * MOVE_SPD, player->pos.y}, data))
			newpos.x = MOVE_SPD;
		if (!is_wall((t_2d_point){player->pos.x, player->pos.y + player->dir.y * MOVE_SPD}, data))
			newpos.y = MOVE_SPD;
		if ((newpos.x && newpos.y) && is_wall((t_2d_point){player->pos.x + player->dir.x * newpos.x, player->pos.y + player->dir.y * newpos.y}, data))
			return (0);
		else
			player->pos = (t_2d_point){player->pos.x + player->dir.x * newpos.x, 
											player->pos.y + player->dir.y * newpos.y};
	}
	else if (player->move & 1 << MOVE_BACK_B)
	{
		if (!is_wall((t_2d_point){player->pos.x - player->dir.x * MOVE_SPD, player->pos.y}, data))
			newpos.x = MOVE_SPD;
		if (!is_wall((t_2d_point){player->pos.x, player->pos.y - player->dir.y * MOVE_SPD}, data))
			newpos.y = MOVE_SPD;
		if ((newpos.x && newpos.y) && is_wall((t_2d_point){player->pos.x - player->dir.x * MOVE_SPD, player->pos.y - player->dir.y * MOVE_SPD}, data))
			return (0);
		else
			player->pos = (t_2d_point){player->pos.x - player->dir.x * newpos.x,
											player->pos.y - player->dir.y * newpos.y};
	}
	else if (player->move & 1 << MOVE_LEFT_B)
	{
		if (!is_wall((t_2d_point){player->pos.x + player->dir.y * MOVE_SPD, player->pos.y}, data))
			newpos.x = MOVE_SPD;
		if (!is_wall((t_2d_point){player->pos.x, player->pos.y - player->dir.x * MOVE_SPD}, data))
			newpos.y = MOVE_SPD;
		if ((newpos.x && newpos.y) && is_wall((t_2d_point){player->pos.x + player->dir.y * MOVE_SPD, player->pos.y - player->dir.x * MOVE_SPD}, data))
			return (0);
		else
			player->pos = (t_2d_point){player->pos.x + player->dir.y * newpos.x,
											player->pos.y - player->dir.x * newpos.y};
	}
	else if (player->move & 1 << MOVE_RIGHT_B)
	{
		if (!is_wall((t_2d_point){player->pos.x - player->dir.y * MOVE_SPD, player->pos.y}, data))
			newpos.x = MOVE_SPD;
		if (!is_wall((t_2d_point){player->pos.x, player->pos.y + player->dir.x * MOVE_SPD}, data))
			newpos.y = MOVE_SPD;
		if ((newpos.x && newpos.y) && is_wall((t_2d_point){player->pos.x - player->dir.y * MOVE_SPD, player->pos.y + player->dir.y * MOVE_SPD}, data))
			return (0);
		else
			player->pos = (t_2d_point){player->pos.x - player->dir.y * newpos.x,
											player->pos.y + player->dir.x * newpos.y};
	}
	if (newpos.x || newpos.y)
		return (1);
	return (0);
}

int	adjust_fov(t_data *data)
{
	if (data->player.move_cam & 1 << ZOOM_IN_B && data->player.fov > 40)
	{
		data->player.fov -= FOV_SPD;
		data->player.plane = (t_2d_point){data->player.plane.x * 0.9, data->player.plane.y * 0.9};
		return (1);
	}
	else if (data->player.move_cam & 1 << ZOOM_OUT_B && data->player.fov < 150)
	{
		data->player.fov += FOV_SPD;
		data->player.plane = (t_2d_point){data->player.plane.x * 1.111111111, data->player.plane.y * 1.111111111};
		return (1);
	}
	return (0);
}

int	rotate_player(t_data *data)
{
	if (data->player.move_cam & 1 << ROT_B)
	{
		rotate_point(&data->player.dir, ROT_SPD);
		rotate_point(&data->player.plane, ROT_SPD);
	}
	else if (data->player.move_cam & 1 << RROT_B)
	{
		rotate_point(&data->player.dir, -ROT_SPD);
		rotate_point(&data->player.plane, -ROT_SPD);
	}
	return (1);
}

int	vertical_movement(t_data *data)
{
	if (data->player.move_cam & 1 << LOOK_UP_B && data->player.vertical < 250)
	{
		data->player.vertical += VERTICAL_SPD;
		return (1);
	}
	else if (data->player.move_cam & 1 << LOOK_DOWN_B
		&& data->player.vertical > -250)
	{
		data->player.vertical -= VERTICAL_SPD;
		return (1);
	}
	return (0);
}
