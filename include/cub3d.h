/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-estr <fda-estr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 20:44:05 by rvaz              #+#    #+#             */
/*   Updated: 2024/01/21 23:28:07 by fda-estr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../lib/libft/libft.h"
# include "../lib/minilibx-linux/mlx.h"
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <math.h>

typedef struct s_player
{
	int		pos_x;						//	player's x position
	int		pos_y;						//	player's y position
}				t_player;

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
	t_player	*player;				//	pointer to player's struct
}				t_data;

/* parser.c	*/

void	parser(t_data *data, char *str);

/* parser.c	*/

void	identifier_init(t_data *data);

/* utils.c	*/

void	initializer(t_data *data);

#endif
