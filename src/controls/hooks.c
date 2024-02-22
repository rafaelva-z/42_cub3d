/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz <rvaz@student.42lisboa.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 18:44:31 by rvaz              #+#    #+#             */
/*   Updated: 2024/02/22 13:43:02 by rvaz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	update_sprite(t_data *data, t_sprite *sprites, int sprite_amt)
{
	int	i;

	i = -1;
	while (++i < sprite_amt)
	{
		if (sprites[i].type == SPRT_DOOR)
		{
			if (sprites[i].state == D_CLOSED || sprites[i].state == D_OPEN)
				continue ;
			else if (sprites[i].state == D_OPENING)
				sprites[i].current_frame++;
			else if (sprites[i].state == D_CLOSING)
				sprites[i].current_frame--;
			if (sprites[i].current_frame > 6)
			{
				sprites[i].state = D_OPEN;
				sprites[i].current_frame = 0;
				data->map.map[(int)sprites[i].pos.y][(int)sprites[i].pos.x] = MAP_OPEN_DOOR;
			}
			else if (sprites[i].current_frame < 0)
			{
				sprites[i].state = D_CLOSED;
				sprites[i].current_frame = 0;
				data->map.map[(int)sprites[i].pos.y][(int)sprites[i].pos.x] = MAP_DOOR;
			}
		}
		else
		{
			sprites[i].current_frame++;
			if (sprites[i].current_frame > 6)
				sprites[i].current_frame = 0;
		}
	}
}

/**
 * @brief Runs every tick, and updates the player's position and view
*/
int	game_update(t_data *data)
{
	t_player	*player;
	int			update;

	update = 0;
	player = &data->player;
	while (time_stamp(data) < data->next_frame)
		;
	data->next_frame += FRAME_RATE;
	update_sprite(data, data->sprites, data->sprite_amt);
	if (player->actions)
		update += move_player(data);
	if (player->actions || !player->mouse_toggle)
	{
		update += rotate_player(&data->player);
		update += vertical_movement(&data->player);
		update += adjust_fov(&data->player);
	}
	enemy(data);
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
		|| keycode == MOVE_LEFT || keycode == MOVE_RIGHT || keycode == ZOOM_OUT
		|| keycode == ZOOM_IN || keycode == ROT || keycode == RROT
		|| keycode == ZOOM_IN || keycode == ZOOM_OUT || keycode == LOOK_UP
		|| keycode == LOOK_DOWN)
		set_actions(keycode, data);
	else if (keycode == TOGGLE_MOUSE)
		toggle_mouse(data);
	if (keycode == INTERACT)
		door_interactions(data);
	return (0);
}

/**
 * @brief Detects when a key is released
*/
int	key_release(int keycode, t_player *player)
{
	if (keycode == MOVE_FORWARD)
		player->actions &= player->actions ^ 1 << MOVE_FORWARD_B;
	else if (keycode == MOVE_BACK)
		player->actions &= player->actions ^ (1 << MOVE_BACK_B);
	else if (keycode == MOVE_LEFT)
		player->actions &= player->actions ^ (1 << MOVE_LEFT_B);
	else if (keycode == MOVE_RIGHT)
		player->actions &= player->actions ^ (1 << MOVE_RIGHT_B);
	else if (keycode == ROT)
		player->actions &= player->actions ^ 1 << ROT_B;
	else if (keycode == RROT)
		player->actions &= player->actions ^ 1 << RROT_B;
	else if (keycode == ZOOM_OUT)
		player->actions &= player->actions ^ 1 << ZOOM_OUT_B;
	else if (keycode == ZOOM_IN)
		player->actions &= player->actions ^ 1 << ZOOM_IN_B;
	else if (keycode == LOOK_UP)
		player->actions &= player->actions ^ 1 << LOOK_UP_B;
	else if (keycode == LOOK_DOWN)
		player->actions &= player->actions ^ 1 << LOOK_DOWN_B;
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
	if (y > WIN_HEIGHT / 2 && player->vertical > -150)
		player->vertical -= VERTICAL_SPD * MOUSE_SENS;
	else if (y < WIN_HEIGHT / 2 && player->vertical < 150)
		player->vertical += VERTICAL_SPD * MOUSE_SENS;
	player->mouse.x = x;
	return (0);
}

int	close_pgm(t_data *data)
{
	free_and_exit(data, MSG_EXIT, 0);
	return (0);
}

// int	automation(t_data *data)
// {
// 	static uint64_t	texture_change;

// 	if (texture_change == 0)
// 		texture_change = time_stamp(data) + (uint64_t)200;
// 	if (time_stamp(data) > texture_change)
// 	{
// 		if (data->enemy_indx < 6)
// 			data->enemy_indx++;
// 		else
// 			data->enemy_indx = 0;
// 	}
// 	enemy(data);
// }