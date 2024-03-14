/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rc_floor_ceiling.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz <rvaz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 13:51:53 by rvaz              #+#    #+#             */
/*   Updated: 2024/03/13 19:26:33 by rvaz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	fc_set_color(t_data *data, t_point t_pos, t_point *color)
{
	if (data->floor_colour == -1)
	{
		color->x = data->textures[F_IMG]->color_grid[(int)t_pos.y]
		[(int)t_pos.x];
		color->y = data->textures[C_IMG]->color_grid[(int)t_pos.y]
		[(int)t_pos.x];
		return ;
	}
	color->x = data->ceiling_colour;
	color->y = data->floor_colour;
}

static void	fc_set_pos(t_point *t_step, t_point *real_pos, t_point *t_pos)
{
	t_pos->x = (int)(TEXTURE_WIDTH
			* (real_pos->x - (int)real_pos->x) * 2) & (TEXTURE_WIDTH - 1);
	t_pos->y = (int)(TEXTURE_HEIGHT
			* (real_pos->y - (int)real_pos->y) * 2) & (TEXTURE_HEIGHT - 1);
	real_pos->x += t_step->x;
	real_pos->y += t_step->y;
}

/**
 * @brief	loop to draw the floor and ceiling
 * 			"t_step" is the distance between each x ray,
 * 			"distance" is the distance from the camera to the floor,
 * 			"real_pos" is the current position x and y,
 * 			"t_pos" is the position in the texture image.
*/
static void	rc_fc_loop(t_point *r, t_vector ray_p, t_data *data)
{
	t_point	t_step;
	double	distance;
	t_point	real_pos;
	t_point	t_pos;
	t_point	color;

	while (++r->y < WIN_HEIGHT)
	{
		distance = (WIN_HEIGHT / 2) / (r->y - WIN_HEIGHT / 2);
		t_step.x = distance * (ray_p.p_b.x - ray_p.p_a.x) / WIN_WIDTH;
		t_step.y = distance * (ray_p.p_b.y - ray_p.p_a.y) / WIN_WIDTH;
		real_pos.x = data->player.pos.x + distance * ray_p.p_a.x;
		real_pos.y = data->player.pos.y + distance * ray_p.p_a.y;
		r->x = -1;
		while (++r->x < WIN_WIDTH)
		{
			fc_set_pos(&t_step, &real_pos, &t_pos);
			fc_set_color(data, t_pos, &color);
			draw_pixel(data->img, (int)r->x, (int)r->y,
				shader(color.x, r->y, (t_point){WIN_HEIGHT * 0.844, 45}, 0));
			draw_pixel(data->img, (int)r->x, WIN_HEIGHT - (int)r->y,
				shader(color.y, r->y, (t_point){WIN_HEIGHT * 0.844, 45}, 0));
		}
	}
}

/**
 * @brief	Draws the floor and ceiling.
 * 			"r" is the screen x position,
 * 			"raydir0" is the leftmost ray,
 * 			"raydir1" is the rightmost ray.
*/
void	rc_floor_ceiling(t_data *data)
{
	t_point	r;
	t_point	raydir0;
	t_point	raydir1;

	r.y = -1;
	raydir0.x = data->player.dir.x - data->player.plane.x;
	raydir0.y = data->player.dir.y - data->player.plane.y;
	raydir1.x = data->player.dir.x + data->player.plane.x;
	raydir1.y = data->player.dir.y + data->player.plane.y;
	rc_fc_loop(&r, (t_vector){raydir0, raydir1}, data);
}
