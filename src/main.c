/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz <rvaz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 20:34:35 by rvaz              #+#    #+#             */
/*   Updated: 2024/01/24 18:48:25 by rvaz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
		return (1);			// Error handling
	initializer(&data);
	//data.player->camera.point_a.x = data.player->pos.x + data.player->dir.x - WIN_WIDTH / 2;
	//data.player->camera.point_a.y = data.player->pos.y + data.player->dir.y + WIN_HEIGHT / 2;
	parser(&data, argv[1]);
	raycast(&data);
}