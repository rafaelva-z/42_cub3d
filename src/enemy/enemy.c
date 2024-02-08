/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-estr <fda-estr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 22:26:46 by fda-estr          #+#    #+#             */
/*   Updated: 2024/02/08 11:18:55 by fda-estr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static double	distance_calc(t_2d_point p1, t_2d_point p2)
{
	double	dist;

	dist = sqrt(pow((p2.x - p1.x), 2) + pow((p2.y - p1.y), 2));
	return (dist);
}

static void	direction_change(t_data *data, t_enemy *enemy)
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
		rotate_point(&enemy->dir, ran);			/////////////////////////////
	}
}

static void	wall_proximity(t_data *data, t_enemy *enemy)
{
	(void) data;
	(void) enemy;
}

static void	player_in_sight(t_data *data, t_enemy *enemy)
{
	double	dist;


	//	if player is in sight

	// vector_norm
	enemy->follow = 1;
	enemy->dir.x = data->player.pos.x - enemy->pos.x;
	enemy->dir.y = data->player.pos.y - enemy->pos.y;
	dist = distance_calc(data->player.pos, enemy->pos);
	enemy->dir.x *= (1 / dist);
	enemy->dir.y *= (1 / dist);
}

static void	step_forward(t_enemy *enemy)
{
	enemy->pos.x += 0.1 * enemy->dir.x; 
	enemy->pos.y += 0.1 * enemy->dir.y;
	enemy->follow = 0; 
}

void	enemy(t_data *data)
{
	t_enemy	*current;
	double	dist;

	current = data->enemy_list;
	while (current)
	{
		dist = distance_calc(data->player.pos, current->pos);
		if (dist > 10)
		{
			current = current->next_enemy;
			continue ;
		}
		if (dist > 0.5)
			free_and_exit(data, MSG_LOSE, 0);
		player_in_sight(data, current);
		if (!current->follow)
			direction_change(data, current);
		wall_proximity(data, current);
		step_forward(current);
		current = current->next_enemy;
	}
}
