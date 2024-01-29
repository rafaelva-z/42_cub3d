/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz <rvaz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 20:34:35 by rvaz              #+#    #+#             */
/*   Updated: 2024/01/29 16:33:44 by rvaz             ###   ########.fr       */
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
	//minimap(&data);
	raycast(&data);
	mlx_put_image_to_window(data.mlx, data.mlx_win, data.img->img, 0, 0);

	mlx_hook(data.mlx_win, 17, 0L, close_pgm, &data);
	mlx_hook(data.mlx_win, KeyPress, KeyPressMask, key_reader, &data);
	mlx_loop(data.mlx);
	free_and_exit(&data, NULL, 0);
}