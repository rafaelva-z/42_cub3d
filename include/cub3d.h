/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz <rvaz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 20:44:05 by rvaz              #+#    #+#             */
/*   Updated: 2024/01/24 17:01:58 by rvaz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../lib/libft/libft.h"
//# include "../lib/minilibx-linux/mlx.h"
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <math.h>

# define M_PI 3.14159265358979323846

//	Screen Resolution
# define WIN_WIDTH	900
# define WIN_HEIGHT	600

//	Keyboard
# define KEY_ESC	65307
# define KEY_LEFT	65361
# define KEY_UP		65362
# define KEY_RIGHT	65363
# define KEY_DOWN	65364
# define KEY_PLUS	65451
# define KEY_MINUS	65453
# define KEY_A		97
# define KEY_C		99
# define KEY_D		100
# define KEY_E		101
# define KEY_F		102
# define KEY_Q		113
# define KEY_R		114
# define KEY_S		115
# define KEY_V		118
# define KEY_W		119
# define KEY_X		120
# define KEY_Z		122

//	Controls
# define UP			KEY_W
# define LEFT		KEY_A
# define DOWN		KEY_S
# define RIGHT		KEY_D
# define ZOOM_IN	KEY_PLUS
# define ZOOM_OUT	KEY_MINUS

typedef struct s_2d_point
{
	double	x;
	double	y;
}	t_2d_point;

typedef struct s_vector
{
	t_2d_point	point_a;
	t_2d_point	point_b;
}	t_vector;

typedef struct s_player
{
	t_2d_point	pos;
	t_2d_point	dir;
	t_vector	camera;
}				t_player;

typedef struct s_map
{
	char		**map;
	t_2d_point	size;
}				t_map; 

typedef struct s_file
{
	char	**file;						//	pointer to the matrix to the file content
	char	*north_file;				//	pointer to the texture file name
	char	*east_file;					//				||
	char	*south_file;				//				||
	char	*west_file;					//				||
	char	*ceiling_file;				//				||
	char	*floor_file;				//				||
}				t_file;


typedef struct s_data
{
	void		*mlx;					//	pointer to mlx
	void		*mlx_win;				//	pointer to the mlx window
	void		*north_img;				//	ponter to north image
	void		*east_img;				//	pointer to east image
	void		*south_img;				//	pointer to south image
	void		*west_img;				//	pointer to west image
	t_file		*file;					//	pointer to the file struct
	char		**map;					//	pointer to map
	t_2d_point	map_size;
	t_player	*player;				//	pointer to player's struct
}				t_data;

/* parser.c	*/

void	parser(t_data *data, char *str);

/* parser.c	*/

void	identifier_init(t_data *data);

/* map_check */

void	map_check(t_data *data);

/* utils.c	*/

void	initializer(t_data *data);
void	free_and_exit(t_data *data, char *msg);

#endif
