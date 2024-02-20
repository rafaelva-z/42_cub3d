/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-estr <fda-estr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 12:13:05 by rvaz              #+#    #+#             */
/*   Updated: 2024/02/18 16:11:51 by fda-estr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	shader(int color, double distance, double a, double b, short mode)
{
	double	i;

	if (!SHADER || color == CHROMA_KEY_COLOR)
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

	if (color == CHROMA_KEY_COLOR)
		return ;
	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}