/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dteruya <dteruya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 13:31:08 by dteruya           #+#    #+#             */
/*   Updated: 2025/04/29 17:20:11 by dteruya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	*eating(t_philo *philo)
{
	t_data	*data;
	long	start_time;

	data = philo->data;
	take_forks(philo);
	pthread_mutex_lock(&philo->data->table_mtx);
	philo->last_meal = get_absolute_time();
	philo->meals_counter++;
	if (data->must_eat > 0 && philo->meals_counter >= data->must_eat)
		philo->state = true;
	pthread_mutex_unlock(&philo->data->table_mtx);
	if (!end_cycle(data))
		return (NULL);
	print_msg(philo, "is eating");
	start_time = get_time(data);
	while (end_cycle(data) && get_time(data) - start_time < data->time_to_eat)
		usleep(200);
	pthread_mutex_unlock(&philo->l_fork->fork);
	pthread_mutex_unlock(&philo->r_fork->fork);
	return (NULL);
}

void	*sleeping(t_philo *philo)
{
	if (!end_cycle(philo->data))
		return (NULL);
	print_msg(philo, "is sleeping");
	usleep(philo->data->time_to_sleep * 1000);
	return (NULL);
}

void	*thinking(t_philo *philo)
{
	if (!end_cycle(philo->data))
		return (NULL);
	print_msg(philo, "is thinking");
	usleep(philo->data->time_to_sleep * 1000);
	return (NULL);
}