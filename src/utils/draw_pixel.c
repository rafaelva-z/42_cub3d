/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_pixel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz <rvaz@student.42lisboa.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 18:12:41 by rvaz              #+#    #+#             */
/*   Updated: 2024/02/16 16:40:12 by rvaz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	shader(int color, double distance, double a, double b, short mode)
{
	double	i;

	if (!SHADER)
		return (color);
	i = distance;
	if (mode == 1)
	{
		while (i > a)
		{
			color = (color & 0xfefefefe) >> 1;
			i -= b;
		}
	}
	else 
	{
		while (i < a)
		{
			color = (color & 0xfefefefe) >> 1;
			i += b;
		}
	}
	return (color);
}

// void	shader(int color, double distance, int *r, int *g, int *b)
// {
// 	*r = (color >> 16) & 0xFF;
// 	*g = (color >> 8) & 0xFF;
// 	*b = color & 0xFF;
// 	*r = *r * (1 - distance);
// 	*g = *g * (1 - distance);
// 	*b = *b * (1 - distance);
// }

void	draw_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	// if ((color & CHROMA_KEY_COLOR) == 0)
	// 	return ;
	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
