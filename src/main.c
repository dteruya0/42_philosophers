/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dteruya <dteruya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 16:57:11 by dteruya           #+#    #+#             */
/*   Updated: 2025/05/08 14:53:24 by dteruya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	clean_up(t_data *data)
{
	if (!data->philos && !data->forks)
		return ;
	if (data->philos)
		free(data->philos);
	if (data->forks)
		free(data->forks);
	return ;
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac == 5 || ac == 6)
	{
		if (!parse_args(ac, av))
		{
			init(&data, av);
			simulation(&data);
			clean_up(&data);
		}
		else
			printf(ARG);
	}
	else
		printf(ARG);
	return (0);
}
