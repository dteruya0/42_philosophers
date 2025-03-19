/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dteruya <dteruya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 16:57:11 by dteruya           #+#    #+#             */
/*   Updated: 2025/03/19 16:57:20 by dteruya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	exit_error(char *error)
{
	printf("%s", error);
	exit(EXIT_FAILURE);
}

int	main(int argc, char **argv)
{
	pthread_t	t1;
	
	if (argc < 5 || argc > 6)
		exit_error(ARG);
	else
	{
		
	}
	return (0);
}