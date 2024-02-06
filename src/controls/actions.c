/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz <rvaz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 14:59:53 by rvaz              #+#    #+#             */
/*   Updated: 2024/02/06 19:36:29 by rvaz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	move_player(t_data *data)
{
	// Implementing new movement system with movement vector

	t_2d_point	new_dir;
	t_player	*player;

	player = &data->player;
	new_dir = player->mov_dir;
	if (player->move & 1 << MOVE_FORWARD_B)
	{
		player->mov_dir = player->dir;
		// vector_norm(&player->mov_dir);
		player->mov_dir = (t_2d_point){player->mov_dir.x * 0.5, player->mov_dir.x * 0.5};
		// if (!is_wall(vector_add(player->pos, player->mov_dir), data))
			player->pos = vector_add(player->pos, player->mov_dir);
	}
	else if (player->move & 1 << MOVE_BACK_B)
	{
		new_dir = player->mov_dir;
		rotate_point(&new_dir, 90);
		// player->mov_dir = vector_add(player->mov_dir, );
	}
	return (1);

	// OLD

	// This needs some work
	// if (player->move & 1 << MOVE_FORWARD_B)
	// {
	// 	if (!is_wall((t_2d_point){player->pos.x + player->dir.x * MOVE_SPD, player->pos.y}, data))
	// 		newpos.x = MOVE_SPD;
	// 	if (!is_wall((t_2d_point){player->pos.x, player->pos.y + player->dir.y * MOVE_SPD}, data))
	// 		newpos.y = MOVE_SPD;
	// 	if ((newpos.x && newpos.y) && is_wall((t_2d_point){player->pos.x + player->dir.x * newpos.x, player->pos.y + player->dir.y * newpos.y}, data))
	// 		return (0);
	// 	else
	// 		player->pos = (t_2d_point){player->pos.x + player->dir.x * newpos.x, 
	// 										player->pos.y + player->dir.y * newpos.y};
	// }
	// else if (player->move & 1 << MOVE_BACK_B)
	// {
	// 	if (!is_wall((t_2d_point){player->pos.x - player->dir.x * MOVE_SPD, player->pos.y}, data))
	// 		newpos.x = MOVE_SPD;
	// 	if (!is_wall((t_2d_point){player->pos.x, player->pos.y - player->dir.y * MOVE_SPD}, data))
	// 		newpos.y = MOVE_SPD;
	// 	if ((newpos.x && newpos.y) && is_wall((t_2d_point){player->pos.x - player->dir.x * MOVE_SPD, player->pos.y - player->dir.y * MOVE_SPD}, data))
	// 		return (0);
	// 	else
	// 		player->pos = (t_2d_point){player->pos.x - player->dir.x * newpos.x,
	// 										player->pos.y - player->dir.y * newpos.y};
	// }
	// else if (player->move & 1 << MOVE_LEFT_B)
	// {
	// 	if (!is_wall((t_2d_point){player->pos.x + player->dir.y * MOVE_SPD, player->pos.y}, data))
	// 		newpos.x = MOVE_SPD;
	// 	if (!is_wall((t_2d_point){player->pos.x, player->pos.y - player->dir.x * MOVE_SPD}, data))
	// 		newpos.y = MOVE_SPD;
	// 	if ((newpos.x && newpos.y) && is_wall((t_2d_point){player->pos.x + player->dir.y * MOVE_SPD, player->pos.y - player->dir.x * MOVE_SPD}, data))
	// 		return (0);
	// 	else
	// 		player->pos = (t_2d_point){player->pos.x + player->dir.y * newpos.x,
	// 										player->pos.y - player->dir.x * newpos.y};
	// }
	// else if (player->move & 1 << MOVE_RIGHT_B)
	// {
	// 	if (!is_wall((t_2d_point){player->pos.x - player->dir.y * MOVE_SPD, player->pos.y}, data))
	// 		newpos.x = MOVE_SPD;
	// 	if (!is_wall((t_2d_point){player->pos.x, player->pos.y + player->dir.x * MOVE_SPD}, data))
	// 		newpos.y = MOVE_SPD;
	// 	if ((newpos.x && newpos.y) && is_wall((t_2d_point){player->pos.x - player->dir.y * MOVE_SPD, player->pos.y + player->dir.y * MOVE_SPD}, data))
	// 		return (0);
	// 	else
	// 		player->pos = (t_2d_point){player->pos.x - player->dir.y * newpos.x,
	// 										player->pos.y + player->dir.x * newpos.y};
	// }
	// if (newpos.x || newpos.y)
	// 	return (1);
	// return (0);
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

