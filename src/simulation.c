/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dteruya <dteruya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 16:30:46 by dteruya           #+#    #+#             */
/*   Updated: 2025/04/23 16:41:19 by dteruya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	*monitoring(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (!data->end_simulation)
	{
		if (philo_died(data))
			data->end_simulation = true;
		if (philo_satiated(data))
			data->end_simulation = true;
	}
	return (NULL);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!philo->data->end_simulation)
	{
		if (philo->data->num_philos == 1)
		{
			printf("%ld philo %d has taken a fork\n", get_time(philo->data), philo->id);
			usleep(philo->data->time_to_die * 1000);
			printf("%ld philo %i died\n", get_time(philo->data), philo->id);
			philo->data->end_simulation = true;
			break;
		}
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
		data->philos[i].last_meal = data->start_simulation;
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
