/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dteruya <dteruya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 13:31:08 by dteruya           #+#    #+#             */
/*   Updated: 2025/04/24 18:41:48 by dteruya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	*eating(t_philo *philo)
{
	long last_meal;

	take_forks(philo);
	pthread_mutex_lock(&philo->status);
	last_meal = philo->last_meal;
	philo->last_meal = get_absolute_time();
	printf(G"%lu philo %d is eating\n"RST, get_time(philo->data), philo->id);
	philo->meals_counter++;
	pthread_mutex_unlock(&philo->status);
	usleep(philo->data->time_to_eat *1000);
	pthread_mutex_unlock(&philo->l_fork->fork);
	pthread_mutex_unlock(&philo->r_fork->fork);
	return (NULL);
}

void	*sleeping(t_philo *philo)
{
	if (!philo->data->end_simulation)
	{
		printf("%lu philo %d is sleeping\n", get_time(philo->data), philo->id);
		usleep(philo->data->time_to_sleep *1000);
	}
	return (NULL);
}

void	*thinking(t_philo *philo)
{
	if (!philo->data->end_simulation)
	{
		printf("%lu philo %d is thinking\n", get_time(philo->data), philo->id);
		usleep(philo->data->time_to_sleep *1000);
	}
	return (NULL);
}