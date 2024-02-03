/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz <rvaz@student.42lisboa.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 15:03:40 by rvaz              #+#    #+#             */
/*   Updated: 2024/02/03 15:30:40 by rvaz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	set_move_cam(int keycode, t_data *data)
{
	if (keycode == ROT)
		data->player.move_cam |= 1 << ROT_B;
	else if (keycode == RROT)
		data->player.move_cam |= 1 << RROT_B;
	else if (keycode == ZOOM_OUT)
		data->player.move_cam |= 1 << ZOOM_OUT_B;
	else if (keycode == ZOOM_IN)
		data->player.move_cam |= 1 << ZOOM_IN_B;
	else if (keycode == LOOK_UP)
		data->player.move_cam |= 1 << LOOK_UP_B;
	else if (keycode == LOOK_DOWN)
		data->player.move_cam |= 1 << LOOK_DOWN_B;
}

void	set_move(int keycode, t_data *data)
{
	if (keycode == MOVE_FORWARD)
		data->player.move |= 1 << MOVE_FORWARD_B;
	else if (keycode == MOVE_BACK)
		data->player.move |= 1 << MOVE_BACK_B;
	else if (keycode == MOVE_LEFT)
		data->player.move |= 1 << MOVE_LEFT_B;
	else if (keycode == MOVE_RIGHT)
		data->player.move |= 1 << MOVE_RIGHT_B;
}

