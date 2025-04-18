/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dteruya <dteruya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 16:34:31 by dteruya           #+#    #+#             */
/*   Updated: 2025/04/18 15:34:26 by dteruya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	error_exit(const char *error)
{
	printf(R "%s\n" RST, error);
	exit(EXIT_FAILURE);
}

void	clean_up(t_data *data)
{
	if (!data->philos && !data->forks)
		return;
	if (data->philos)
		free(data->philos);
	if (data->forks)
		free(data->forks);
	return;
}