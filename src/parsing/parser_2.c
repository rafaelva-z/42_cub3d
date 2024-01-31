/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-estr <fda-estr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 23:05:31 by fda-estr          #+#    #+#             */
/*   Updated: 2024/01/31 20:59:27 by fda-estr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static char	*identifier_skipper(t_data *data, char *s)
{
	char	*prod;
	int		i;

	i = -1;
	prod = s;
	while (*prod && *prod != ' ')
		prod++;
	while (*prod && *prod == ' ')
		prod++;
	if (!(*prod))
		free_and_exit(data, "Error: invalid identifier\n", 1);
	while (prod[++i])
	{
		if (prod[i] == ' ')
			free_and_exit(data, "Error: invalid identifier\n", 1);
	}
	return (prod);
}

void	identifier_init(t_data *dt)
{
	int	i;

	i = -1;
	while (++i < 6)
	{
		if (!ft_strncmp(dt->file->file[i], "NO ", 3))
			dt->file->north_file = identifier_skipper(dt, dt->file->file[i]);
		else if (!ft_strncmp(dt->file->file[i], "SO ", 3))
			dt->file->south_file = identifier_skipper(dt, dt->file->file[i]);
		else if (!ft_strncmp(dt->file->file[i], "WE ", 3))
			dt->file->west_file = identifier_skipper(dt, dt->file->file[i]);
		else if (!ft_strncmp(dt->file->file[i], "EA ", 3))
			dt->file->east_file = identifier_skipper(dt, dt->file->file[i]);
		else if (!ft_strncmp(dt->file->file[i], "F ", 2))
			dt->file->floor_file = identifier_skipper(dt, dt->file->file[i]);
		else if (!ft_strncmp(dt->file->file[i], "C ", 2))
			dt->file->ceiling_file = identifier_skipper(dt, dt->file->file[i]);
		else
			free_and_exit(dt, "Error: Invalid identifier\n", 1);
	}
	if (!dt->file->ceiling_file || !dt->file->floor_file
		|| !dt->file->west_file || !dt->file->north_file
		|| !dt->file->east_file || !dt->file->south_file)
		free_and_exit(dt, "Error: Doubled identifier\n", 1);
}

static int	get_pixel(t_img *img, int x, int y)
{
	char	*temp;
	int	prod;

	temp = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	prod = *(int *)temp;
	return (prod);
}

static void	colors_to_grid(t_img *image)
{
	int	i;
	int	j;

	i = -1;
	while (++i < 64)
		image->color_grid[i] = malloc(sizeof(int) * 64);
	i = -1;
	while (++i < 64)
	{
		j = -1;
		while (++j < 64)
			image->color_grid[j][i] = get_pixel(image, i, j);
	}
}

void	image_to_color_grid(t_data *data)
{
	data->image.north_img.color_grid = malloc(sizeof(int *) * 64);
	if (!data->image.north_img.color_grid)
		free_and_exit(data, ERR_MALLOC, 1);
	colors_to_grid(&data->image.north_img);
	data->image.east_img.color_grid = malloc(sizeof(int *) * 64);
	if (!data->image.east_img.color_grid)
		free_and_exit(data, ERR_MALLOC, 1);
	colors_to_grid(&data->image.east_img);
	data->image.south_img.color_grid = malloc(sizeof(int *) * 64);
	if (!data->image.south_img.color_grid)
		free_and_exit(data, ERR_MALLOC, 1);
	colors_to_grid(&data->image.south_img);
	data->image.west_img.color_grid = malloc(sizeof(int *) * 64);
	if (!data->image.west_img.color_grid)
		free_and_exit(data, ERR_MALLOC, 1);
	colors_to_grid(&data->image.west_img);
}

void	image_init(t_data *d, int size)
{
	d->image.north_img.img = mlx_xpm_file_to_image(d->mlx,
		d->file->north_file, &size, &size);
	if (!d->image.north_img.img)
		free_and_exit(d, ERR_MALLOC, 1);
	d->image.north_img.addr = mlx_get_data_addr(d->image.north_img.img, &d->image.north_img.bits_per_pixel,
		&d->image.north_img.line_length, &d->image.north_img.endian);
	d->image.south_img.img = mlx_xpm_file_to_image(d->mlx,
		d->file->south_file, &size, &size);
	if (!d->image.south_img.img)
		free_and_exit(d, ERR_MALLOC, 1);
	d->image.south_img.addr = mlx_get_data_addr(d->image.south_img.img, &d->image.south_img.bits_per_pixel,
		&d->image.south_img.line_length, &d->image.south_img.endian);
	d->image.east_img.img = mlx_xpm_file_to_image(d->mlx,
		d->file->north_file, &size, &size);
	if (!d->image.east_img.img)
		free_and_exit(d, ERR_MALLOC, 1);
	d->image.east_img.addr = mlx_get_data_addr(d->image.east_img.img, &d->image.east_img.bits_per_pixel,
		&d->image.east_img.line_length, &d->image.east_img.endian);
	d->image.west_img.img = mlx_xpm_file_to_image(d->mlx,
		d->file->north_file, &size, &size);
	if (!d->image.west_img.img)
		free_and_exit(d, ERR_MALLOC, 1);
	d->image.west_img.addr = mlx_get_data_addr(d->image.west_img.img, &d->image.west_img.bits_per_pixel,
		&d->image.west_img.line_length, &d->image.west_img.endian);
}
