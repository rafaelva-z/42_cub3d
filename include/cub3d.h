/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-estr <fda-estr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 20:44:05 by rvaz              #+#    #+#             */
/*   Updated: 2024/01/27 16:00:13 by fda-estr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# ifndef DEBUG
#  define DEBUG 0
# endif

# define SKY_COLOR		0x005274ff
# define WALL_COLOR		0x00aeb5d1
# define FLOOR_COLOR	0x000c1126
# define START_FOV		66

# include "../lib/libft/libft.h"
# include "../lib/minilibx-linux/mlx.h"
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <math.h>

//	Messages
# define ERR_ARGC		"cub3d: wrong number of arguments. Use only a map path\n"
# define ERR_MALLOC		"cub3d: malloc() failed\n"
# define ERR_MLX_INIT	"cub3d: mlx_init() failed\n"
# define ERR_MLX_WIN	"cub3d: mlx_new_window() failed\n"
# define ERR_MAP		"cub3d: invalid map\n"

# define MSG_EXIT		"cub3d: Thank you for testing!\n"

# define M_PI			3.14159265358979323846

//	Screen Resolution
# define WIN_WIDTH		750
# define WIN_HEIGHT		500

//	Keyboard
# define KEY_ESC		65307
# define KEY_LEFT		65361
# define KEY_UP			65362
# define KEY_RIGHT		65363
# define KEY_DOWN		65364
# define KEY_PLUS		65451
# define KEY_MINUS		65453
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
# define ROT			KEY_E
# define RROT			KEY_Q
# define LOOK_UP		KEY_UP
# define LOOK_DOWN		KEY_DOWN

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
	double		fov;
	int			vertical;
}				t_player;

typedef struct s_image
{
	void		*north_img;				//	ponter to north image
	void		*east_img;				//	pointer to east image
	void		*south_img;				//	pointer to south image
	void		*west_img;				//	pointer to west image
	void		*mm_wall_img;				//	pointer to west image
	void		*mm_floor_img;				//	pointer to west image
	void		*mm_vacum_img;				//	pointer to west image
	void		*frame_x;
	void		*frame_y;
}				t_image;

typedef struct s_map
{
	char		**map;
	t_2d_point	size;
}				t_map;

typedef struct s_ray
{
	t_2d_point	dir;
	t_2d_point	last_hit;
	double		distance;
}				t_ray;

// this one may be provisory
typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_img;

/**
 * @brief Structure that holds file content and file names
*/
typedef struct s_file
{
	char	**file;
	char	*north_file;
	char	*east_file;
	char	*south_file;
	char	*west_file;
	char	*ceiling_file;
	char	*floor_file;
}				t_file;

/**
 * @brief Structure that holds all the data needed for the program
*/
typedef struct s_data
{
	void		*mlx;					//	pointer to mlx
	void		*mlx_win;				//	pointer to the mlx window
	t_img		*img;
	t_file		*file;					//	pointer to the file struct
	t_map		map;					//	pointer to map
	t_player	player;					//	pointer to player's struct
	t_image		ig;
}				t_data;

//		initializer.c
void	initializer(t_data *data);

//		hooks.c
int		key_reader(int keycode, t_data *data);
int		close_pgm(t_data *data);

//		free.c
void	free_data(t_data *data);
void	free_and_exit(t_data *data, char *msg, int exit_status);

//		parser.c
void	parser(t_data *data, char *str);

//		parser_2.c
void	identifier_init(t_data *data);

//		map_check.c
void	map_check(t_data *data);

//		map_check_utils
void	map_and_player_init(t_data *data);

//		map_check_utils
void	map_and_player_init(t_data *data);

//		utils.c
void	initializer(t_data *data);
int		coordinate_finder(char **mtx, char c, char axle);
void	rotate_point(t_2d_point *point, double angle);
int		display_error(char *str);
int		is_inside_map(t_2d_point point, t_2d_point map_size);
int		is_wall(t_2d_point point, t_data *data);

//		dda.c
double	dda(t_2d_point *start, t_ray *ray, t_data *data);

//		raycat.c
void	raycast(t_data *data);

//		minimap.c
void	minimap(t_data *data);

void	move_player(int keycode, t_data *data);
void	adjust_fov(int keycode, t_data *data);
void	rotate_player(int keycode, t_data *data);
void	draw_pixel(t_img *img, int x, int y, int color);
void	draw_line(t_vector line, t_img *img, int color);
#endif
