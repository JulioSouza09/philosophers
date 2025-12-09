#include "../include/philo.h"

long	get_timestamp(void)
{
	struct timeval time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	print_state(t_philo *philo, int philo_id, char *action, int update)
{
	t_timestamp	timestamp;

	timestamp = get_timestamp() - philo->table->start_time;
	if (pthread_mutex_lock(philo->table->print_lock) != 0)
		return (EXIT_FAILURE);
	printf("%lld %d %s\n", timestamp, philo_id, action);
	if (pthread_mutex_unlock(philo->table->print_lock) != 0)
		return (EXIT_FAILURE);
	if (update == UPDATE_LAST_MEAL)
	{
		philo->last_meal = timestamp;
		philo->meals_count++;
	}
	else if (update == UPDATE_LAST_SLEEP)
		philo->last_sleep = timestamp;
	return (EXIT_SUCCESS);
}
