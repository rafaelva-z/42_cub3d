/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xpm_to_image.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-estr <fda-estr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 20:14:37 by fda-estr          #+#    #+#             */
/*   Updated: 2024/01/29 02:22:19 by fda-estr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	extract_file(t_data *data, t_xpm *xpm, char *file)
{
	int		fd;
	char	*s_join;
	char	*s;

	s_join = NULL;
	fd = open(file, O_RDONLY);
	if (fd == -1)
		free_and_exit(data, ERR_FD, 1);
	while (1)
	{
		s = get_next_line(fd);
		if (!s)
			break ;
		s_join = ft_strjoin_free(s_join, s, 3);
	}
	xpm->file = ft_split(s_join, '\n');
	if (!xpm->file)
		free_and_exit(data, ERR_MALLOC, 1);
}

static void	init_header(t_data *data, t_xpm *xpm)
{
	int	i;
	(void) data;

	i = -1;
	while (!ft_isdigit(xpm->file[3][++i]))
		;
	xpm->width = ft_atoi(xpm->file[3] + i);
	while (ft_isdigit(xpm->file[3][++i]))
		;
	while (!ft_isdigit(xpm->file[3][++i]))
		;
	xpm->hight = ft_atoi(xpm->file[3] + i);
	while (ft_isdigit(xpm->file[3][++i]))
		;
	while (!ft_isdigit(xpm->file[3][++i]))
		;
	xpm->nbr_colors = ft_atoi(xpm->file[3] + i);
	while (ft_isdigit(xpm->file[3][++i]))
		;
	xpm->char_per_color = ft_atoi(xpm->file[3] + i);
}

static void	init_color_table(t_data *data, t_xpm *xpm)
{
	int	i;
	char *temp;

	xpm->color_table = xpm->file + 4;
	xpm->colors = malloc(sizeof(int) * xpm->nbr_colors);
	i = -1;
	while (++i < xpm->nbr_colors)
	{
		temp = xpm->color_table[i];
		while (*temp && *temp != 'c')
			temp++;
		if (*temp)
			temp++;
		else
			printf("Error handling\n"); //	error handling
		if (!ft_strncmp(temp, "black", 5) || !ft_strncmp(temp, "white", 5) || !ft_strncmp(temp, "grey", 4))
			black_white();			//			THIS!!!
		else
			xpm->colors[i] = ft_atoi_base(temp);	//		ALSO THIS!!!
	}
}

int **ft_xpm_to_image(t_data *data, char *file)
{
	t_xpm 	xpm;
	int		**img;

	extract_file(data, &xpm, file);
	init_header(data, &xpm);
	init_color_table(data, &xpm);
	// init_image_table(data, &xpm);
	// image_generator(&xpm);

	img = ft_calloc(sizeof(int), 6);
	return (img);
}