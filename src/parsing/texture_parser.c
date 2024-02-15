/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz <rvaz@student.42lisboa.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 18:05:40 by fda-estr          #+#    #+#             */
/*   Updated: 2024/02/15 14:31:43 by rvaz             ###   ########.fr       */
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

static int	get_pixel(t_img *img, int x, int y)
{
	char	*temp;
	int	prod;

	temp = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	prod = *(int *)temp;
	return (prod);
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
			free_and_exit(data, ERR_MALLOC, 1);
		img->columns_created++;
	}
	i = -1;
	while (++i < img->width)
	{
		j = -1;
		while (++j < img->height)
			img->color_grid[j][i] = get_pixel(img, i, j);
	}
}

// void	image_to_color_grid(t_data *data)
// {
// 	data->image.north_img.color_grid = malloc(sizeof(int *) * 64);
// 	if (!data->image.north_img.color_grid)
// 		free_and_exit(data, ERR_MALLOC, 1);
// 	colors_to_grid(&data->image.north_img);
// 	data->image.east_img.color_grid = malloc(sizeof(int *) * 64);
// 	if (!data->image.east_img.color_grid)
// 		free_and_exit(data, ERR_MALLOC, 1);
// 	colors_to_grid(&data->image.east_img);
// 	data->image.south_img.color_grid = malloc(sizeof(int *) * 64);
// 	if (!data->image.south_img.color_grid)
// 		free_and_exit(data, ERR_MALLOC, 1);
// 	colors_to_grid(&data->image.south_img);
// 	data->image.west_img.color_grid = malloc(sizeof(int *) * 64);
// 	if (!data->image.west_img.color_grid)
// 		free_and_exit(data, ERR_MALLOC, 1);
// 	colors_to_grid(&data->image.west_img);
// }

static void	image_init(t_data *data, t_img *img, char	*path)
{
	get_size(data, path, img);
	img->img = mlx_xpm_file_to_image(data->mlx, path, &img->width, &img->height);
	if (!img->img)
		free_and_exit(data, ERR_IMG, 1);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
		&img->line_length, &img->endian);
	img->color_grid = malloc(sizeof(int *) * img->width);
	if (!img->color_grid)
		free_and_exit(data, ERR_MALLOC, 1);
	colors_to_grid(data, img);
}

