/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dteruya <dteruya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 13:31:08 by dteruya           #+#    #+#             */
/*   Updated: 2025/05/08 14:57:00 by dteruya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	eating(t_philo *philo)
{
	t_data	*data;
	long	start_time;

	data = philo->data;
	pthread_mutex_lock(&data->table_mtx);
	philo->last_meal = get_absolute_time();
	philo->meals_counter++;
	if (data->must_eat > 0 && philo->meals_counter >= data->must_eat)
		philo->state = true;
	pthread_mutex_unlock(&data->table_mtx);
	if (!end_cycle(data))
		return ;
	print_msg(philo, "is eating");
	start_time = get_time(data);
	while (end_cycle(data) && get_time(data) - start_time < data->time_to_eat)
		usleep(200);
}

void	sleeping(t_philo *philo)
{
	t_data	*data;
	long	start_time;

	data = philo->data;
	if (!end_cycle(data))
		return ;
	print_msg(philo, "is sleeping");
	start_time = get_time(data);
	while (end_cycle(data) && get_time(data) - start_time < data->time_to_sleep)
		usleep(200);
}

void	thinking(t_philo *philo)
{
	t_data	*data;
	long	start_time;

	data = philo->data;
	if (!end_cycle(data))
		return ;
	print_msg(philo, "is thinking");
	start_time = get_time(data);
	while (end_cycle(data) && get_time(data) - start_time < data->time_to_think)
		usleep(200);
}
