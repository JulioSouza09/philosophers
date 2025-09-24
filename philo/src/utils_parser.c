/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcesar-s <jcesar-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 19:14:51 by jcesar-s          #+#    #+#             */
/*   Updated: 2025/09/24 19:29:26 by jcesar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *nptr)
{
	int	result;
	int	signal;

	result = 0;
	signal = 1;
	while ((*nptr >= 9 && *nptr <= 13) || *nptr == 32)
		++nptr;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			signal *= -1;
		++nptr;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		result = result * 10 + (*nptr - '0');
		++nptr;
	}
	return (result * signal);
}

int	is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	is_number(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] != '-' && str[i] != '+' && is_digit(str[i]) == FALSE)
			return (0);
		++i;
	}
	return (1);
}

int	is_all_numbers(int argc, char **argv)
{
	int	i;

	i = 0;
	while (i < argc)
	{
		if (is_number(argv[i]) == FALSE)
			return (0);
		++i;
	}
	return (1);
}
