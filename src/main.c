/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz <rvaz@student.42lisboa.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 20:34:35 by rvaz              #+#    #+#             */
/*   Updated: 2024/01/26 00:10:10 by rvaz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	main(int argc, char **argv)
{
	t_data	data;
	
	if (argc != 2)
		return (1);			// Error handling
	initializer(&data);
	parser(&data, argv[1]);
	//minimap(&data);
	// raycast(&data);
	mlx_key_hook(data.mlx_win, key_reader, &data);
	mlx_hook(data.mlx_win, 17, 0L, close_pgm, &data);
	mlx_loop(data.mlx);
	//raycast(&data);
	free_and_exit(&data, NULL);
}
