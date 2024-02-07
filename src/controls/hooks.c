/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-estr <fda-estr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 18:44:31 by rvaz              #+#    #+#             */
/*   Updated: 2024/02/07 20:22:53 by fda-estr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/**
 * @brief Runs every tick, and updates the player's position and view
*/
int	game_update(t_data *data)
{
	t_player	*player;
	int			update;

	update = 0;
	player = &data->player;
	if (player->move)
		update += move_player(data);
	if (player->move_cam || !player->mouse_toggle)
	{
		update += rotate_player(&data->player);
		update += vertical_movement(&data->player);
		update += adjust_fov(&data->player);
	}
	if (update)
		update_view(data);
	if (!player->mouse_toggle)
		mlx_mouse_move(data->mlx, data->mlx_win, WIN_WIDTH / 2, WIN_HEIGHT / 2);
	return (0);
}

/**
 * @brief Detects user input
*/
int	key_reader(int keycode, t_data *data)
{
	if (keycode == KEY_ESC)
		close_pgm(data);
	else if (keycode == MOVE_FORWARD || keycode == MOVE_BACK
		|| keycode == MOVE_LEFT || keycode == MOVE_RIGHT)
		set_move(keycode, data);
	else if (keycode == ZOOM_OUT || keycode == ZOOM_IN || keycode == ROT
		|| keycode == RROT || keycode == ZOOM_IN || keycode == ZOOM_OUT
		|| keycode == LOOK_UP || keycode == LOOK_DOWN)
		set_move_cam(keycode, data);
	else if (keycode == TOGGLE_MOUSE)
		toggle_mouse(data);
	return (0);
}

/**
 * @brief Detects when a key is released
*/
int	key_release(int keycode, t_player *player)
{
	if (keycode == MOVE_FORWARD)
		player->move &= player->move ^ 1 << MOVE_FORWARD_B;
	else if (keycode == MOVE_BACK)
		player->move &= player->move ^ (1 << MOVE_BACK_B);
	else if (keycode == MOVE_LEFT)
		player->move &= player->move ^ (1 << MOVE_LEFT_B);
	else if (keycode == MOVE_RIGHT)
		player->move &= player->move ^ (1 << MOVE_RIGHT_B);
	else if (keycode == ROT)
		player->move_cam &= player->move_cam ^ 1 << ROT_B;
	else if (keycode == RROT)
		player->move_cam &= player->move_cam ^ 1 << RROT_B;
	else if (keycode == ZOOM_OUT)
		player->move_cam &= player->move_cam ^ 1 << ZOOM_OUT_B;
	else if (keycode == ZOOM_IN)
		player->move_cam &= player->move_cam ^ 1 << ZOOM_IN_B;
	else if (keycode == LOOK_UP)
		player->move_cam &= player->move_cam ^ 1 << LOOK_UP_B;
	else if (keycode == LOOK_DOWN)
		player->move_cam &= player->move_cam ^ 1 << LOOK_DOWN_B;
	return (0);
}

int	mouse_reader(int x, int y, t_player *player)
{
	if (player->mouse_toggle)
		return (0);
	if (x > WIN_WIDTH / 2)
	{
		rotate_point(&player->dir, ROT_SPD * MOUSE_SENS);
		rotate_point(&player->plane, ROT_SPD * MOUSE_SENS);
	}
	else if (x < WIN_WIDTH / 2)
	{
		rotate_point(&player->dir, -ROT_SPD * MOUSE_SENS);
		rotate_point(&player->plane, -ROT_SPD * MOUSE_SENS);
	}
	if (y > WIN_HEIGHT / 2 && player->vertical < 250)
		player->vertical -= VERTICAL_SPD * MOUSE_SENS;
	else if (y < WIN_HEIGHT / 2 && player->vertical > -250)
		player->vertical += VERTICAL_SPD * MOUSE_SENS;
	player->mouse.x = x;
	return (0);
}

int	close_pgm(t_data *data)
{
	free_and_exit(data, MSG_EXIT, 0);
	return (0);
}

int	automation(t_data *data)
{
	static uint64_t	walk;
	static uint64_t	texture_change;
	static int		texture_indx;

	if (walk == 0)
	{
		walk = time_stamp + 100;
		texture_change = time_stamp + 200;
	}
	if (time_stamp > texture_change)
	{
		if (data->enemy_indx < 6)
			data->enemy_indx++;
		else
			data->enemy_indx = 0;
	}
	if (time_stamp > walk)
		enemy(data);
}