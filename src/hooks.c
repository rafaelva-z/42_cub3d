/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz <rvaz@student.42lisboa.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 18:44:31 by rvaz              #+#    #+#             */
/*   Updated: 2024/02/03 01:51:40 by rvaz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	move_player(int keycode, t_data *data)
{
	t_2d_point	newpos;

	// This needs some work
	newpos = (t_2d_point){0, 0};
	if (keycode == MOVE_FORWARD)
	{
		if (!is_wall((t_2d_point){data->player.pos.x + data->player.dir.x * MOVE_SPD, data->player.pos.y}, data))
			newpos.x = MOVE_SPD;
		if (!is_wall((t_2d_point){data->player.pos.x, data->player.pos.y + data->player.dir.y * MOVE_SPD}, data))
			newpos.y = MOVE_SPD;
		if ((newpos.x && newpos.y) && is_wall((t_2d_point){data->player.pos.x + data->player.dir.x * newpos.x, data->player.pos.y + data->player.dir.y * newpos.y}, data))
			return (0);
		else
			data->player.pos = (t_2d_point){data->player.pos.x + data->player.dir.x * newpos.x, 
											data->player.pos.y + data->player.dir.y * newpos.y};
	}
	else if (keycode == MOVE_BACK)
	{
		if (!is_wall((t_2d_point){data->player.pos.x - data->player.dir.x * MOVE_SPD, data->player.pos.y}, data))
			newpos.x = MOVE_SPD;
		if (!is_wall((t_2d_point){data->player.pos.x, data->player.pos.y - data->player.dir.y * MOVE_SPD}, data))
			newpos.y = MOVE_SPD;
		if ((newpos.x && newpos.y) && is_wall((t_2d_point){data->player.pos.x - data->player.dir.x * MOVE_SPD, data->player.pos.y - data->player.dir.y * MOVE_SPD}, data))
			return (0);
		else
			data->player.pos = (t_2d_point){data->player.pos.x - data->player.dir.x * newpos.x,
											data->player.pos.y - data->player.dir.y * newpos.y};
	}
	else if (keycode == MOVE_LEFT)
	{
		if (!is_wall((t_2d_point){data->player.pos.x + data->player.dir.y * MOVE_SPD, data->player.pos.y}, data))
			newpos.x = MOVE_SPD;
		if (!is_wall((t_2d_point){data->player.pos.x, data->player.pos.y - data->player.dir.x * MOVE_SPD}, data))
			newpos.y = MOVE_SPD;
		if ((newpos.x && newpos.y) && is_wall((t_2d_point){data->player.pos.x + data->player.dir.y * MOVE_SPD, data->player.pos.y - data->player.dir.x * MOVE_SPD}, data))
			return (0);
		else
			data->player.pos = (t_2d_point){data->player.pos.x + data->player.dir.y * newpos.x,
											data->player.pos.y - data->player.dir.x * newpos.y};
	}
	else if (keycode == MOVE_RIGHT)
	{
		if (!is_wall((t_2d_point){data->player.pos.x - data->player.dir.y * MOVE_SPD, data->player.pos.y}, data))
			newpos.x = MOVE_SPD;
		if (!is_wall((t_2d_point){data->player.pos.x, data->player.pos.y + data->player.dir.x * MOVE_SPD}, data))
			newpos.y = MOVE_SPD;
		if ((newpos.x && newpos.y) && is_wall((t_2d_point){data->player.pos.x - data->player.dir.y * MOVE_SPD, data->player.pos.y + data->player.dir.y * MOVE_SPD}, data))
			return (0);
		else
			data->player.pos = (t_2d_point){data->player.pos.x - data->player.dir.y * newpos.x,
											data->player.pos.y + data->player.dir.x * newpos.y};
	}
	if (newpos.x || newpos.y)
	{
		printf("newpos: %f, %f\n", newpos.x, newpos.y);
		return (1);
	}
	return (0);
}

int	adjust_fov(int keycode, t_data *data)
{
	double	adjust_amount;

	adjust_amount = 3;
	if (keycode == ZOOM_IN && data->player.fov > 40)
	{
		data->player.fov -= adjust_amount;
		data->player.plane = (t_2d_point){data->player.plane.x * 0.9, data->player.plane.y * 0.9};
		return (1);
	}
	else if (keycode == ZOOM_OUT && data->player.fov < 150)
	{
		data->player.fov += adjust_amount;
		data->player.plane = (t_2d_point){data->player.plane.x * 1.111111111, data->player.plane.y * 1.111111111};
		return (1);
	}
	return (0);
}

int	rotate_player(int keycode, t_data *data)
{
	double	rot_amount;

	rot_amount = 3;
	if (keycode == ROT)
	{
		rotate_point(&data->player.dir, rot_amount);
		rotate_point(&data->player.plane, rot_amount);
	}
	else if (keycode == RROT)
	{
		rotate_point(&data->player.dir, -rot_amount);
		rotate_point(&data->player.plane, -rot_amount);
	}
	return (1);
}

int	vertical_movement(int keycode, t_data *data)
{
	int	adjust_amount;

	adjust_amount = 10;
	if (keycode == LOOK_UP && data->player.vertical < 250)
	{
		data->player.vertical += adjust_amount;
		return (1);
	}
	else if (keycode == LOOK_DOWN && data->player.vertical > -250)
	{
		data->player.vertical -= adjust_amount;
		return (1);
	}
	return (0);
}

int	key_reader(int keycode, t_data *data)
{
	int	update;

	update = 0;
	if (keycode == KEY_ESC)
		close_pgm(data);
	else if (keycode == MOVE_FORWARD || keycode == MOVE_BACK
		|| keycode == MOVE_LEFT || keycode == MOVE_RIGHT)
		update = move_player(keycode, data);
	else if (keycode == ZOOM_OUT || keycode == ZOOM_IN)
		update = adjust_fov(keycode, data);
	else if (keycode == ROT || keycode == RROT)
		update = rotate_player(keycode, data);
	else if (keycode == LOOK_UP || keycode == LOOK_DOWN)
		update = vertical_movement(keycode, data);
	else
		return (0);
	if (update)
	{
		update_view(data);
		//printf("pos: %f, %f, vertical: %d %d, dir: %f %f, fov %f\n", data->player.pos.x, data->player.pos.y, data->player.vertical, data->player.vertical, data->player.dir.x, data->player.dir.y, data->player.fov);
	}
	return (0);
}

int	close_pgm(t_data *data)
{
	free_and_exit(data, MSG_EXIT, 0);
	return (0);
}
