/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rc_spritecast.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz <rvaz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 11:42:45 by rvaz              #+#    #+#             */
/*   Updated: 2024/03/18 15:39:35 by rvaz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/**
 * @brief	Order the sprites based on distance to the player using bouble sort
*/
static void	sc_order_sprites(t_sprite *sprites, int *sprt_order, int sprite_amt)
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
			if (sprites[sprt_order[i]].dist_player
				< sprites[sprt_order[i + 1]].dist_player)
			{
				tmp = sprt_order[i];
				sprt_order[i] = sprt_order[i + 1];
				sprt_order[i + 1] = tmp;
			}
		}
	}
}

/**
 * @brief	Sets all sprites positions based on the player's position
*/
static void	sc_set_sprite_positions(t_sprite *sprites, int *sprt_order,
	int sprite_amt, t_player *player)
{
	int	i;

	i = -1;
	while (++i < sprite_amt)
		sprites[sprt_order[i]].dist_player = fabs((fabs((player->pos.x
							- sprites[sprt_order[i]].pos.x))
					+ fabs((player->pos.y - sprites[sprt_order[i]].pos.y))));
}

/**
 * @brief	Sets all sprites textures based on player and sprite direction
*/
static void	sc_set_sprite_texture(t_data *data, t_sprite *sprite)
{
	float	radians;
	float	degrees;

	radians = atan2(data->player.dir.y, data->player.dir.x)
		- atan2(sprite->dir.y, sprite->dir.x);
	degrees = radians * (180 / M_PI);
	if (degrees < 0)
		degrees += 360;
	if (sprite->type == SPRT_ENEMY)
		set_enemy_texture(data, sprite, degrees);
	else if (sprite->type == SPRT_OBJ1)
		set_object_texture(data, sprite, degrees);
}

void	draw_sprite( t_data *data, t_rc_sprites *rc, int i)
{
	t_point		t_pos;
	int			x;
	int			y;
	int			color;

	x = rc->draw_start.x - 1;
	while (++x < rc->draw_end.x)
	{
		t_pos.x = (int)(256
				* (x - (-rc->sprt_size.x / 2 + rc->sprite_screen_x))
				* TEXTURE_WIDTH / rc->sprt_size.x) / 256;
		if (rc->transform.y < 0 || x < 0 || x > WIN_WIDTH
			|| rc->transform.y > data->z_buffer[x])
			continue ;
		y = rc->draw_start.y;
		while (++y < rc->draw_end.y)
		{
			t_pos.y = (y * 256 - WIN_HEIGHT * 128 + rc->sprt_size.y * 128);
			t_pos.y = ((t_pos.y * TEXTURE_HEIGHT) / rc->sprt_size.y) / 256;
			color = sc_set_color(&t_pos, data, i);
			draw_pixel(data->img, x, y, shader(color, fabs(data->sprites
					[data->sprt_order[i]].dist_player), (t_point){2, 0.3}, 1));
		}
	}
}

void	rc_sprites(t_data *data)
{
	t_rc_sprites	*rc;
	int				i;

	rc = malloc(sizeof(t_rc_sprites));
	if (!rc)
		free_and_exit(data, ERR_MALLOC, 1);
	sc_set_sprite_positions(data->sprites, data->sprt_order,
		data->sprite_amt, &data->player);
	sc_order_sprites(data->sprites, data->sprt_order, data->sprite_amt);
	i = -1;
	while (++i < data->sprite_amt)
	{
		if (rc_door(data, &data->sprites[data->sprt_order[i]], &data->player))
			continue ;
		sc_set_sprite_texture(data, &data->sprites[data->sprt_order[i]]);
		sc_matrix_multiplication(data, &rc->transform, i);
		rc->sprite_screen_x = (WIN_WIDTH / 2)
			* (1 + rc->transform.x / rc->transform.y);
		rc->sprt_size.y = fabs((double)WIN_HEIGHT / rc->transform.y);
		rc->sprt_size.x = rc->sprt_size.y;
		sc_set_draw_pos(rc);
		draw_sprite(data, rc, i);
	}
	free(rc);
}
