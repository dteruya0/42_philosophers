/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dteruya <dteruya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 16:30:46 by dteruya           #+#    #+#             */
/*   Updated: 2025/04/29 16:10:29 by dteruya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	*monitoring(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (end_cycle(data))
	{
		if (philo_died(data))
			break ;
		if (philo_satiated(data))
		{
			pthread_mutex_lock(&data->monitor_mtx);
			data->end_simulation = true;
			pthread_mutex_unlock(&data->monitor_mtx);
			break ;
		}
		usleep(200);
	}
	return (NULL);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->num_philos == 1)
	{
		printf("%ld philo %d has taken a fork\n", get_time(philo->data), philo->id);
		usleep(philo->data->time_to_die * 1000);
		return (NULL);
	}
	while (end_cycle(philo->data))
	{
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}

void	simulation(t_data *data)
{
	int	i;

	data->start_simulation = get_absolute_time();
	i = 0;
	while (i < data->num_philos)
	{
		data->philos[i].last_meal = data->start_simulation;
		pthread_create(&data->philos[i].thread_id, NULL, routine, &data->philos[i]);
		i++;
	}
	pthread_create(&data->monitor, NULL, monitoring, data);
	i = 0;
	while (i < data->num_philos)
	{
		pthread_join(data->philos[i].thread_id, NULL);
		i++;
	}
	pthread_join(data->monitor, NULL);
}

void	*take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->r_fork->fork);
		pthread_mutex_lock(&philo->data->print_mtx);
		printf("%ld philo %d has taken a fork\n", get_time(philo->data), philo->id);
		pthread_mutex_lock(&philo->l_fork->fork);
		printf("%ld philo %d has taken a fork\n", get_time(philo->data), philo->id);
		pthread_mutex_unlock(&philo->data->print_mtx);
	}
	else
	{
		pthread_mutex_lock(&philo->l_fork->fork);
		pthread_mutex_lock(&philo->data->print_mtx);
		printf("%ld philo %d has taken a fork\n", get_time(philo->data), philo->id);
		pthread_mutex_lock(&philo->r_fork->fork);
		printf("%ld philo %d has taken a fork\n", get_time(philo->data), philo->id);
		pthread_mutex_unlock(&philo->data->print_mtx);
	}
	return (NULL);
}

bool	end_cycle(t_data *data)
{
	bool	end;

	pthread_mutex_lock(&data->monitor_mtx);
	end = !data->end_simulation;
	pthread_mutex_unlock(&data->monitor_mtx);
	return (end);
}