/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-estr <fda-estr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 22:26:46 by fda-estr          #+#    #+#             */
/*   Updated: 2024/03/09 15:13:50 by fda-estr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	rand_dir_change(t_data *data, int index)
{
	int				ran;
	struct timeval	time;

	if (gettimeofday(&time, NULL) < 0)
		free_and_exit(data, ERR_TIME, 1);
	srand(time.tv_usec);
	ran = rand() % 20;
	if (ran == 0)
	{
		ran = (180 / 8) * ((rand() % 16) - 8);
		rotate_enemy(&data->sprites[index], ran);
	}
}

static void	avoid_wall(t_data *data, t_sprite *sprt, int rot_dir, int i)
{
	bool		left_touch;
	bool		right_touch;
	t_point		cld_pos[2];

	while (i++ < 360)
	{
		left_touch = false;
		right_touch = false;
		get_colid_pos(&cld_pos[0], &cld_pos[1], sprt);
		if (data->map.map[(int)cld_pos[0].y][(int)cld_pos[0].x] != MAP_EMPTY)
			left_touch = true;
		if (data->map.map[(int)cld_pos[1].y][(int)cld_pos[1].x] != MAP_EMPTY)
			right_touch = true;
		if (left_touch && right_touch)
			rotate_enemy(sprt, 1 * rot_dir);
		else if (left_touch && !right_touch)
			rotate_enemy(sprt, -1);
		else if (!left_touch && right_touch)
			rotate_enemy(sprt, 1);
		else if (!left_touch && !right_touch)
			break ;
	}
}

static void	player_in_sight(t_data *data, t_sprite *enemy)
{
	double	dist;

	rc_enemy(data, enemy);
	if (get_timestamp(data) > enemy->follow_timer && enemy->state != E_FOLLOW)
		return ;
	enemy->dir.x = data->player.pos.x - enemy->pos.x;
	enemy->dir.y = data->player.pos.y - enemy->pos.y;
	dist = distance_calc(data->player.pos, enemy->pos);
	enemy->dir.x *= (1 / dist);
	enemy->dir.y *= (1 / dist);
	enemy->coliders[0].x = 0.60 * enemy->dir.x;
	enemy->coliders[0].y = 0.60 * enemy->dir.y;
	rotate_point(&enemy->coliders[0], 45);
	enemy->coliders[1].x = 0.60 * enemy->dir.x;
	enemy->coliders[1].y = 0.60 * enemy->dir.y;
	rotate_point(&enemy->coliders[1], -45);
}

static void	step_forward(t_data *data, t_sprite *sprt)
{
	if (sprt->state == E_IDLE)
		return ;
	if (sprt->pos.x + ENEMY_SPD * sprt->dir.x >= 0)
		sprt->pos.x += (ENEMY_SPD * sprt->dir.x);
	if (sprt->pos.y + ENEMY_SPD * sprt->dir.y)
		sprt->pos.y += (ENEMY_SPD * sprt->dir.y);
}

void	enemy(t_data *data)
{
	int		i;
	double	dist;
	int		rot_dir;

	i = -1;
	rot_dir = 1;
	while (++i < data->sprite_amt)
	{
		if (data->sprites[i].type != SPRT_ENEMY)
			continue ;
		dist = distance_calc(data->player.pos, data->sprites[i].pos);
		if (dist > 10)
			continue ;
		if (dist < 0.5)
			free_and_exit(data, MSG_LOSE, 0);
		rot_dir *= -1;
		player_in_sight(data, &data->sprites[i]);
		if (data->sprites[i].state != E_FOLLOW)
			rand_dir_change(data, i);
		avoid_wall(data, &data->sprites[i], rot_dir, 0);
		step_forward(data, &data->sprites[i]);
	}
}
