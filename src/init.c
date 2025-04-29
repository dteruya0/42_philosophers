/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dteruya <dteruya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 12:03:04 by dteruya           #+#    #+#             */
/*   Updated: 2025/04/29 16:10:24 by dteruya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static void	init_data(t_data *data, char **av)
{
	data->num_philos = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	data->time_to_think = time_to_think(data);
	data->must_eat = -1;
	if (av[5])
		data->must_eat = ft_atoi(av[5]);
	data->end_simulation = false;
	pthread_mutex_init(&data->print_mtx, NULL);
	pthread_mutex_init(&data->table_mtx, NULL);
	pthread_mutex_init(&data->monitor_mtx, NULL);
}

static void	init_forks(t_data *data)
{
	int	i;

	i = 0;
	data->forks = malloc(sizeof(t_fork) * data->num_philos);
	if (!data->forks)
		error_exit(MALLOC);
	while (i < data->num_philos)
	{
		pthread_mutex_init(&data->forks[i].fork, NULL);
		data->forks[i].id = i + 1;
		i++;
	}
}

static t_fork	*designate_fork(t_data *data, char side)
{
	int	fork_id;

	if (side == 'r')
		fork_id = data->philos->id;
	else
		fork_id = data->philos->id + 1 % data->num_philos;
	return (&data->forks[fork_id]);
}

void	init_philos(t_data *data)
{
	int		i;

	i = 0;
	data->philos = malloc(sizeof(t_philo) * data->num_philos);
	if (!data->philos)
		error_exit(MALLOC);
	while (i < data->num_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].meals_counter = 0;
		data->philos[i].state = false;
		data->philos[i].r_fork = designate_fork(data, 'r');
		data->philos[i].l_fork = designate_fork(data, 'l');
		data->philos[i].data = data;
		i++;
	}
}

void	init(t_data *data, char **av)
{
	init_data(data, av);
	init_forks(data);
	init_philos(data);
}