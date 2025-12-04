/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcesar-s <jcesar-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 19:17:52 by jcesar-s          #+#    #+#             */
/*   Updated: 2025/09/24 19:19:28 by jcesar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
#include <limits.h>

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*allocated_ptr;

	allocated_ptr = malloc(size * nmemb);
	if (!allocated_ptr)
		return (NULL);
	memset(allocated_ptr, 0, size * nmemb);
	return (allocated_ptr);
}

int	ft_strlen(const char *str)
{
	int	len;

	len = 0;
	while (str[len] != '\0')
		++len;
	return (len);
}

int	is_valid_number(char *str)
{
	while ((*str >= 9 && *str <= 13) || *str == 32)
		++str;
	if (*str == '-')
		return (FALSE);
	if (*str == '+')
		++str;
	if (*str == '\0')
		return (FALSE);
	while (*str != '\0')
	{
		if (*str < '0' || *str > '9')
			return (FALSE);
		++str;
	}
	return (TRUE);
}

int	ft_atoi_safe(const char *nptr, int *result)
{
	long	number;

	number = 0;
	while ((*nptr >= 9 && *nptr <= 13) || *nptr == 32)
		++nptr;
	if (*nptr == '+')
		++nptr;
	while (*nptr >= '0' && *nptr <= '9')
	{
		number = number * 10 + (*nptr - '0');
		if (number > INT_MAX)
			return (EXIT_FAILURE);
		++nptr;
	}
	if (number == 0)
		return (EXIT_FAILURE);
	*result = (int) number;
	return (EXIT_SUCCESS);
}

int	ft_error(const char *message)
{
	int	message_len;

	message_len = ft_strlen(message);
	write(2, "Error: ", 7);
	write(2, message, message_len);
	write(2, "\n", 1);
	return (1);
}
