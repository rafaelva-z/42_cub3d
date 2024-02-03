/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz <rvaz@student.42lisboa.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 20:34:35 by rvaz              #+#    #+#             */
/*   Updated: 2024/02/03 16:27:29 by rvaz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"


// int	get_pixel(t_img *img, int x, int y)
// {
// 	char	*temp;
// 	int	prod;

// 	printf("bits p pixel: %d\n", img->bits_per_pixel);
// 	temp = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
// 	prod = *(int *)temp;
// 	return (prod);
// }

void	test(t_data *data)
{
	int		i;
	int		j;
	void	*mlx;
	void	*mlx_win;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 500, 500, "test ick les");
	i = -1;
	while (++i < 64)
	{
		j = -1;
		while (++j < 64)
		{
			mlx_pixel_put(mlx, mlx_win, i, j, data->image.north_img.color_grid[j][i]);
		}
	}
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
		return (display_error(ERR_ARGC));
	initializer(&data);
	parser(&data, argv[1]);
	// test(&data);
	// mlx_put_image_to_window(data.mlx, data.mlx_win, data.img->img, 0, 0);
	update_view(&data);
	mlx_hook(data.mlx_win, 17, 0L, close_pgm, &data);
	mlx_hook(data.mlx_win, 2, 1L << 0, key_reader, &data);
	mlx_hook(data.mlx_win, 3, 1L << 1, key_release, &data);
	// MOUSE MOVEMENT
	mlx_hook(data.mlx_win, 6, (1L << 6), mouse_reader, &data);
	mlx_do_key_autorepeatoff(data.mlx);
	mlx_loop_hook(data.mlx, game_update, &data);
	mlx_loop(data.mlx);
	free_and_exit(&data, NULL, 0);
}