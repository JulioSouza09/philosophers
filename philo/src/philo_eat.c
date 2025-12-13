/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_eat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcesar-s <jcesar-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 16:14:59 by jcesar-s          #+#    #+#             */
/*   Updated: 2025/12/13 16:48:52 by jcesar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
#include <pthread.h>
#include <stdlib.h>

int	take_forks(t_philo *philo)
{
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;

	if (philo->id & 1)
	{
		first = philo->left_fork;
		second = philo->right_fork;
	}
	else
	{
		first = philo->right_fork;
		second = philo->left_fork;
	}
	pthread_mutex_lock(first);
	safe_print(philo, get_timestamp(), "has taken a fork");
	pthread_mutex_lock(second);
	safe_print(philo, get_timestamp(), "has taken a fork");
	return (EXIT_SUCCESS);
}

int	put_down_forks(t_philo *philo)
{
	if (pthread_mutex_unlock(philo->left_fork) != 0)
		return (EXIT_FAILURE);
	if (pthread_mutex_unlock(philo->right_fork) != 0)
		return (EXIT_FAILURE);
	if (pthread_mutex_unlock(philo->right_fork) != 0)
		return (EXIT_FAILURE);
	if (pthread_mutex_unlock(philo->left_fork) != 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	philo_eat(t_philo *philo)
{
	take_forks(philo);
	pthread_mutex_lock(philo->table->state_lock);
	philo->last_meal = get_timestamp();
	philo->meals_count++;
	pthread_mutex_unlock(philo->table->state_lock);
	safe_print(philo, philo->last_meal, "is eating");
	usleep(philo->table->rules.time_to_eat * 1000);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	return (EXIT_SUCCESS);
}

void	case_1_philo(t_philo *philo)
{
	safe_print(philo, get_timestamp(), "has taken a fork");
	usleep(philo->table->rules.time_to_die * 1000);
	safe_print(philo, get_timestamp(), "has died");
	set_dead(philo->table);
}
