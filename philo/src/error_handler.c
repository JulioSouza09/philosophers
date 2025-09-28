/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcesar-s <jcesar-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 19:08:03 by jcesar-s          #+#    #+#             */
/*   Updated: 2025/09/28 21:11:17 by jcesar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_putstr_fd(char *str, int fd)
{
	if (!str)
		return (ft_putstr_fd("(null)", fd));
	while (*str != '\0')
		write(fd, str++, 1);
}

int	put_usage_error(char *program_path)
{
	ft_putstr_fd("Usage: ", 2);
	ft_putstr_fd(program_path, 2);
	ft_putstr_fd(" n_philo time_to_die time_to_eat time_to_sleep ", 2);
	ft_putstr_fd("[n_times_each_philosopher_must_eat]\n", 2);
	return (EXIT_FAILURE);
}
