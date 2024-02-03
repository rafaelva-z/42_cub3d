/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz <rvaz@student.42lisboa.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 17:45:18 by rvaz              #+#    #+#             */
/*   Updated: 2024/01/31 13:11:22 by rvaz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	draw_vertical_line(t_2d_point start, int size, t_img *img, int color)
{
	int	y_pos;

	if (start.x >= WIN_WIDTH || start.y >= WIN_HEIGHT || size <= 0)
		return ;
	y_pos = start.y;
	if (color == 0)
	{
		if (size < WIN_HEIGHT * 0.7)
			color = WALL_COLOR - size / 5;
		else
			color = WALL_COLOR - (WIN_HEIGHT * 0.7) / 5;
	}
	while (size > 0)
	{
		//printf("c: %x startx: %f ypos: %d\n", color, start.x, y_pos);
		if (start.x >= 0 && y_pos >= 0
			&& y_pos < WIN_HEIGHT && start.x < WIN_WIDTH)
			draw_pixel(img, start.x, y_pos, color);
		y_pos++;
		size--;
	}
}
