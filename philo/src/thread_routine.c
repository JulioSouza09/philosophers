/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcesar-s <jcesar-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 11:49:15 by jcesar-s          #+#    #+#             */
/*   Updated: 2025/09/26 13:13:43 by jcesar-s         ###   ########.fr       */
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
	printf("thread %d is eating...\n", id);
}

void	thread_think(int id)
{
	printf("Philosopher %d is thinking...\n", id);
}

void	*thread_monitor(void *arg)
{
	int	id;
	int raw_value = *(int *)arg;
   
	// TODO:
	//pthread_mutex_lock(ADDRESS OF PRINT MUTEX);
    printf("DEBUG: Raw value received: %d\n", raw_value);
	//pthread_mutex_unlock(pthread_mutex_t *mutex)
    fflush(stdout);
    
    id = raw_value + 1;
	thread_sleep(id);
	thread_eat(id);
	thread_think(id);
	return (NULL);
}

/*
 * lock mutex garfo 1
 * printa pegou 1 garfo
 * lock mutex garfo 2
 * printa pegou 2 garfos
 * comer
 * unlock 2 garos
 * */
