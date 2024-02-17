/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz <rvaz@student.42lisboa.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 17:28:39 by rvaz              #+#    #+#             */
/*   Updated: 2024/02/17 12:30:47 by rvaz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	init_data(t_data *data)
{
	data->mlx = NULL;
	data->mlx_win = NULL;
	data->mlx_win_mm = NULL;
	data->map.map = NULL;
	data->map.minimap = NULL;
	data->file = malloc(sizeof(t_file));
	if (!data->file)
		free_and_exit(data, ERR_MALLOC, 1);
	data->file->file = NULL;
	data->file->north_file = NULL;
	data->file->east_file = NULL;
	data->file->south_file = NULL;
	data->file->west_file = NULL;
	data->file->floor_file = NULL;
	data->file->ceiling_file = NULL;
	begining_time_stamp(data);
	data->enemy_indx = 0;
	data->z_buffer = calloc(WIN_WIDTH, sizeof(double));
	texture_array_init(data);
}

static void	init_mlx(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		free_and_exit(data, ERR_MLX_INIT, 1);
	data->mlx_win = mlx_new_window(data->mlx, WIN_WIDTH, WIN_HEIGHT, WIN_TITLE);
	if (!data->mlx_win)
		free_and_exit(data, ERR_MLX_WIN, 1);
	data->img = malloc(sizeof(t_img));
	if (!data->img)
		free_and_exit(data, ERR_MALLOC, 1);
	data->img->img = mlx_new_image(data->mlx, WIN_WIDTH, WIN_HEIGHT);
	data->img->addr = mlx_get_data_addr(data->img->img, 
			&(data->img->bits_per_pixel), &(data->img->line_length),
			&(data->img->endian));

	data->mlx_win_mm = mlx_new_window(data->mlx, MM_WIDTH, MM_HEIGHT, WIN_TITLE);
	if (!data->mlx_win_mm)
		free_and_exit(data, ERR_MLX_WIN, 1);
	data->img_mm = malloc(sizeof(t_img));
	if (!data->img_mm)
		free_and_exit(data, ERR_MALLOC, 1);
	data->img_mm->img = mlx_new_image(data->mlx, MM_WIDTH, MM_HEIGHT);
	data->img_mm->addr = mlx_get_data_addr(data->img_mm->img, 
			&(data->img_mm->bits_per_pixel), &(data->img_mm->line_length),
			&(data->img_mm->endian));

	mlx_do_key_autorepeatoff(data->mlx);
}

static void	init_player(t_data *data)
{
	data->player.fov = START_FOV;
	data->player.vertical = 0;
	data->player.move = 0;
	data->player.move_cam = 0;
	data->player.mouse = (t_point){0, 0};
	data->player.mov_dir = (t_point){0, 0};
	data->player.mouse_toggle = 1;
}

void	initializer(t_data *data)
{
	init_data(data);
	init_mlx(data);
	init_player(data);
	// new stuff to be organized
	data->sprite_amt = 3; // counted in parsing
	data->sprites = calloc(data->sprite_amt, sizeof(t_sprite)); // has to be allocated after parsing
	data->sprite_order = calloc(data->sprite_amt, sizeof(int)); // has to be allocated after parsing
	// initialize all instances of sprites (enemies and objects)
	for (int i = 0; i < data->sprite_amt; i++)
	{
		data->sprites[i].texture = data->textures[EB0_IMG]; // defined in parsing
		data->sprites[i].pos = (t_point){(i + 1) * 2, (i + 1) * 2}; // defined in parsing
		if (i == 0)
		{
			data->sprites[i].dir = (t_point){1, 0}; // defined in parsing
			data->sprites[i].current_frame = 0; // random value?
			data->sprites[i].type = SPRT_ENEMY; // defined in parsing
		}
		else if (i == 1)
		{
			data->sprites[i].dir = (t_point){0, 1}; // defined in parsing
			data->sprites[i].current_frame = 4; // random value?
			data->sprites[i].type = SPRT_ENEMY; // defined in parsing
		}
		else if (i == 2)
		{
			data->sprites[i].dir = (t_point){-1, 0}; // defined in parsing
			data->sprites[i].current_frame = 2; // random value?
			data->sprites[i].type = SPRT_ENEMY; // defined in parsing
		}
		data->sprite_order[i] = i;
	}
	data->enemy_list = NULL; // "enemy_list" should be replaced by "sprites"
}
