/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-estr <fda-estr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 16:08:06 by fda-estr          #+#    #+#             */
/*   Updated: 2024/02/09 13:22:21 by fda-estr         ###   ########.fr       */
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
		free_and_exit(data, "Error: invalid file extension", 1);
}

static void	new_line_check(t_data *data, char *s)
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
	}
	if (!s[i])
	{
		free(s);
		free_and_exit(data, ERR_MAP, 1);
	}
	while (s[++i])
	{
		if (s[i] == '\n' && s[i + 1] == '\n')
		{
			free(s);
			free_and_exit(data, ERR_MAP, 1);
		}
	}
	if (i && s[i - 1] == '\n')
	{
		free(s);
		free_and_exit(data, ERR_MAP, 1);
	}
}

static void	file_extractor(t_data *data, char *str)
{
	int		fd;
	char	*s;
	char	*join_s;

	s = NULL;
	join_s = NULL;
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
		free_and_exit(data, "Error: empty map...\n", 1);
	new_line_check(data, join_s);
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
	file_extractor(data, str);
	trimmer(data);
	if (DEBUG == 1)
	{
		printf("====MAP-FILE================\n");
		for (int i = 0; data->file->file[i]; i++)
			printf("%s|\n", data->file->file[i]);
		printf("====MAP-END=================\n");
	}
	identifier_init(data);
	if (DEBUG == 1)
	{
		printf("\n===TEXTURE-FILES============\n");
		printf("SO: %s|\n", data->file->south_file);
		printf("NO: %s|\n", data->file->north_file);
		printf("WE: %s|\n", data->file->west_file);
		printf("EA: %s|\n", data->file->east_file);
		printf("F: %s|\n", data->file->floor_file);
		printf("C: %s|\n", data->file->ceiling_file);
		printf("\n===TEXTURE-FILES-END========\n");
	}
	map_check(data);
	if (DEBUG == 1)
		printf("\nVALID MAP!\n");
	texture_parser(data);
	enemy_parser(data);
	free_file(data->file);
	data->file = NULL;
}
