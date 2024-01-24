/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-estr <fda-estr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 20:34:35 by rvaz              #+#    #+#             */
/*   Updated: 2024/01/24 19:06:52 by fda-estr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
		return (1);			// Error handling
	initializer(&data);
	//insert this in the initializer
	//data.player->camera.point_a.x = data.player->pos.x + data.player->dir.x - WIN_WIDTH / 2;
	//data.player->camera.point_a.y = data.player->pos.y + data.player->dir.y + WIN_HEIGHT / 2;

	parser(&data, argv[1]);
	rotate_point(&data.player.dir, 1);
	// dda(data.player.pos, data.player.dir, data);


	
}