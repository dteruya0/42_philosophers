/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dteruya <dteruya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 11:51:43 by dteruya           #+#    #+#             */
/*   Updated: 2025/04/29 15:14:02 by dteruya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

long	get_absolute_time(void)
{
	struct timeval	time;
	long	current;

	gettimeofday(&time, NULL);
	current = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (current);
}

long	get_time(t_data *data)
{
	struct timeval	time;
	long	current;

	gettimeofday(&time, NULL);
	current = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (current - data->start_simulation);
}

bool	philo_died(t_data *data)
{
	int	i;
	int	n_philos;
	int	die_time;
	int	now;

	i = 0;
	n_philos = data->num_philos;
	die_time = data->time_to_die;
	now = get_time(data);
	while (i < n_philos)
	{
		pthread_mutex_lock(&data->table_mtx);
		if (now - data->philos[i].last_meal > die_time)
		{
			pthread_mutex_lock(&data->print_mtx);
			printf(R"%lu philo %i died\n"RST, get_time(data), data->philos[i].id);
			pthread_mutex_unlock(&data->print_mtx);
			data->end_simulation = true;
			pthread_mutex_unlock(&data->table_mtx);
			return (true);
		}
		pthread_mutex_unlock(&data->table_mtx);
		i++;
	}
	return (false);
}

bool	philo_satiated(t_data *data)
{
	int	i;
	int	meals;

	i = 0;
	if (data->must_eat < 0)
		return false;
	while (i < data->num_philos)
	{
		pthread_mutex_lock(&data->table_mtx);
		meals = data->philos[i].meals_counter;
		pthread_mutex_unlock(&data->table_mtx);
		if (meals < data->must_eat)
			return false;
		i++;
	}
	return true;
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