void	texture_parser(t_data *data)
{
	image_init(data, data->textures[NO_IMG], data->file->north_file);
	image_init(data, data->textures[EA_IMG], data->file->east_file);
	image_init(data, data->textures[SO_IMG], data->file->south_file);
	image_init(data, data->textures[WE_IMG], data->file->west_file);
	image_init(data, data->textures[F_IMG], data->file->floor_file);
	image_init(data, data->textures[C_IMG], data->file->ceiling_file);
	image_init(data, data->textures[MMW_IMG], "./textures/minimap/mm_wall.xpm");
	image_init(data, data->textures[MMF_IMG], "./textures/minimap/mm_floor.xpm");
	image_init(data, data->textures[MMV_IMG], "./textures/minimap/mm_vacum.xpm");
	image_init(data, data->textures[EF0_IMG], "./textures/enemy/enemy_0.xpm");
	image_init(data, data->textures[EF1_IMG], "./textures/enemy/enemy_1.xpm");
	image_init(data, data->textures[EF2_IMG], "./textures/enemy/enemy_2.xpm");
	image_init(data, data->textures[EF3_IMG], "./textures/enemy/enemy_3.xpm");
	image_init(data, data->textures[EF4_IMG], "./textures/enemy/enemy_4.xpm");
	image_init(data, data->textures[EF5_IMG], "./textures/enemy/enemy_5.xpm");
	image_init(data, data->textures[EF6_IMG], "./textures/enemy/enemy_6.xpm");
	image_init(data, data->textures[EL0_IMG], "./textures/enemy/enemy_left_0.xpm");
	image_init(data, data->textures[EL1_IMG], "./textures/enemy/enemy_left_1.xpm");
	image_init(data, data->textures[EL2_IMG], "./textures/enemy/enemy_left_2.xpm");
	image_init(data, data->textures[EL3_IMG], "./textures/enemy/enemy_left_3.xpm");
	image_init(data, data->textures[EL4_IMG], "./textures/enemy/enemy_left_4.xpm");
	image_init(data, data->textures[EL5_IMG], "./textures/enemy/enemy_left_5.xpm");
	image_init(data, data->textures[EL6_IMG], "./textures/enemy/enemy_left_6.xpm");
	image_init(data, data->textures[EB0_IMG], "./textures/enemy/enemy_back_0.xpm");
	image_init(data, data->textures[EB1_IMG], "./textures/enemy/enemy_back_1.xpm");
	image_init(data, data->textures[EB2_IMG], "./textures/enemy/enemy_back_2.xpm");
	image_init(data, data->textures[EB3_IMG], "./textures/enemy/enemy_back_3.xpm");
	image_init(data, data->textures[EB4_IMG], "./textures/enemy/enemy_back_4.xpm");
	image_init(data, data->textures[EB5_IMG], "./textures/enemy/enemy_back_5.xpm");
	image_init(data, data->textures[EB6_IMG], "./textures/enemy/enemy_back_6.xpm");
	image_init(data, data->textures[ER0_IMG], "./textures/enemy/enemy_right_0.xpm");
	image_init(data, data->textures[ER1_IMG], "./textures/enemy/enemy_right_1.xpm");
	image_init(data, data->textures[ER2_IMG], "./textures/enemy/enemy_right_2.xpm");
	image_init(data, data->textures[ER3_IMG], "./textures/enemy/enemy_right_3.xpm");
	image_init(data, data->textures[ER4_IMG], "./textures/enemy/enemy_right_4.xpm");
	image_init(data, data->textures[ER5_IMG], "./textures/enemy/enemy_right_5.xpm");
	image_init(data, data->textures[ER6_IMG], "./textures/enemy/enemy_right_6.xpm");
	image_init(data, data->textures[D0_IMG], "./textures/door/door_0.xpm");
	image_init(data, data->textures[D1_IMG], "./textures/door/door_1.xpm");
	image_init(data, data->textures[D2_IMG], "./textures/door/door_2.xpm");
	image_init(data, data->textures[D3_IMG], "./textures/door/door_3.xpm");
	image_init(data, data->textures[D4_IMG], "./textures/door/door_4.xpm");
	image_init(data, data->textures[D5_IMG], "./textures/door/door_5.xpm");
	image_init(data, data->textures[D6_IMG], "./textures/door/door_6.xpm");
}

// void	image_init(t_data *d, int size)
// {
// 	d->image.north_img.img = mlx_xpm_file_to_image(d->mlx,
// 		d->file->north_file, &size, &size);
// 	if (!d->image.north_img.img)
// 		free_and_exit(d, ERR_MALLOC, 1);
// 	d->image.north_img.addr = mlx_get_data_addr(d->image.north_img.img, &d->image.north_img.bits_per_pixel,
// 		&d->image.north_img.line_length, &d->image.north_img.endian);
// 	d->image.south_img.img = mlx_xpm_file_to_image(d->mlx,
// 		d->file->south_file, &size, &size);
// 	if (!d->image.south_img.img)
// 		free_and_exit(d, ERR_MALLOC, 1);
// 	d->image.south_img.addr = mlx_get_data_addr(d->image.south_img.img, &d->image.south_img.bits_per_pixel,
// 		&d->image.south_img.line_length, &d->image.south_img.endian);
// 	d->image.east_img.img = mlx_xpm_file_to_image(d->mlx,
// 		d->file->east_file, &size, &size);
// 	if (!d->image.east_img.img)
// 		free_and_exit(d, ERR_MALLOC, 1);
// 	d->image.east_img.addr = mlx_get_data_addr(d->image.east_img.img, &d->image.east_img.bits_per_pixel,
// 		&d->image.east_img.line_length, &d->image.east_img.endian);
// 	d->image.west_img.img = mlx_xpm_file_to_image(d->mlx,
// 		d->file->west_file, &size, &size);
// 	if (!d->image.west_img.img)
// 		free_and_exit(d, ERR_MALLOC, 1);
// 	d->image.west_img.addr = mlx_get_data_addr(d->image.west_img.img, &d->image.west_img.bits_per_pixel,
// 		&d->image.west_img.line_length, &d->image.west_img.endian);
// }