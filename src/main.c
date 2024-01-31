/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-estr <fda-estr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 20:34:35 by rvaz              #+#    #+#             */
/*   Updated: 2024/01/31 13:31:23 by fda-estr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
		return (display_error(ERR_ARGC));
	initializer(&data);
	parser(&data, argv[1]);
	minimap(&data);
	raycast(&data);
	mlx_put_image_to_window(data.mlx, data.mlx_win, data.img->img, 0, 0);
	mlx_hook(data.mlx_win, 2, 1L << 0, key_reader, &data);
	mlx_hook(data.mlx_win, 17, 0L, close_pgm, &data);
	mlx_loop(data.mlx);
	free_and_exit(&data, NULL, 0);
}
