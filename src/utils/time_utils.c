/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvaz <rvaz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 12:15:47 by rvaz              #+#    #+#             */
/*   Updated: 2024/03/12 21:15:04 by rvaz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	begining_timestamp(t_data *data)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) < 0)
		free_and_exit(data, ERR_TIME, 1);
	data->start_time = (time.tv_sec * 1000) + (time.tv_usec / 1000);
}

uint64_t	get_timestamp(t_data *data)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) < 0)
		free_and_exit(data, ERR_TIME, 1);
	return ((time.tv_sec * 1000)
		+ (time.tv_usec / 1000) - data->start_time);
}

uint64_t	get_abs_timestamp(t_data *data)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) < 0)
		free_and_exit(data, ERR_TIME, 1);
	return (time.tv_sec + time.tv_usec);
}
