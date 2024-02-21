/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-estr <fda-estr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 22:26:46 by fda-estr          #+#    #+#             */
/*   Updated: 2024/02/21 15:57:54 by fda-estr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static double	distance_calc(t_point p1, t_point p2)
{
	double	dist;
	dist = sqrt(pow((p2.x - p1.x), 2) + pow((p2.y - p1.y), 2));
	return (dist);
}

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

static void	avoid_wall(t_data *data, int index, int rot_dir)
{
	bool	left_touch;
	bool	right_touch;
	t_point colider_pos[2];
	int i = 0;

	while (i++ < 360)
	{
		left_touch = false;
		right_touch = false;
		colider_pos[0].x = data->sprites[index].coliders[0].x + data->sprites[index].pos.x;
		colider_pos[0].y = data->sprites[index].coliders[0].y + data->sprites[index].pos.y;
		colider_pos[1].x = data->sprites[index].coliders[1].x + data->sprites[index].pos.x; 
		colider_pos[1].y = data->sprites[index].coliders[1].y + data->sprites[index].pos.y;
		if (data->map.map[(int)colider_pos[0].y][(int)colider_pos[0].x] != '0')
			left_touch = true;
		if (data->map.map[(int)colider_pos[1].y][(int)colider_pos[1].x] != '0')
			right_touch = true;
		if (left_touch && right_touch)
			rotate_enemy(&data->sprites[index], 1 * rot_dir);
		else if (left_touch && !right_touch)
			rotate_enemy(&data->sprites[index], -1);
		else if (!left_touch && right_touch)
			rotate_enemy(&data->sprites[index], 1);
		else if (!left_touch && !right_touch)
		{
			data->sprites[index].move = true;
			break ;
		}
	}
	if (i > 360)
		data->sprites[index].move = false;
}

static void	player_in_sight(t_data *data, t_sprite *enemy)
{
	double	dist;


	enemy_raycast(data, enemy);
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

static void	step_forward(t_data *data, int index)
{
	if (data->sprites[index].move == false)
		return ;
	if (data->sprites[index].pos.x + ENEMY_SPD * data->sprites[index].dir.x >= 0)
		data->sprites[index].pos.x += (ENEMY_SPD * data->sprites[index].dir.x);
	if (data->sprites[index].pos.y + ENEMY_SPD * data->sprites[index].dir.y)
		data->sprites[index].pos.y += (ENEMY_SPD * data->sprites[index].dir.y);
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
		rot_dir *= -1;
		if (data->sprites[i].type != SPRT_ENEMY)
			continue ;
		dist = distance_calc(data->player.pos, data->sprites[i].pos);
		if (dist > 10)
			continue ;
		if (dist < 0.5)
			free_and_exit(data, MSG_LOSE, 0);
		player_in_sight(data, &data->sprites[i]);
		// if (!current->follow)
			rand_dir_change(data, i);
		avoid_wall(data, i, rot_dir);
		step_forward(data, i);
	}
}
