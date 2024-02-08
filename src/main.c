/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz <rvaz@student.42lisboa.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 20:34:35 by rvaz              #+#    #+#             */
/*   Updated: 2024/02/08 16:20:58 by rvaz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	mlx_hooks(t_data *data)
{
	mlx_hook(data->mlx_win, 17, 0L, close_pgm, data);
	mlx_hook(data->mlx_win, 2, 1L << 0, key_reader, data);
	mlx_hook(data->mlx_win, 3, 1L << 1, key_release, &data->player);
	mlx_hook(data->mlx_win, 6, (1L << 6), mouse_reader, &data->player);
	mlx_loop_hook(data->mlx, game_update, data);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
		return (display_error(ERR_ARGC));
	initializer(&data);
	parser(&data, argv[1]);
	update_view(&data);
	mlx_hooks(&data);
	mlx_loop(data.mlx);
	free_and_exit(&data, NULL, 0);
}
