/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dteruya <dteruya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 16:30:46 by dteruya           #+#    #+#             */
/*   Updated: 2025/05/08 14:57:08 by dteruya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static void	*monitoring(void *arg)
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

static void	*routine(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = philo->data;
	while (end_cycle(data))
	{
		if (data->num_philos == 1)
		{
			printf("%ld philo %d has taken a fork\n", get_time(data), philo->id);
			usleep(data->time_to_die * 1000);
			return (NULL);
		}
		if (end_cycle(data))
		{
			if (!take_forks(philo))
				return (NULL);
			eating(philo);
			drop_forks(philo);
			sleeping(philo);
			thinking(philo);
		}
	}
	return (NULL);
}

void	simulation(t_data *data)
{
	int	i;

	data->start_simulation = get_absolute_time();
	pthread_mutex_lock(&data->table_mtx);
	i = 0;
	while (i < data->num_philos)
	{
		data->philos[i].last_meal = data->start_simulation;
		i++;
	}
	pthread_mutex_unlock(&data->table_mtx);
	pthread_create(&data->monitor, NULL, monitoring, data);
	i = 0;
	while (i < data->num_philos)
	{
		pthread_create(&data->philos[i].thread_id,
			NULL, routine, &data->philos[i]);
		i++;
	}
	pthread_join(data->monitor, NULL);
	i = 0;
	while (i < data->num_philos)
		pthread_join(data->philos[i++].thread_id, NULL);
}

bool	end_cycle(t_data *data)
{
	bool	end;

	pthread_mutex_lock(&data->monitor_mtx);
	end = !data->end_simulation;
	pthread_mutex_unlock(&data->monitor_mtx);
	return (end);
}
