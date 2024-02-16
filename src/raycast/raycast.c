/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz <rvaz@student.42lisboa.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 18:41:12 by rvaz              #+#    #+#             */
/*   Updated: 2024/02/16 16:43:37 by rvaz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	draw_wall(t_data *data, int r, t_ray *ray)
{
	int		sky_size;
	t_img	*texture;

	if (ray->side == 0)
	{
		if (ray->dir.x < 0)
			texture = data->textures[WE_IMG];
		else
			texture = data->textures[EA_IMG];
	}
	else
	{
		if (ray->dir.y < 0)
			texture = data->textures[NO_IMG];
		else
			texture = data->textures[SO_IMG];
	}
	sky_size = ((WIN_HEIGHT - ray->wall_height) / 2) + data->player.vertical;
	draw_vertical_line_texture((t_point){r, sky_size}, texture, data, ray);
}

void	rc_floor_ceiling(t_data *data)
{
	t_point	r;				// current ray position
	t_point	raydir0;		// leftmost ray
	t_point	raydir1;		// rightmost ray
	double	distance;		// distance from the camera to the floor
	t_point	t_step;			// distance between each x ray
	t_point	real_pos;	// current position x and y
	int		color_c;
	int		color_f;
	t_point	t_pos;

	raydir0.x = data->player.dir.x - data->player.plane.x;
	raydir0.y = data->player.dir.y - data->player.plane.y;
	raydir1.x = data->player.dir.x + data->player.plane.x;
	raydir1.y = data->player.dir.y + data->player.plane.y;
	r.y = -1;
	while (++r.y < WIN_HEIGHT)
	{
		distance = (0.5 * WIN_HEIGHT) / (r.y - WIN_HEIGHT / 2); // camera height divided by y position relative to center of the screen
		t_step.x = distance * (raydir1.x - raydir0.x) / WIN_WIDTH;
		t_step.y = distance * (raydir1.y - raydir0.y) / WIN_WIDTH;
		real_pos.x = data->player.pos.x + distance * raydir0.x;
		real_pos.y = data->player.pos.y + distance * raydir0.y;
		r.x = -1;
		while (++r.x < WIN_WIDTH)
		{
			t_pos.x = (int)(TEXTURE_WIDTH * (real_pos.x - (int)real_pos.x) * 2) & (TEXTURE_WIDTH - 1);
			t_pos.y = (int)(TEXTURE_HEIGHT * (real_pos.y - (int)real_pos.y) * 2) & (TEXTURE_HEIGHT - 1);
			real_pos.x += t_step.x;
			real_pos.y += t_step.y;
			color_f = data->textures[F_IMG]->color_grid[(int)t_pos.y][(int)t_pos.x];
			color_c = data->textures[C_IMG]->color_grid[(int)t_pos.y][(int)t_pos.x];
			draw_pixel(data->img, (int)r.x, (int)r.y, shader(color_f, r.y, 500, 45, 0));
			draw_pixel(data->img, (int)r.x, WIN_HEIGHT - (int)r.y, shader(color_c, r.y, 500, 45, 0));
		}
	}
}

/**
 * @brief	Order the sprites based on distance to the player using bouble sort
*/
void	orderSprites(t_sprite *sprites, int *sprite_order, int sprite_amt)
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
			if (sprites[sprite_order[i]].dist_player < sprites[sprite_order[i + 1]].dist_player)
			{
				tmp = sprite_order[i];
				sprite_order[i] = sprite_order[i + 1];
				sprite_order[i + 1] = tmp;
			}
		}
	}
}


