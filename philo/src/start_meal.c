#include "../include/philo.h"
#include <pthread.h>
#include <unistd.h>

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
	t_timestamp val;

	pthread_mutex_lock(table->state_lock);
	val = *value;
	pthread_mutex_unlock(table->state_lock);
	return (val);
}

void	set_val(t_table *table, int *val, int content)
{
	pthread_mutex_lock(table->state_lock);
	*val = content;
	pthread_mutex_unlock(table->state_lock);
}

void	set_dead(t_table *table)
{
	pthread_mutex_lock(table->state_lock);
	table->stop_meal = TRUE;
	pthread_mutex_unlock(table->state_lock);
}

int	safe_print(t_philo *philo, long timestamp, char *message)
{
	long	start_time;

	if (is_dead(philo->table) == TRUE)
		return (EXIT_FAILURE);
	start_time = philo->table->start_time;
	pthread_mutex_lock(philo->table->print_lock);
	printf("%ld %d %s\n", timestamp - start_time, philo->id, message);
	pthread_mutex_unlock(philo->table->print_lock);
	return (EXIT_SUCCESS);
}

void	fork_take(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		safe_print(philo, get_timestamp(), "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		safe_print(philo, get_timestamp(), "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		safe_print(philo, get_timestamp(), "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		safe_print(philo, get_timestamp(), "has taken a fork");
	}
}

void	case_1_philo(t_philo *philo)
{
	while (is_dead(philo->table) != TRUE)
	{
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(philo->table->state_lock);
		philo->last_meal = get_timestamp();
		pthread_mutex_unlock(philo->table->state_lock);
		safe_print(philo, philo->last_meal, "has taken a fork");
		usleep(philo->table->rules.time_to_die * 1000);
		pthread_mutex_unlock(philo->right_fork);
	}
}

void	*meal_cycle(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	if (philo->table->philos_count == 1)
		case_1_philo(philo);
	if (philo->id % 2 == 0)
		usleep(1000);
	while (is_dead(philo->table) != TRUE)
	{
		pthread_mutex_lock(philo->left_fork);
		safe_print(philo, get_timestamp(), "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		safe_print(philo, get_timestamp(), "has taken a fork");
		//fork_take(philo);
		pthread_mutex_lock(philo->table->state_lock);
		philo->meals_count++;
		philo->last_meal = get_timestamp();
		pthread_mutex_unlock(philo->table->state_lock);
		safe_print(philo, philo->last_meal, "is eating");
		usleep(philo->table->rules.time_to_eat * 1000);
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);

		safe_print(philo, get_timestamp(), "is sleeping");
		usleep(philo->table->rules.time_to_sleep * 1000);

		safe_print(philo, get_timestamp(), "is thinking");
		if (philo->id % 2 != 0)
			usleep(1000);
		//philo_eat(philo);
		//philo_sleep(philo);
		//philo_think(philo);
	}
	return (NULL);
}

void	*monitor(void *arg)
{
	t_table		*table;
	t_timestamp	timestamp;
	t_timestamp	last_meal;
	int			i;
	int			minimum_meals;

	table = (t_table *) arg;
	while (TRUE)
	{
		i = 0;
		minimum_meals = 0;
		while (i < table->philos_count)
		{
			timestamp = get_timestamp();
			last_meal = get_val(table, &table->philos[i].last_meal);
			if (timestamp - last_meal > (t_timestamp) table->rules.time_to_die)
			{
				safe_print(&table->philos[i], timestamp, "has died");
				set_dead(table);
				return (NULL);
			}
			int meals = (int)get_val(table, (t_timestamp*) &table->philos[i].meals_count);
			if (table->rules.minimum_meals != -1 && meals >= table->rules.minimum_meals)
				++minimum_meals;
			++i;
		}
		if (minimum_meals == table->philos_count)
		{
			set_dead(table);
			return (NULL);
		}
		usleep(1000);
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
