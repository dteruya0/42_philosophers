/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dteruya <dteruya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 16:30:46 by dteruya           #+#    #+#             */
/*   Updated: 2025/04/24 18:47:58 by dteruya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	*monitoring(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (!data->end_simulation)
	{
		if (philo_died(data) || philo_satiated(data))
		{
			pthread_mutex_lock(&data->table_mtx);
			data->end_simulation = true;
			pthread_mutex_unlock(&data->table_mtx);
		}
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
	while (!philo->data->end_simulation)
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
	pthread_create(&data->monitor, NULL, monitoring, data);
	i = 0;
	while (i < data->num_philos)
	{
		data->philos[i].last_meal = get_absolute_time();
		pthread_create(&data->philos[i].thread_id, NULL, routine, &data->philos[i]);
		i++;
	}
	pthread_join(data->monitor, NULL);
	i = 0;
	while (i < data->num_philos)
	{
		pthread_join(data->philos[i].thread_id, NULL);
		i++;
	}
}

void	*take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->r_fork->fork);
		printf("%ld philo %d has taken a fork\n", get_time(philo->data), philo->id);
		pthread_mutex_lock(&philo->l_fork->fork);
		printf("%ld philo %d has taken a fork\n", get_time(philo->data), philo->id);
	}
	else
	{
		pthread_mutex_lock(&philo->r_fork->fork);
		printf("%ld philo %d has taken a fork\n", get_time(philo->data), philo->id);
		pthread_mutex_lock(&philo->l_fork->fork);
		printf("%ld philo %d has taken a fork\n", get_time(philo->data), philo->id);
	}
	return (NULL);
}
