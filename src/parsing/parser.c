/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fda-estr <fda-estr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 16:08:06 by fda-estr          #+#    #+#             */
/*   Updated: 2024/01/24 17:57:08 by fda-estr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	extension(t_data *data, char *str)
{
	char	*temp;

	temp = str;
	while (*temp && *temp != '.')
		temp++;
	if (ft_strncmp(temp, ".cub", 5))
		free_and_exit(data, "Error: invalid file extension");
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
			continue;
		if (line_count == 6)
			break ;
		line_count++;
		while (s[++i] && s[i] != '\n')
			;
	}
	if (!s[i])
	{
		free (s);
		free_and_exit(data, "Error: invalid map\n");
	}
	while (s[++i])
		if (s[i] == '\n' && s[i + 1] == '\n')
		{
			free (s);
			free_and_exit(data, "Error: invalid map\n");
		}
	if (i && s[i - 1] == '\n')
	{
		free (s);
		free_and_exit(data, "Error: invalid map\n");
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
		printf("Error\n");	//	Error handling
	while (1)
	{
		s = get_next_line(fd);
		if (!s)
			break ;
		join_s = ft_strjoin_free(join_s, s, 3);
	}
	if (!join_s)
	{
		printf("Error: empty map...\n");
		exit (1);
	}
	new_line_check(data, join_s);
	data->file->file = ft_split(join_s, '\n');
	free (join_s);
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
		free (temp);
	}
}

void	parser(t_data *data, char *str)
{
	extension(data, str);
	file_extractor(data, str);
	trimmer(data);

	int i = -1;
	while (data->file->file[++i])
		printf("%s|\n", data->file->file[i]);


	identifier_init(data);

	
	printf("SO: %s|\n", data->file->south_file);
	printf("NO: %s|\n", data->file->north_file);
	printf("WE: %s|\n", data->file->west_file);
	printf("EA: %s|\n", data->file->east_file);
	printf("F: %s|\n", data->file->floor_file);
	printf("C: %s|\n", data->file->ceiling_file);

	map_check(data);
	printf("\nVALID MAP!\n");
	free (data->file);
}
