/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dteruya <dteruya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 16:57:11 by dteruya           #+#    #+#             */
/*   Updated: 2025/05/08 11:31:25 by dteruya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

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
