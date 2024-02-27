/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-estr <fda-estr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 18:05:40 by fda-estr          #+#    #+#             */
/*   Updated: 2024/02/25 19:03:44 by fda-estr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	get_size(t_data *data, char	*path, t_img *img)
{
	char	*str;
	int		fd;
	char	*temp;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		free_and_exit(data, ERR_FD, 1);
	while (1)
	{
		str = get_next_line(fd);
		if (!str)
			free_and_exit(data, ERR_IMG, 1);
		if (str && str[0] == '\"')
			break ;
		free (str);
	}
	temp = str;
	while (*str && !ft_isdigit(*str))
		str++;
	img->width = ft_atoi(str);
	while (*str && ft_isdigit(*str))
		str++;
	img->height = ft_atoi(str);
	free (temp);
	close (fd);
}

static void	colors_to_grid(t_data *data, t_img *img)
{
	int	i;
	int	j;

	i = -1;
	while (++i < img->width)
	{
		img->color_grid[i] = malloc(sizeof(int) * img->height);
		if (!img->color_grid[i])
		{
			while (i--)
				free(img->color_grid[i]);
			free (img->color_grid);
			img->color_grid = NULL;
			free_and_exit(data, ERR_MALLOC, 1);
		}
	}
	i = -1;
	while (++i < img->width)
	{
		j = -1;
		while (++j < img->height)
			img->color_grid[j][i] = get_pixel(img, i, j);
	}
}

static void	image_init(t_data *dt, t_img *img, char	*path)
{
	get_size(dt, path, img);
	img->img = mlx_xpm_file_to_image(dt->mlx, path, &img->width, &img->height);
	if (!img->img)
		free_and_exit(dt, ERR_IMG, 1);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_length, &img->endian);
	img->color_grid = malloc(sizeof(int *) * img->width);
	if (!img->color_grid)
		free_and_exit(dt, ERR_MALLOC, 1);
	colors_to_grid(dt, img);
}

void	texture_parser_aux(t_data *dt)
{
	image_init(dt, dt->textures[NO_IMG], dt->file->north_file);
	image_init(dt, dt->textures[EA_IMG], dt->file->east_file);
	image_init(dt, dt->textures[SO_IMG], dt->file->south_file);
	image_init(dt, dt->textures[WE_IMG], dt->file->west_file);
	image_init(dt, dt->textures[F_IMG], dt->file->floor_file);
	image_init(dt, dt->textures[C_IMG], dt->file->ceiling_file);
	image_init(dt, dt->textures[MMW_IMG], "./textures/minimap/mm_wall.xpm");
	image_init(dt, dt->textures[MMF_IMG], "./textures/minimap/mm_floor.xpm");
	image_init(dt, dt->textures[MMV_IMG], "./textures/minimap/mm_vacum.xpm");
	image_init(dt, dt->textures[EF0_IMG], "./textures/enemy/enemy_0.xpm");
	image_init(dt, dt->textures[EF1_IMG], "./textures/enemy/enemy_1.xpm");
	image_init(dt, dt->textures[EF2_IMG], "./textures/enemy/enemy_2.xpm");
	image_init(dt, dt->textures[EF3_IMG], "./textures/enemy/enemy_3.xpm");
	image_init(dt, dt->textures[EF4_IMG], "./textures/enemy/enemy_4.xpm");
	image_init(dt, dt->textures[EF5_IMG], "./textures/enemy/enemy_5.xpm");
	image_init(dt, dt->textures[EF6_IMG], "./textures/enemy/enemy_6.xpm");
	image_init(dt, dt->textures[EL0_IMG], "./textures/enemy/enemy_left_0.xpm");
	image_init(dt, dt->textures[EL1_IMG], "./textures/enemy/enemy_left_1.xpm");
	image_init(dt, dt->textures[EL2_IMG], "./textures/enemy/enemy_left_2.xpm");
	image_init(dt, dt->textures[EL3_IMG], "./textures/enemy/enemy_left_3.xpm");
	image_init(dt, dt->textures[EL4_IMG], "./textures/enemy/enemy_left_4.xpm");
	image_init(dt, dt->textures[EL5_IMG], "./textures/enemy/enemy_left_5.xpm");
	image_init(dt, dt->textures[EL6_IMG], "./textures/enemy/enemy_left_6.xpm");
	image_init(dt, dt->textures[EB0_IMG], "./textures/enemy/enemy_back_0.xpm");
}

void	texture_parser(t_data *dt)
{
	image_init(dt, dt->textures[EB1_IMG], "./textures/enemy/enemy_back_1.xpm");
	image_init(dt, dt->textures[EB2_IMG], "./textures/enemy/enemy_back_2.xpm");
	image_init(dt, dt->textures[EB3_IMG], "./textures/enemy/enemy_back_3.xpm");
	image_init(dt, dt->textures[EB4_IMG], "./textures/enemy/enemy_back_4.xpm");
	image_init(dt, dt->textures[EB5_IMG], "./textures/enemy/enemy_back_5.xpm");
	image_init(dt, dt->textures[EB6_IMG], "./textures/enemy/enemy_back_6.xpm");
	image_init(dt, dt->textures[ER0_IMG], "./textures/enemy/enemy_right_0.xpm");
	image_init(dt, dt->textures[ER1_IMG], "./textures/enemy/enemy_right_1.xpm");
	image_init(dt, dt->textures[ER2_IMG], "./textures/enemy/enemy_right_2.xpm");
	image_init(dt, dt->textures[ER3_IMG], "./textures/enemy/enemy_right_3.xpm");
	image_init(dt, dt->textures[ER4_IMG], "./textures/enemy/enemy_right_4.xpm");
	image_init(dt, dt->textures[ER5_IMG], "./textures/enemy/enemy_right_5.xpm");
	image_init(dt, dt->textures[ER6_IMG], "./textures/enemy/enemy_right_6.xpm");
	image_init(dt, dt->textures[D0_IMG], "./textures/door/door_0.xpm");
	image_init(dt, dt->textures[D1_IMG], "./textures/door/door_1.xpm");
	image_init(dt, dt->textures[D2_IMG], "./textures/door/door_2.xpm");
	image_init(dt, dt->textures[D3_IMG], "./textures/door/door_3.xpm");
	image_init(dt, dt->textures[D4_IMG], "./textures/door/door_4.xpm");
	image_init(dt, dt->textures[D5_IMG], "./textures/door/door_5.xpm");
	image_init(dt, dt->textures[D6_IMG], "./textures/door/door_6.xpm");
	texture_parser_aux(dt);
}
