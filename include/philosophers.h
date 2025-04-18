/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dteruya <dteruya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 16:58:28 by dteruya           #+#    #+#             */
/*   Updated: 2025/04/18 19:02:50 by dteruya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <stdbool.h>
# include <sys/time.h>

// Reset
# define RST	"\033[0m"

// Cores básicas
# define R	"\033[0;31m"
# define G	"\033[0;32m"
# define Y	"\033[0;33m"
# define B	"\033[0;34m"
# define W	"\033[0;37m"

//define macros
# define ARG "Error: Incorrect arguments\n"
# define MALLOC "Error: Malloc error\n"

typedef pthread_mutex_t	t_mtx;
typedef struct s_philo t_philo;

typedef struct s_fork
{
	int		id;
	t_mtx	fork;
}	t_fork;

typedef struct s_data
{
	int			num_philos;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			time_to_think;
	int			must_eat;
	long		start_simulation;
	bool		end_simulation;
	pthread_t	monitor;
	t_mtx		print_mtx;
	t_mtx		table_mtx;
	t_fork		*forks;
	t_philo		*philos;
}	t_data;

typedef struct s_philo
{
	int			id;
	int			last_meal;
	int			meals_counter;
	bool		state;
	pthread_t	thread_id;
	t_fork		*r_fork;
	t_fork		*l_fork;
	t_data		*data;
}	t_philo;

bool	parse_args(int ac, char **av);
void	init(t_data *data, char **av);
int		ft_atoi(const char *nptr);
void	error_exit(const char *error);
//long	get_time(t_data *data);
void	clean_up(t_data *data);
int		time_to_think(t_data *data);

#endif