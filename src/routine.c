/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dteruya <dteruya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 13:31:08 by dteruya           #+#    #+#             */
/*   Updated: 2025/05/08 14:39:15 by dteruya          ###   ########.fr       */
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

int	take_forks(t_philo *philo)
{
	t_data			*data;
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;

	data = philo->data;
	if (philo->id % 2 == 0)
	{
		first = &philo->r_fork->fork;
		second = &philo->l_fork->fork;
	}
	else
	{
		first = &philo->l_fork->fork;
		second = &philo->r_fork->fork;
	}
	if (!lock_fork(data, first))
		return (0);
	print_msg(philo, "has taken a fork");
	if (!lock_fork(data, second))
	{
		pthread_mutex_unlock(first);
		return (0);
	}
	print_msg(philo, "has taken a fork");
	return (1);
}

void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->l_fork->fork);
	pthread_mutex_unlock(&philo->r_fork->fork);
}
