/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz <rvaz@student.42lisboa.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 20:34:35 by rvaz              #+#    #+#             */
/*   Updated: 2024/02/03 01:16:52 by rvaz             ###   ########.fr       */
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
	update_view(&data);
	mlx_hook(data.mlx_win, 17, 0L, close_pgm, &data);
	mlx_hook(data.mlx_win, KeyPress, KeyPressMask, key_reader, &data);
	mlx_loop(data.mlx);
	free_and_exit(&data, NULL, 0);
}