/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dteruya <dteruya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 11:51:43 by dteruya           #+#    #+#             */
/*   Updated: 2025/05/08 11:51:23 by dteruya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

long	get_absolute_time(void)
{
	struct timeval	time;
	long			current;

	gettimeofday(&time, NULL);
	current = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (current);
}

long	get_time(t_data *data)
{
	struct timeval	time;
	long			current;

	gettimeofday(&time, NULL);
	current = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (current - data->start_simulation);
}

bool	philo_died(t_data *data)
{
	int		i;
	long	now_ms;
	long	last_ms;

	i = 0;
	while (i < data->num_philos)
	{
		now_ms = get_absolute_time();
		pthread_mutex_lock(&data->table_mtx);
		last_ms = data->philos[i].last_meal;
		pthread_mutex_unlock(&data->table_mtx);
		if (now_ms - last_ms >= data->time_to_die)
		{
			pthread_mutex_lock(&data->print_mtx);
			printf(R"%ld philo %d died\n"RST,
				get_time(data), data->philos[i].id);
			pthread_mutex_unlock(&data->print_mtx);
			pthread_mutex_lock(&data->monitor_mtx);
			data->end_simulation = true;
			pthread_mutex_unlock(&data->monitor_mtx);
			return (true);
		}
		i++;
	}
	return (false);
}

bool	levou_as_comidas(t_data *data)
{
	int	i;
	int	meals;

	i = 0;
	if (data->must_eat < 0)
		return (false);
	while (i < data->num_philos)
	{
		pthread_mutex_lock(&data->table_mtx);
		meals = data->philos[i].meals_counter;
		pthread_mutex_unlock(&data->table_mtx);
		if (meals < data->must_eat)
			return (false);
		i++;
	}
	return (true);
}

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
