/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz <rvaz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 15:38:11 by rvaz              #+#    #+#             */
/*   Updated: 2024/03/18 17:06:51 by rvaz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

//	Keyboard
# define KEY_ESC		65307
# define KEY_LEFT		65361
# define KEY_UP			65362
# define KEY_RIGHT		65363
# define KEY_DOWN		65364
# define KEY_PLUS		65451
# define KEY_MINUS		65453
# define KEY_CTRL       65507
# define KEY_SPACE		32
# define KEY_A			97
# define KEY_C			99
# define KEY_D			100
# define KEY_E			101
# define KEY_F			102
# define KEY_Q			113
# define KEY_R			114
# define KEY_S			115
# define KEY_V			118
# define KEY_W			119
# define KEY_X			120
# define KEY_Z			122

//	Controls
# define MOVE_FORWARD	KEY_W
# define MOVE_LEFT		KEY_A
# define MOVE_BACK		KEY_S
# define MOVE_RIGHT		KEY_D
# define ZOOM_IN		KEY_PLUS
# define ZOOM_OUT		KEY_MINUS
# define ROT			KEY_RIGHT
# define RROT			KEY_LEFT
# define LOOK_UP		KEY_UP
# define LOOK_DOWN		KEY_DOWN
# define TOGGLE_MOUSE   KEY_CTRL
# define INTERACT		KEY_SPACE

// 	Controls bits

# define MOVE_FORWARD_B	0
# define MOVE_BACK_B	1
# define MOVE_LEFT_B	2
# define MOVE_RIGHT_B	3
# define ROT_B			4
# define RROT_B			5
# define ZOOM_IN_B		6
# define ZOOM_OUT_B		7
# define LOOK_UP_B		8
# define LOOK_DOWN_B	9

//	Player Constants

# define MOUSE_SENS		0.3
# define START_FOV		66
# define FOV_SPD		0.001
# define MOVE_SPD		0.1
# define ROT_SPD		4

#endif