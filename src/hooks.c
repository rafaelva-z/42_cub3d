/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz <rvaz@student.42lisboa.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 18:44:31 by rvaz              #+#    #+#             */
/*   Updated: 2024/01/31 12:40:34 by rvaz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	move_player(int keycode, t_data *data)
{
	double	move_amt;

	// problem: if a corner is pointing at player and player walks into it, the player goes through wall. Because
	//			even though the path is not clear, the sliding cells to the left and right are free. So it "slides"
	//			both ways going into the wall.
	move_amt = 0.01;
	if (keycode == MOVE_FORWARD)
		data->player.pos = (t_2d_point){data->player.pos.x + data->player.dir.x * (move_amt * !is_wall((t_2d_point){data->player.pos.x + data->player.dir.x * move_amt, data->player.pos.y}, data)), 
										data->player.pos.y + data->player.dir.y * (move_amt * !is_wall((t_2d_point){data->player.pos.x, data->player.pos.y + data->player.dir.y * move_amt}, data))};
	else if (keycode == MOVE_BACK)
		data->player.pos = (t_2d_point){data->player.pos.x - data->player.dir.x * (move_amt * !is_wall((t_2d_point){data->player.pos.x - data->player.dir.x * move_amt, data->player.pos.y}, data)),
										data->player.pos.y - data->player.dir.y * (move_amt * !is_wall((t_2d_point){data->player.pos.x, data->player.pos.y - data->player.dir.y * move_amt}, data))};
	else if (keycode == MOVE_LEFT)
		data->player.pos = (t_2d_point){data->player.pos.x + data->player.dir.y * (move_amt * !is_wall((t_2d_point){data->player.pos.x + data->player.dir.y * move_amt, data->player.pos.y}, data)),
										data->player.pos.y - data->player.dir.x * (move_amt * !is_wall((t_2d_point){data->player.pos.x, data->player.pos.y - data->player.dir.x * move_amt}, data))};
	else if (keycode == MOVE_RIGHT)
		data->player.pos = (t_2d_point){data->player.pos.x - data->player.dir.y * move_amt * !is_wall((t_2d_point){data->player.pos.x - data->player.dir.y * move_amt, data->player.pos.y}, data),
										data->player.pos.y + data->player.dir.x * move_amt * !is_wall((t_2d_point){data->player.pos.x, data->player.pos.y + data->player.dir.x * move_amt}, data)};
	//printf("newpos: %f %f, dir %f %f\n", data->player.pos.x, data->player.pos.y * move_amt, data->player.dir.x, data->player.dir.y * move_amt);
}

void	adjust_fov(int keycode, t_data *data)
{
	double	adjust_amount;

	adjust_amount = 3;
	if (keycode == ZOOM_IN && data->player.fov > 10)
		data->player.fov -= adjust_amount;
	else if (keycode == ZOOM_OUT && data->player.fov < 180)
		data->player.fov += adjust_amount;
}

void	rotate_player(int keycode, t_data *data)
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
}

void vertical_movement(int keycode, t_data *data)
{
	int	adjust_amount;

	adjust_amount = 10;
	if (keycode == LOOK_UP)
		data->player.vertical += adjust_amount;
	else if (keycode == LOOK_DOWN)
		data->player.vertical -= adjust_amount;
}

int	key_reader(int keycode, t_data *data)
{
	if (keycode == KEY_ESC)
		close_pgm(data);
	else if (keycode == MOVE_FORWARD || keycode == MOVE_BACK
		|| keycode == MOVE_LEFT || keycode == MOVE_RIGHT)
		move_player(keycode, data);
	else if (keycode == ZOOM_OUT || keycode == ZOOM_IN)
		adjust_fov(keycode, data);
	else if (keycode == ROT || keycode == RROT)
		rotate_player(keycode, data);
	else if (keycode == LOOK_UP || keycode == LOOK_DOWN)
		vertical_movement(keycode, data);
	else
		return (0);
	ft_bzero(data->img->addr, (WIN_WIDTH * WIN_HEIGHT)
		* sizeof(data->img->bits_per_pixel));
	raycast(data);
	//minimap(data);
	return (0);
}

int	close_pgm(t_data *data)
{
	printf("Program closing\n");
	free_and_exit(data, MSG_EXIT, 0);
	return (0);
}
