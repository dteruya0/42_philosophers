/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dteruya <dteruya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 14:56:02 by dteruya           #+#    #+#             */
/*   Updated: 2025/05/08 14:57:14 by dteruya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

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

int	lock_fork(t_data *data, pthread_mutex_t *fork)
{
	pthread_mutex_lock(fork);
	if (!end_cycle(data))
	{
		pthread_mutex_unlock(fork);
		return (0);
	}
	return (1);
}
