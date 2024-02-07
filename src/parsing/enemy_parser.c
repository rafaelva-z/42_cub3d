/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-estr <fda-estr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 22:37:41 by fda-estr          #+#    #+#             */
/*   Updated: 2024/02/07 21:26:40 by fda-estr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static t_enemy	*new_list(t_data *data, int x, int y)
{
	t_enemy	*node;

	node = (t_enemy *) malloc(sizeof(t_enemy));
	if (!node)
		free_and_exit(data, ERR_MALLOC, 1);
	node->dir = (t_2d_point) {1, 0};
	node->pos.x = x + 0.5;
	node->pos.y = y + 0.5;
	node->follow = 0;
	node->move = 1;
	node->next_enemy = NULL;
	return (node);
}

static void	list_add_back(t_data *data, t_enemy *node)
{
	t_enemy *current;

	current = data->enemy_list;
	if (!current)
	{
		data->enemy_list = node;
		return ;
	}
	while(current->next_enemy)
		current = current->next_enemy;
	current->next_enemy = node;
}

void	enemy_parser(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	while (data->map.map[++i])
	{
		j = -1;
		while (data->map.map[i][++j])
		{
			if (data->map.map[i][j] == 'M')
			{
				list_add_back(data, new_list(data, j, i));
				data->map.map[i][j] = '0';
			}
		}
	}
}