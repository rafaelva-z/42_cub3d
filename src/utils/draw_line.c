/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz <rvaz@student.42lisboa.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 17:45:18 by rvaz              #+#    #+#             */
/*   Updated: 2024/01/26 01:37:45 by rvaz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	draw_line(t_vector line, t_img *img, int color)
{
	while (line.point_a.y != line.point_b.y)
	{
		if (line.point_a.x >= 0 && line.point_a.y >= 0
			&& line.point_a.x < WIN_WIDTH && line.point_a.y < WIN_HEIGHT)
			draw_pixel(img, line.point_a.x, line.point_a.y, color);
		line.point_a.y++;
	}
}
