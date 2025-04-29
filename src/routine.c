/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dteruya <dteruya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 13:31:08 by dteruya           #+#    #+#             */
/*   Updated: 2025/04/29 16:01:28 by dteruya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	*eating(t_philo *philo)
{
	take_forks(philo);
	pthread_mutex_lock(&philo->data->table_mtx);
	philo->last_meal = get_time(philo->data);
	printf(G"%lu philo %d is eating\n"RST, get_time(philo->data), philo->id);
	philo->meals_counter++;
	pthread_mutex_unlock(&philo->data->table_mtx);
	usleep(philo->data->time_to_eat * 1000);
	pthread_mutex_unlock(&philo->l_fork->fork);
	pthread_mutex_unlock(&philo->r_fork->fork);
	return (NULL);
}

void	*sleeping(t_philo *philo)
{
	if (end_cycle(philo->data))
	{
		pthread_mutex_lock(&philo->data->print_mtx);
		printf("%lu philo %d is sleeping\n", get_time(philo->data), philo->id);
		pthread_mutex_unlock(&philo->data->print_mtx);
		usleep(philo->data->time_to_sleep *1000);
	}
	return (NULL);
}

void	*thinking(t_philo *philo)
{
	if (end_cycle(philo->data))
	{
		pthread_mutex_lock(&philo->data->print_mtx);
		printf("%lu philo %d is thinking\n", get_time(philo->data), philo->id);
		pthread_mutex_unlock(&philo->data->print_mtx);
		usleep(philo->data->time_to_sleep *1000);
	}
	return (NULL);
}