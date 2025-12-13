/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_meal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcesar-s <jcesar-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 16:10:58 by jcesar-s          #+#    #+#             */
/*   Updated: 2025/12/13 19:59:02 by jcesar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

void	*meal_cycle(void *arg)
{
	t_philo	*philo;
	long	time;

	philo = (t_philo *) arg;
	if (philo->table->philos_count == 1)
		case_1_philo(philo);
	if (philo->id % 2 == 0)
		usleep(1000);
	time = philo->table->rules.time_to_sleep;
	while (is_dead(philo->table) != TRUE)
	{
		philo_eat(philo);
		safe_print(philo, get_timestamp(), "is sleeping");
		if (philo->table->rules.time_to_die < time)
			time = philo->table->rules.time_to_die;
		usleep(time * 1000);
		safe_print(philo, get_timestamp(), "is thinking");
		if (philo->id % 2 != 0)
			usleep(1000);
	}
	return (NULL);
}

int	check_death(t_table *table, int *minimum_meals)
{
	t_timestamp	timestamp;
	t_timestamp	last_meal;
	int			meals;
	int			i;

	i = 0;
	*minimum_meals = 0;
	while (i < table->philos_count)
	{
		timestamp = get_timestamp();
		last_meal = get_val(table, &table->philos[i].last_meal);
		if (timestamp - last_meal > (t_timestamp) table->rules.time_to_die)
		{
			safe_print(&table->philos[i], timestamp, "has died");
			set_dead(table);
			return (EXIT_FAILURE);
		}
		meals = (int)get_val(table,
				(t_timestamp*) &table->philos[i].meals_count);
		if (table->rules.minimum_meals != -1
			&& meals >= table->rules.minimum_meals)
			++(*minimum_meals);
		++i;
	}
	return (EXIT_SUCCESS);
}

void	*monitor(void *arg)
{
	t_table		*table;
	int			minimum_meals;

	table = (t_table *) arg;
	while (TRUE)
	{
		if (check_death(table, &minimum_meals) != 0)
			return (NULL);
		if (minimum_meals == table->philos_count)
		{
			set_dead(table);
			return (NULL);
		}
		usleep(1000);
	}
	return (NULL);
}

int	start_meal(t_table *table)
{
	int			i;
	pthread_t	*th;
	t_philo		*ph;

	th = table->threads;
	ph = table->philos;
	i = -1;
	table->start_time = get_timestamp();
	while (++i < table->philos_count)
	{
		table->philos[i].last_meal = table->start_time;
		if (pthread_create(&th[i], NULL, meal_cycle, &ph[i]) != 0)
		{
			table->stop_meal = TRUE;
			finish_meal(th, i);
			return (EXIT_FAILURE);
		}
	}
	if (pthread_create(&th[i], NULL, monitor, table) != 0)
	{
		table->stop_meal = TRUE;
		finish_meal(th, i);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	finish_meal(pthread_t *threads, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (pthread_join(threads[i], NULL) != 0)
			return (EXIT_FAILURE);
		++i;
	}
	return (EXIT_SUCCESS);
}
