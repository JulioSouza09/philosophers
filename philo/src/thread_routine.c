/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcesar-s <jcesar-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 11:49:15 by jcesar-s          #+#    #+#             */
/*   Updated: 2025/09/28 20:56:11 by jcesar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

void	thread_msg(char *msg, int id, pthread_mutex_t *print_lock)
{
	pthread_mutex_lock(print_lock);
	printf(msg, id);
	pthread_mutex_unlock(print_lock);
}

void	thread_sleep(int id)
{
	printf("%d is sleeping\n", id);
	usleep(10000);
}

void	thread_eat(t_philosopher *philo, t_locks *locks)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&locks->fork_lock[philo->fork_right]);
		pthread_mutex_lock(&locks->fork_lock[philo->fork_left]);
	}
	else
	{
		pthread_mutex_lock(&locks->fork_lock[philo->fork_left]);
		pthread_mutex_lock(&locks->fork_lock[philo->fork_right]);
	}
	thread_msg("%d has taken a fork\n", philo->id, &locks->print_lock);
	thread_msg("%d is eating\n", philo->id, &locks->print_lock);
	pthread_mutex_unlock(&locks->fork_lock[philo->fork_right]);
	pthread_mutex_unlock(&locks->fork_lock[philo->fork_left]);
}

void	thread_think(int id)
{
	printf("%d is thinking\n", id);
}

void	*thread_monitor(void *arg)
{
	t_program	*data;

	data = (t_program *)arg;
	thread_eat(&data->philosopher, &data->locks);
	thread_sleep(data->philosopher.id);
	thread_think(data->philosopher.id);
	return (NULL);
}
