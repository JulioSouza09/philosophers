/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meal_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcesar-s <jcesar-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 16:10:18 by jcesar-s          #+#    #+#             */
/*   Updated: 2025/12/13 16:16:42 by jcesar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

long	get_timestamp(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	safe_print(t_philo *philo, long timestamp, char *message)
{
	long	start_time;

	start_time = philo->table->start_time;
	pthread_mutex_lock(philo->table->print_lock);
	if (is_dead(philo->table) == TRUE)
	{
		pthread_mutex_unlock(philo->table->print_lock);
		return (EXIT_FAILURE);
	}
	printf("%ld %d %s\n", timestamp - start_time, philo->id, message);
	pthread_mutex_unlock(philo->table->print_lock);
	return (EXIT_SUCCESS);
}

int	is_dead(t_table *table)
{
	int	dead;

	pthread_mutex_lock(table->state_lock);
	dead = table->stop_meal;
	pthread_mutex_unlock(table->state_lock);
	return (dead);
}

t_timestamp	get_val(t_table *table, t_timestamp *value)
{
	t_timestamp	val;

	pthread_mutex_lock(table->state_lock);
	val = *value;
	pthread_mutex_unlock(table->state_lock);
	return (val);
}

void	set_dead(t_table *table)
{
	pthread_mutex_lock(table->state_lock);
	table->stop_meal = TRUE;
	pthread_mutex_unlock(table->state_lock);
}