static void rc_sprites(t_data *data)
{
	for (int i = 0; i < data->sprite_amt; i++)
	{
		data->sprite_order[i] = i; // this would be more efficient if the values were kept from one iteration to the next
		data->sprites[i].dist_player = fabs((fabs((data->player.pos.x - data->sprites[i].pos.x)) + fabs((data->player.pos.y - data->sprites[i].pos.y))));
	}
	orderSprites(data->sprites, data->sprite_order, data->sprite_amt);
	//projecting sprites
	for(int i = 0; i < data->sprite_amt; i++)
    {
		t_point	sprt_pos = (t_point){data->sprites[data->sprite_order[i]].pos.x - data->player.pos.x, data->sprites[data->sprite_order[i]].pos.y - data->player.pos.y};	// sprite pos relative to player
		double	invert = 1.0 / (data->player.plane.x * data->player.dir.y - data->player.dir.x * data->player.plane.y); // for matrix
		t_point	transform = (t_point){invert * (data->player.dir.y * sprt_pos.x - data->player.dir.x * sprt_pos.y), invert * (-data->player.plane.y * sprt_pos.x + data->player.plane.x * sprt_pos.y)}; // matrix multiplication;
		int		sprite_screen_x = (WIN_WIDTH / 2) * (1 + transform.x / transform.y);
		t_point	sprite_size; //sprite size on screen
		sprite_size.y = abs(WIN_HEIGHT / transform.y);
		//Calculating start and end point for drawing
		t_point	draw_start;
		t_point draw_end;
		draw_start.y = -sprite_size.y / 2 + WIN_HEIGHT / 2;
		if (draw_start.y < 0)
			draw_start.y = 0;
		draw_end.y = sprite_size.y / 2 + WIN_HEIGHT / 2;
		if (draw_end.y >= WIN_HEIGHT)
			draw_end.y = WIN_HEIGHT - 1;
		sprite_size.x = abs(WIN_HEIGHT / transform.y);
		draw_start.x = -sprite_size.x / 2 + sprite_screen_x;
		if (draw_start.x < 0)
			draw_start.x = 0;
		draw_end.x = sprite_size.x / 2 + sprite_screen_x;
		if (draw_end.x >= WIN_WIDTH)
			draw_end.x = WIN_WIDTH - 1;
		//Draw the sprite
		for (int stripe = draw_start.x; stripe < draw_end.x; stripe++)
		{
			int tex_x = (int)(256 * (stripe - (-sprite_size.x / 2 + sprite_screen_x)) * TEXTURE_WIDTH / sprite_size.x) / 256;
			if (transform.y > 0 && stripe > 0 && stripe < WIN_WIDTH && transform.y < data->z_buffer[stripe])
			{
				for (int y = draw_start.y; y < draw_end.y; y++)
				{
					int d = y * 256 - WIN_HEIGHT * 128 + sprite_size.y * 128;
					int tex_y = ((d * TEXTURE_HEIGHT) / sprite_size.y) / 256;
					int color = data->sprites[data->sprite_order[i]].texture->color_grid[tex_y][tex_x];
					draw_pixel(data->img, stripe, y, shader(color, abs(data->sprites[data->sprite_order[i]].dist_player), 2.0, 0.3, 1));
				}
			}
		}
	}
}

void	rc_walls(t_data *data, t_player *player)
{
	t_ray		ray;
	double		camera_x;
	int			r;

	r = 0;
	while (r < WIN_WIDTH)
	{
		camera_x = 2.0 * r / (double)WIN_WIDTH - 1.0;
		ray.dir.x = player->dir.x + player->plane.x * camera_x;
		ray.dir.y = player->dir.y + player->plane.y * camera_x;
		dda(&ray, data);
		ray.wall_height = WIN_HEIGHT
			/ (ray.distance * (data->player.fov * 0.0151));
		//draw_vert_line_grad_center(data->img, r, data->player.vertical);
		data->z_buffer[r] = ray.distance; // sprite casting
		draw_wall(data, r, &ray);
		r++;
	}
}

/**
 * @brief	The raycast main function
*/
void	raycast(t_data *data)
{
	rc_floor_ceiling(data);
	rc_walls(data, &data->player);
	rc_sprites(data);
	// free (data->z_buffer); // sprite casting
}

void	enemy_raycast(t_data *data, t_enemy *enemy)
{
	t_ray		ray;
	double		camera_x;
	int			r;

	r = 0;
	while (r < 30) // define a macro for enemy rays
	{
		camera_x = 2.0 * (double)r / 30.0 - 1.0;
		ray.dir.x = enemy->dir.x + enemy->plane.x * camera_x;
		ray.dir.y = enemy->dir.y + enemy->plane.y * camera_x;
		dda(&ray, data);
		// check if player was found on ray hit linked list then:
		/*
		if (playerfound())
			follow = 1
		else
			follow = 0
		*/
		r++;
	}
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img->img, 0, 0);
}