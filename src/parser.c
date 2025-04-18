/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dteruya <dteruya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 17:44:07 by dteruya           #+#    #+#             */
/*   Updated: 2025/04/14 17:58:39 by dteruya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	ft_atoi(const char *nptr)
{
	int	index;
	int	number;
	int	sign;

	sign = 1;
	number = 0;
	index = 0;
	while ((nptr[index] >= 9 && nptr[index] <= 13) || nptr[index] == 32)
		index++;
	if (nptr[index] == '-')
	{
		sign = (-1);
		index++;
	}
	else if (nptr[index] == '+')
		index++;
	while (nptr[index] >= '0' && nptr[index] <= '9')
	{
		number = (number * 10) + (nptr[index] - '0');
		index++;
	}
	return (number * sign);
}

static int	ft_isdigit(char c)
{
	if (c > 47 && c < 58)
		return (1);
	return (0);
}

bool	parse_args(int ac, char **av)
{
	int		i;
	bool	flag;

	flag = false;
	i = 1;
	while (i < ac)
	{
		if (!ft_isdigit(*av[i]) || ft_atoi(av[i]) < 0)
			flag = true;
		i++;
	}
	return (flag);
}
