/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rc_spritecast2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz <rvaz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 14:14:03 by rvaz              #+#    #+#             */
/*   Updated: 2024/03/12 17:51:19 by rvaz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	set_object_texture(t_data *data, t_sprite *sprite, double degrees)
{
	if (degrees < 45)
		sprite->texture = data->textures[F_IMG + sprite->current_frame];
	else if (degrees < 135)
		sprite->texture = data->textures[F_IMG + sprite->current_frame];
	else if (degrees < 225)
		sprite->texture = data->textures[F_IMG + sprite->current_frame];
	else if (degrees < 315)
		sprite->texture = data->textures[F_IMG + sprite->current_frame];
}

void	set_enemy_texture(t_data *data, t_sprite *sprite, double degrees)
{
	if (degrees < 45)
		sprite->texture = data->textures[EB0_IMG + sprite->current_frame];
	else if (degrees < 135)
		sprite->texture = data->textures[EL0_IMG + sprite->current_frame];
	else if (degrees < 225)
		sprite->texture = data->textures[EF0_IMG + sprite->current_frame];
	else if (degrees < 315)
		sprite->texture = data->textures[ER0_IMG + sprite->current_frame];
}

void	sc_matrix_multiplication(t_data *data, t_point *transform, int i)
{
	t_point	sprt_pos;
	double	invert;

	sprt_pos.x = data->sprites[data->sprt_order[i]].pos.x
		- data->player.pos.x;
	sprt_pos.y = data->sprites[data->sprt_order[i]].pos.y
		- data->player.pos.y;
	invert = 1.0 / (data->player.plane.x * data->player.dir.y
			- data->player.dir.x * data->player.plane.y);
	(*transform).x = invert * (data->player.dir.y * sprt_pos.x
			- data->player.dir.x * sprt_pos.y);
	(*transform).y = invert * (-data->player.plane.y * sprt_pos.x
			+ data->player.plane.x * sprt_pos.y);
}

int	sc_set_color( t_point *t_pos, t_data *data, int i)
{
	int	color;

	if (t_pos->x >= 0 && t_pos->x < TEXTURE_WIDTH
		&& t_pos->y >= 0 && t_pos->y < TEXTURE_HEIGHT)
		color = data->sprites[data->sprt_order[i]]
			.texture->color_grid[(int)t_pos->y][(int)t_pos->x];
	else
		color = 0;
	return (color);
}

void	sc_set_draw_pos(t_rc_sprites *rc)
{
	rc->draw_start.y = -rc->sprt_size.y / 2 + WIN_HEIGHT / 2;
	if (rc->draw_start.y < 0)
		rc->draw_start.y = 0;
	rc->draw_end.y = rc->sprt_size.y / 2 + WIN_HEIGHT / 2;
	if (rc->draw_end.y >= WIN_HEIGHT)
		rc->draw_end.y = WIN_HEIGHT - 1;
	rc->draw_start.x = -rc->sprt_size.x / 2 + rc->sprite_screen_x;
	if (rc->draw_start.x < 0)
		rc->draw_start.x = 0;
	rc->draw_end.x = rc->sprt_size.x / 2 + rc->sprite_screen_x;
	if (rc->draw_end.x >= WIN_WIDTH)
		rc->draw_end.x = WIN_WIDTH - 1;
}
