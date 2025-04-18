/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dteruya <dteruya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 16:30:46 by dteruya           #+#    #+#             */
/*   Updated: 2025/04/18 19:05:44 by dteruya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"


//outro arquivo

sleep()

// usleep(tmepo de dormir)
//ja printa




void	*monitoring(void *arg)
{
	//ver se geral ja papou
	//ver se alguem foi de vasco
	//
	
}

void	*routine(void *arg)
{
	//come
	//dorme
	//pensa
	//monitoring
	//nao nessa ordem
}

void	simulation(t_data data)
{
	int	i;

//	pthread_create()
	printf("criou a porcaria do monitor\n");
	i = 0;
	while (i < data->num_philos)
	{
		printf("criou a porcaria dos philosophers\n");
		i++;
	}
	printf("O foda se o join\n");
}





init_simulation
criar pthread -> 