#include "../include/philo.h"
#include <pthread.h>

int	create_forks(pthread_mutex_t **forks, int size)
{
	int	i;

	*forks = ft_calloc(size, sizeof(pthread_mutex_t));
	if (*forks == NULL)
		return (EXIT_FAILURE);
	i = 0;
	while (i < size)
	{
		if (pthread_mutex_init(&(*forks)[i], NULL) != 0)
			return (EXIT_FAILURE);
		++i;
	}
	return (EXIT_SUCCESS);
}

int	create_philos(t_table *table)
{
	int	i;
	int	size;

	size = table->philos_count;
	table->philos = ft_calloc(size, sizeof(t_philo));
	if (table->philos == NULL)
		return (EXIT_FAILURE);
	i = 0;
	while (i < size)
	{
		table->philos[i].id = i + 1;
		table->philos[i].left_fork = &table->forks[i];
		table->philos[i].right_fork = &table->forks[(i + 1) % size];
		table->philos[i].table = table;
		++i;
	}
	return (EXIT_SUCCESS);
}

int	create_rules(t_rules *rules, int arg_count, char **args)
{
	int	i;

	i = 2;
	while (i < arg_count)
	{
		if (is_valid_number(args[i]) == FALSE)
			return (EXIT_FAILURE);
		++i;
	}
	if (ft_atoi_safe(args[2], &rules->time_to_die) != 0)
		return (EXIT_FAILURE);
	if (ft_atoi_safe(args[3], &rules->time_to_eat) != 0)
		return (EXIT_FAILURE);
	if (ft_atoi_safe(args[4], &rules->time_to_sleep) != 0)
		return (EXIT_FAILURE);
	if (arg_count == 6)
	{
		if (ft_atoi_safe(args[5], &rules->minimum_meals) != 0)
			return (EXIT_FAILURE);
	}
	else
		rules->minimum_meals = -1;
	return (EXIT_SUCCESS);
}

t_table	*create_table(int arg_count, char **args)
{
	t_table	*table;

	table = ft_calloc(1, sizeof(t_table));
	if (table == NULL)
		return (NULL);
	if (is_valid_number(args[1]) == FALSE)
		return (clean_table(table), NULL);
	if (ft_atoi_safe(args[1], &table->philos_count) != 0)
		return (clean_table(table), NULL);
	table->threads = ft_calloc(table->philos_count + 1, sizeof(pthread_t));
	if (table->threads == NULL)
		return (clean_table(table), NULL);
	if (create_forks(&table->forks, table->philos_count) != 0)
		return (clean_table(table), NULL);
	if (create_philos(table) != 0)
		return (clean_table(table), NULL);
	if (create_rules(&table->rules, arg_count, args) != 0)
		return (clean_table(table), NULL);
	table->print_lock = ft_calloc(1, sizeof(pthread_mutex_t));
	if (table->print_lock == NULL)
		return (clean_table(table), NULL);
	if (pthread_mutex_init(table->print_lock, NULL) != 0)
		return (clean_table(table), NULL);
	table->state_lock = ft_calloc(1, sizeof(pthread_mutex_t));
	if (table->state_lock == NULL)
		return (clean_table(table), NULL);
	if (pthread_mutex_init(table->print_lock, NULL) != 0)
		return (clean_table(table), NULL);
	table->stop_meal = FALSE;
	return (table);
}

void	clean_table(t_table *table)
{
	int	i;

	if (table == NULL)
		return ;
	if (table->forks != NULL)
	{
		i = 0;
		while (i < table->philos_count)
			pthread_mutex_destroy(&table->forks[i++]);
		free(table->forks);
	}
	if (table->philos != NULL)
		free(table->philos);
	if (table->threads != NULL)
		free(table->threads);
	free(table);
}
