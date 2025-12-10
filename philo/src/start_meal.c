#include "../include/philo.h"

void	*meal_cycle(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
//	if (philo->id % 2 != 0 && philo->table->philos_count % 2 != 0)
//		usleep(1000);
	if (philo->id % 2 == 0)
		usleep(1000);
	while (philo->table->stop_meal != TRUE)
	{
		if (philo->table->stop_meal == TRUE)
			break ;
		philo_eat(philo);
		if (philo->table->stop_meal == TRUE)
			break ;
		philo_sleep(philo);
		if (philo->table->stop_meal == TRUE)
			break ;
		philo_think(philo);
	}
	return (NULL);
}

void	*monitor(void *arg)
{
	t_table		*table;
	t_timestamp	timestamp;
	int			i;

	table = (t_table *) arg;
	while (TRUE)
	{
		i = 0;
		while (i < table->philos_count)
		{
			timestamp = get_timestamp() - table->start_time;
			if (timestamp - table->philos[i].last_meal > (t_timestamp) table->rules.time_to_die)
			{
				print_state(&table->philos[i], table->philos[i].id, "has died", DONT_UPDATE);
				table->stop_meal = TRUE;
				return (NULL);
			}
			++i;
		}
	}
	(void)arg;
	return (NULL);
}

int	start_meal(t_table *table)
{
	int			i;
	pthread_t	*th;
	t_philo		*ph;

	th = table->threads;
	ph = table->philos;
	i = 0;
	table->start_time = get_timestamp();
	while (i < table->philos_count)
	{
		if (pthread_create(&th[i], NULL, meal_cycle, &ph[i]) != 0)
		{
			table->stop_meal = TRUE;
			finish_meal(th, i);
			return (EXIT_FAILURE);
		}
		++i;
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
