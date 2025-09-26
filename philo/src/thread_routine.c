/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcesar-s <jcesar-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 11:49:15 by jcesar-s          #+#    #+#             */
/*   Updated: 2025/09/26 16:14:50 by jcesar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>

void	thread_sleep(int id)
{
	printf("thread %d is sleeping...\n", id);
}

void	thread_eat(int id)
{
	printf("Philosopher %d has taken a fork\n", id);
	printf("Philosopher %d is eating...\n", id);
}

void	thread_think(int id)
{
	printf("Philosopher %d is thinking...\n", id);
}

void	*thread_monitor(void *arg)
{
	t_philosopher	*ph;
   
	ph = (t_philosopher *)arg;
	thread_sleep(ph->id);
	thread_eat(ph->id);
	thread_think(ph->id);
	return (NULL);
}
