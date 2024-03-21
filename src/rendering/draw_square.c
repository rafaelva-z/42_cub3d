/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_square.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz <rvaz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 17:29:38 by rvaz              #+#    #+#             */
/*   Updated: 2024/03/21 17:47:52 by rvaz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_square(t_img *img, int x, int y, int size, int color)
{
    t_point pos;

    pos = (t_point){x, y};
    while (pos.y < y + size)
    {
        pos.x = x;
        while (pos.x < x + size)
        {
            draw_pixel(img, pos.x++, pos.y, color);
        }
        pos.y++;
    }
}