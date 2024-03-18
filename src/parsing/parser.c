/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-estr <fda-estr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 16:08:06 by fda-estr          #+#    #+#             */
/*   Updated: 2024/03/18 16:10:52 by fda-estr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	extension(t_data *data, char *str)
{
	int		i;

	i = 0;
	while (str[i])
		i++;
	while (--i > 0 && str[i] != '.')
		;
	if (ft_strncmp(str + i, ".cub", 5))
		free_and_exit(data, ERR_EXT, 1);
}

static int	new_line_check(char *s)
{
	int	i;
	int	line_count;

	i = -1;
	line_count = 0;
	while (s[++i])
	{
		if (s[i] == '\n')
			continue ;
		if (line_count == 6)
			break ;
		line_count++;
		while (s[++i] && s[i] != '\n')
			;
		if (!s[i])
			return (0);
	}
	if (!s[i])
		return (0);
	while (s[++i])
		if (s[i] == '\n' && s[i + 1] == '\n')
			return (0);
	if (i && s[i - 1] == '\n')
		return (0);
	return (1);
}

static void	file_extractor(t_data *data, char *str, char *s, char *join_s)
{
	int		fd;

	fd = open(str, O_RDONLY);
	if (fd == -1)
		free_and_exit(data, ERR_FD, 1);
	while (1)
	{
		s = get_next_line(fd);
		if (!s)
			break ;
		join_s = ft_strjoin_free(join_s, s, 3);
	}
	if (!join_s)
		free_and_exit(data, ERR_EMPTY, 1);
	if (new_line_check(join_s) == 0)
	{
		free (join_s);
		free_and_exit(data, ERR_MAP, 1);
	}
	data->file->file = ft_split(join_s, '\n');
	if (!data->file->file)
		free_and_exit(data, ERR_MALLOC, 1);
	free(join_s);
	close (fd);
}

static void	trimmer(t_data *data)
{
	int		i;
	char	*temp;

	i = -1;
	while (++i < 6)
	{
		temp = data->file->file[i];
		data->file->file[i] = ft_strtrim(data->file->file[i], " ");
		free(temp);
	}
}

void	parser(t_data *data, char *str)
{
	extension(data, str);
	file_extractor(data, str, NULL, NULL);
	trimmer(data);
	identifier_init(data);
	ceiling_floor_init(data);
	map_check(data);
	texture_parser(data);
	sprite_parser(data);
	free_file(data->file);
	data->file = NULL;
}
