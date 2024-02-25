/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_stuff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz <rvaz@student.42lisboa.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 17:23:24 by rvaz              #+#    #+#             */
/*   Updated: 2024/02/24 17:33:00 by rvaz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/**
 * @brief	Sets the texture to be drawn on the wall based on "side" variable
 * 			form the given ray. 0 West/East; 1 North/South; 3/4 Door.
*/
void	set_wall_texture(t_img **txt_lst, t_ray *r, t_sprite *door, t_img **txt)
{
	if (r->side == 0)
	{
		if (r->dir.x < 0)
			*txt = txt_lst[WE_IMG];
		else
			*txt = txt_lst[EA_IMG];
	}
	else if (r->side == 1)
	{
		if (r->dir.y < 0)
			*txt = txt_lst[NO_IMG];
		else
			*txt = txt_lst[SO_IMG];
	}
	else if (r->side == 3 || r->side == 4)
	{
		if (door)
			*txt = txt_lst[D0_IMG + door->current_frame];
		else
			*txt = txt_lst[D0_IMG];
	}
}

/**
 * @brief	Draws the wall on the given vertical line of the screen
*/
void	draw_wall(t_data *data, int r, t_ray *ray, t_sprite *door)
{
	int		sky_size;
	t_img	*texture;

	sky_size = ((WIN_HEIGHT - ray->wall_height) / 2) + data->player.vertical;
	set_wall_texture(data->textures, ray, door, &texture);
	draw_vertical_line_texture((t_point){r, sky_size}, texture, data, ray);
}