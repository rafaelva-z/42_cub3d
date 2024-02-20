/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rc_spritecast.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-estr <fda-estr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 11:42:45 by rvaz              #+#    #+#             */
/*   Updated: 2024/02/20 14:43:54 by fda-estr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/**
 * @brief	Order the sprites based on distance to the player using bouble sort
*/
static void	order_sprites(t_sprite *sprites, int *sprite_order, int sprite_amt)
{
	int			tmp;
	int			i;
	int			j;

	j = -1;
	while (++j < sprite_amt - 1)
	{
		i = -1;
		while (++i < sprite_amt - 1)
		{
			if (sprites[sprite_order[i]].dist_player
				< sprites[sprite_order[i + 1]].dist_player)
			{
				tmp = sprite_order[i];
				sprite_order[i] = sprite_order[i + 1];
				sprite_order[i + 1] = tmp;
			}
		}
	}
}

/**
 * @brief	Sets all sprites positions based on the player's position
*/
static void	set_sprite_positions(t_sprite *sprites, int *sprite_order,
	int sprite_amt, t_player *player)
{
	int	i;

	i = -1;
	while (++i < sprite_amt)
		sprites[sprite_order[i]].dist_player = fabs((fabs((player->pos.x
							- sprites[sprite_order[i]].pos.x))
					+ fabs((player->pos.y - sprites[sprite_order[i]].pos.y))));
}

/**
 * @brief	Sets all sprites textures based on player and sprite direction
*/
static void	set_sprite_texture(t_data *data, t_sprite *sprite)
{
	float	radians;
	float	degrees;

	// Calculating the angle between the player and the sprite & converting to degrees
	radians = atan2(sprite->pos.y - data->player.pos.y,
			sprite->pos.x - data->player.pos.x);
	degrees = radians * (180 / M_PI);
	if (degrees < 0)
		degrees += 360;
	if (sprite->type == SPRT_ENEMY)
	{
		if (degrees < 45)
			sprite->texture = data->textures[EF0_IMG + sprite->current_frame];
		else if (degrees < 135)
			sprite->texture = data->textures[ER0_IMG + sprite->current_frame];
		else if (degrees < 225)
			sprite->texture = data->textures[EB0_IMG + sprite->current_frame];
		else if (degrees < 315)
			sprite->texture = data->textures[EL0_IMG + sprite->current_frame];
	}
	else if (sprite->type == SPRT_OBJ1)
	{
		if (degrees < 45)
			sprite->texture = data->textures[D0_IMG];
		else if (degrees < 135)
			sprite->texture = data->textures[D0_IMG];
		else if (degrees < 225)
			sprite->texture = data->textures[D0_IMG];
		else if (degrees < 315)
			sprite->texture = data->textures[D0_IMG];
	}
	else if (sprite->type == SPRT_OBJ2)
	{
		if (degrees < 45)
			sprite->texture = data->textures[D0_IMG];
		else if (degrees < 135)
			sprite->texture = data->textures[D0_IMG];
		else if (degrees < 225)
			sprite->texture = data->textures[D0_IMG];
		else if (degrees < 315)
			sprite->texture = data->textures[D0_IMG];
	}
}

void	rc_sprites(t_data *data)
{
	int	i;

	set_sprite_positions(data->sprites, data->sprite_order,
		data->sprite_amt, &data->player);
	order_sprites(data->sprites, data->sprite_order, data->sprite_amt);
	i = -1;
	//	sprite projection
	while (++i < data->sprite_amt)
	{
		set_sprite_texture(data, &data->sprites[data->sprite_order[i]]);
		t_point	sprt_pos = (t_point){data->sprites[data->sprite_order[i]].pos.x - data->player.pos.x, data->sprites[data->sprite_order[i]].pos.y - data->player.pos.y};	// sprite pos relative to player
		double	invert = 1.0 / (data->player.plane.x * data->player.dir.y - data->player.dir.x * data->player.plane.y); // for matrix
		t_point	transform = (t_point){invert * (data->player.dir.y * sprt_pos.x - data->player.dir.x * sprt_pos.y), invert * (-data->player.plane.y * sprt_pos.x + data->player.plane.x * sprt_pos.y)}; // matrix multiplication;
		int		sprite_screen_x = (WIN_WIDTH / 2) * (1 + transform.x / transform.y);
		t_point	sprite_size; //sprite size on screen
		sprite_size.y = abs(WIN_HEIGHT / transform.y);
		sprite_size.x = sprite_size.y;
		//Calculating start and end point for drawing
		t_point	draw_start;
		t_point draw_end;
		draw_start.y = -sprite_size.y / 2 + WIN_HEIGHT / 2;
		if (draw_start.y < 0)
			draw_start.y = 0;
		draw_end.y = sprite_size.y / 2 + WIN_HEIGHT / 2;
		if (draw_end.y >= WIN_HEIGHT)
			draw_end.y = WIN_HEIGHT - 1;
		draw_start.x = -sprite_size.x / 2 + sprite_screen_x;
		if (draw_start.x < 0)
			draw_start.x = 0;
		draw_end.x = sprite_size.x / 2 + sprite_screen_x;
		if (draw_end.x >= WIN_WIDTH)
			draw_end.x = WIN_WIDTH - 1;
		//Draw the sprite
		for (int screen_x = draw_start.x; screen_x < draw_end.x; screen_x++)
		{
			int tex_x = (int)(256 * (screen_x - (-sprite_size.x / 2 + sprite_screen_x)) * TEXTURE_WIDTH / sprite_size.x) / 256;
			if (transform.y > 0 && screen_x > 0 && screen_x < WIN_WIDTH && transform.y < data->z_buffer[screen_x])
			{
				for (int y = draw_start.y; y < draw_end.y; y++)
				{
					int d = y * 256 - WIN_HEIGHT * 128 + sprite_size.y * 128;
					int tex_y = ((d * TEXTURE_HEIGHT) / sprite_size.y) / 256;
					int color;
					if (tex_x >= 0 && tex_x < TEXTURE_WIDTH && tex_y >= 0 && tex_y < TEXTURE_HEIGHT)
                        color = data->sprites[data->sprite_order[i]].texture->color_grid[tex_y][tex_x];
                    else
                        color = 0;
					draw_pixel(data->img, screen_x, y, shader(color, abs(data->sprites[data->sprite_order[i]].dist_player), 2.0, 0.3, 1));
				}
			}
		}
	}
}
