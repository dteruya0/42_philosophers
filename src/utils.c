/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dteruya <dteruya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 11:51:43 by dteruya           #+#    #+#             */
/*   Updated: 2025/04/18 19:04:16 by dteruya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"
/*
long	get_time(t_data *data)
{
	struct timeval	time;
	long	curr_time;
	long	init_time;

	gettimeofday(&time, NULL);
	
	return ();
}*/

int	time_to_think(t_data *data)
{
	int	think;

	think = data->time_to_die - (data->time_to_eat + data->time_to_sleep);
	if (think < 0)
		think = 0;
	else if (think > 5)
		think = 5;
	return (think);
}